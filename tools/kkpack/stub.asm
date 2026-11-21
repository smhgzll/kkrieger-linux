; kkpack stub: a tiny static i386 ELF that unpacks the game and execs it.
;
;   nasm -f bin -DPAYLOAD='"payload.bin"' -DPAYLOADINC='"payload.inc"' -o out stub.asm
;
; 1. context-mixing decode (model.asm = kkrunchy_k7 model, ryg, public
;    domain) of [DisFilter tables][DisFilter(.text)][rest of the ELF file]
;    into ubuf
; 2. rebuild the ELF file in img (DisUnfilter = depack2.asm without the
;    PE import/jump table parts)
; 3. memfd_create + write + execveat; with -DLIBPATH (port/dxvk) with
;    LD_LIBRARY_PATH=<our directory> appended so libdxvk_d3d9.so.0 next to
;    us is found ($ORIGIN of a memfd is useless)

bits 32

%define BINARY
%include PAYLOADINC

%define BASE 0x08048000

; ---------------------------------------------------------------------------

section .text
org BASE

ehdr:   db      0x7f,"ELF",1,1,1,0
        dd      0,0
        dw      2,3                     ; ET_EXEC, EM_386
        dd      1
        dd      _start
        dd      phdr-ehdr
        dd      0,0
        dw      52,32,1,0,0,0
phdr:   dd      1,0,ehdr,ehdr           ; PT_LOAD everything, RWX
        dd      file_end-ehdr,bss_end-ehdr
        dd      7,0x1000

; range decoder: eax = P(bit=1) (12 bits) -> ecx = bit
; ebx = code, ebp = range, esi = packed input
decbit: mul     ebp
        shrd    eax,edx,12
        xor     ecx,ecx
        cmp     ebx,eax
        jae     .zero
        mov     ebp,eax
        inc     ecx
        jmp     short .norm
.zero:  sub     ebx,eax
        sub     ebp,eax
.norm:  test    ebp,0xff000000
        jnz     .ret
        shl     ebx,8
        lodsb
        mov     bl,al
        shl     ebp,8
        jmp     short .norm
.ret:   ret

_start:
        mov     esi,payload
        lodsd
        bswap   eax
        xchg    eax,ebx                 ; code
        or      ebp,byte -1             ; range
        call    modelInitASM
        mov     edi,ubuf
        mov     [bufPtr],edi
        mov     [startBufPtr],edi

.byte:  mov     eax,[bufPtr]
        sub     eax,ubuf
        cmp     eax,USIZE
        jae     .decoded
        test    ax,8191                 ; every 8 KB: all-zero block flag
        jnz     .bits
        mov     eax,[zprob]
        call    decbit
        imul    eax,ecx,4095
        inc     eax                     ; bit ? 4096 : 1
        add     eax,[zprob]
        shr     eax,1
        mov     [zprob],eax
        jecxz   .bits
        add     dword [bufPtr],8192     ; (ubuf is already zero)
        jmp     short .byte

.bits:  push    byte 1
        pop     edi                     ; byte with a sentinel bit
.bit:   mov     eax,[prob]
        call    decbit
        lea     edi,[edi*2+ecx]
        cmp     edi,256
        jb      .model
        mov     eax,[bufPtr]
        mov     edx,edi
        mov     [eax],dl
        inc     dword [bufPtr]
.model: call    modelASM                ; fastcall: ecx = bit -> eax = P(1)
        mov     [prob],eax
        cmp     edi,256
        jb      .bit
        jmp     short .byte

.decoded:
        ; head and tail of the ELF file around .text
        mov     esi,ubuf+FSIZE
        mov     edi,img
        mov     ecx,TEXTOFF
        rep     movsb
        mov     edi,img+TEXTOFF+TEXTSIZE
        mov     ecx,FILESIZE-TEXTOFF-TEXTSIZE
        rep     movsb
        mov     esi,ubuf+256
        mov     edi,img+TEXTOFF
        call    DisUnfilter

%ifdef DUMP
        push    byte 4                  ; test build: write the image to stdout
        pop     eax
        xor     ebx,ebx
        inc     ebx
        mov     ecx,img
        mov     edx,FILESIZE
        int     0x80
        xor     eax,eax
        inc     eax
        int     0x80
%endif
%ifdef LIBPATH
        ; LD_LIBRARY_PATH=<dir of /proc/self/exe>
        mov     esi,ldpath
        mov     edi,envbuf
        push    byte 16
        pop     ecx
        rep     movsb
        push    byte 85                 ; readlink
        pop     eax
        mov     ebx,procexe
        mov     ecx,edi
        mov     edx,4000
        int     0x80
        test    eax,eax
        jle     .nolink
        add     edi,eax
        xchg    eax,ecx
        mov     al,'/'
        std
        repne   scasb
        cld
        mov     byte [edi+1],0
.nolink:
        ; envp' = envp + our entry (the last LD_LIBRARY_PATH wins in ld.so)
        mov     eax,[esp]               ; argc
        lea     esi,[esp+eax*4+8]
        mov     edi,newenv
.env:   lodsd
        test    eax,eax
        jz      .envend
        stosd
        jmp     short .env
.envend:
        mov     dword [edi],envbuf
%endif
        ; fd = memfd_create("kkrieger", MFD_CLOEXEC|MFD_EXEC), retry
        ; without MFD_EXEC for kernels before 6.3
        mov     ebx,memname
        push    byte 0x11
        pop     ecx
        mov     eax,356
        int     0x80
        test    eax,eax
        jns     .gotfd
        mov     cl,1
        mov     eax,356
        int     0x80
.gotfd: xchg    eax,ebx
        push    byte 4                  ; write(fd,img,FILESIZE)
        pop     eax
        mov     ecx,img
        mov     edx,FILESIZE
        int     0x80
%ifdef LIBPATH
        mov     eax,358                 ; execveat(fd,"",argv,envp',AT_EMPTY_PATH)
        mov     ecx,memname+8
        lea     edx,[esp+4]
        mov     esi,newenv
%else
        pop     eax                     ; argc
        mov     edx,esp                 ; argv
        lea     esi,[esp+eax*4+4]       ; envp
        mov     eax,358                 ; execveat(fd,"",argv,envp,AT_EMPTY_PATH)
        mov     ecx,memname+8
%endif
        mov     edi,0x1000
        int     0x80
        xchg    eax,ebx                 ; exit(-errno)
        neg     ebx
        push    byte 1
        pop     eax
        int     0x80

; ---------------------------------------------------------------------------
; DisUnfilter: esi = filtered code, edi = dest

%define NBUFFERS 20
%define fMR   0x2
%define fMO   0x3
%define fMODE 0x3
%define fAM   0x1
%define fNI   0x0
%define fBI   0x4
%define fDI   0x8

struc da
.buffer     resd NBUFFERS
.offset     resd 1
.lastJump   resd 1
.nextFunc   resd 1
.funcTable  resd 256
endstruc

DisUnfilter:
        mov     ebp,dataArea
        lea     eax,[edi-4]
        mov     [ebp+da.offset],eax
        xor     eax,eax
        inc     eax
        mov     [ebp+da.nextFunc],eax
        mov     [ebp+da.funcTable],eax  ; funcTable[0] = insert position
        lea     ebx,[esi+NBUFFERS*4]
        xor     ecx,ecx
.init:  lodsd
        mov     [ebp+da.buffer+ecx*4],ebx
        add     ebx,eax
        inc     ecx
        cmp     cl,NBUFFERS
        jne     .init
        mov     esi,[ebp+da.buffer+1*4]
        xchg    esi,[ebp+da.buffer]     ; esi = opcodes, buffer[0] = their end

.main:  cmp     esi,[ebp+da.buffer]
        jb      .gotins
        ret

.gotins:
        xor     eax,eax
        cmp     [ebp+da.nextFunc],eax
        lodsb
        je      .testes
        cmp     al,0xcc
        je      .testes
        lea     ecx,[edi-4]
        sub     ecx,[ebp+da.offset]
        mov     ebx,[ebp+da.funcTable]
        mov     [ebp+da.funcTable+ebx*4],ecx
.incm:  inc     byte [ebp+da.funcTable]
        jz      .incm
        mov     byte [ebp+da.nextFunc],0

.testes:
        cmp     al,0xce                 ; escape
        jne     .noesc
        movsb
        jmp     short .main

.noesc: stosb
        xor     edx,edx
        cmp     al,0x66                 ; operand size prefix
        jne     .nopfx
        mov     dh,1
        lodsb
        stosb
.nopfx: mov     bl,al
        cmp     bl,0xcc
        je      .isret
        sub     bl,0xc2
        cmp     bl,1
        ja      .noret
.isret: mov     byte [ebp+da.nextFunc],1
.noret: mov     ebx,ubuf            ; the opcode tables come first
        cmp     al,0x0f
        jne     .notwo
        lodsb
        stosb
        mov     ah,1
.notwo: shr     eax,1
        xlatb
        jnc     .flagok
        shr     al,4
.flagok:
        and     al,0xf
        mov     cl,al

        test    cl,fMR                  ; mod/rm follows?
        jz      near .nomdrm
        lodsb
        stosb
        mov     ch,al
        mov     al,cl
        and     al,fMODE
        cmp     al,fMO
        jne     .noxtra
        mov     cl,fMR|fNI              ; f6/f7/fe/ff group
        test    ch,0x38
        jnz     .noxtra
        mov     bl,[edi-2]
        test    bl,0x08
        jnz     .noxtra
        add     cl,fBI
        test    bl,0x01
        jz      .noxtra
        add     cl,fDI-fBI
.noxtra:
        and     ch,0xc7
        cmp     ch,0xc4
        je      .nosib
        mov     al,ch
        and     al,0x07
        cmp     al,0x04
        jne     .nosib
        xchg    esi,[ebp+da.buffer+19*4]
        movsb
        xchg    esi,[ebp+da.buffer+19*4]
.nosib: mov     dl,ch
        and     dl,0xc0
        cmp     dl,0x40
        jne     .nodis8
        movzx   ebx,ch
        and     bl,0x07
        xchg    esi,[ebp+da.buffer+1*4+ebx*4]
        movsb
        xchg    esi,[ebp+da.buffer+1*4+ebx*4]
.nodis8:
        cmp     dl,0x80
        je      .dis32
        cmp     ch,0x05
        je      .dis32
        test    dl,dl
        jnz     .nomdrm
        mov     al,[edi-1]
        and     al,0x07
        cmp     al,0x05
        jne     .nomdrm
.dis32: xor     ebx,ebx
        cmp     ch,5
        jne     .nomr5
        inc     ebx
.nomr5: xchg    esi,[ebp+da.buffer+13*4+ebx*4]
        lodsd
        xchg    esi,[ebp+da.buffer+13*4+ebx*4]
        bswap   eax
        stosd

.nomdrm:
        mov     al,cl
        and     al,fMODE
        cmp     al,fAM
        jne     near .noaddr
        shr     cl,2
        jnz     .noad
        xchg    esi,[ebp+da.buffer+15*4]    ; absolute address
        movsd
        xchg    esi,[ebp+da.buffer+15*4]
        jmp     .main
.noad:  dec     cl
        jnz     .dwdrl
        xchg    esi,[ebp+da.buffer+9*4]     ; short branch
        movsb
        xchg    esi,[ebp+da.buffer+9*4]
        jmp     .main
.dwdrl: cmp     byte [edi-1],0xe8
        je      .dwcal
        xchg    esi,[ebp+da.buffer+17*4]    ; near jump: delta to the last one
        lodsd
        xchg    esi,[ebp+da.buffer+17*4]
        shr     eax,1
        jnc     .jmpnc
        not     eax
.jmpnc: add     eax,[ebp+da.lastJump]
        mov     [ebp+da.lastJump],eax
        jmp     short .storad
.dwcal: xor     eax,eax                     ; call: function cache index
        xchg    esi,[ebp+da.buffer+16*4]
        lodsb
        xchg    esi,[ebp+da.buffer+16*4]
        test    al,al
        jz      .dcesc
        mov     eax,[ebp+da.funcTable+eax*4]
        jmp     short .storad
.dcesc: xchg    esi,[ebp+da.buffer+18*4]
        lodsd
        xchg    esi,[ebp+da.buffer+18*4]
        mov     ebx,[ebp+da.funcTable]
        mov     [ebp+da.funcTable+ebx*4],eax
.dcinc: inc     byte [ebp+da.funcTable]
        jz      .dcinc
.storad:
        sub     eax,edi
        add     eax,[ebp+da.offset]
        stosd
        jmp     .main

.noaddr:
        shr     cl,2
        jz      near .main
        dec     cl
        jnz     .dwow
        xchg    esi,[ebp+da.buffer+10*4]    ; imm8
        movsb
        xchg    esi,[ebp+da.buffer+10*4]
        jmp     .main
.dwow:  dec     cl
        jnz     .word
        test    dh,dh
        jnz     .word
        xchg    esi,[ebp+da.buffer+12*4]    ; imm32
        movsd
        xchg    esi,[ebp+da.buffer+12*4]
        jmp     .main
.word:  xchg    esi,[ebp+da.buffer+11*4]    ; imm16
        movsw
        xchg    esi,[ebp+da.buffer+11*4]
        jmp     .main

; ---------------------------------------------------------------------------

%include "model.asm"

section .data

prob:     dd 2048
zprob:    dd 1
%ifdef LIBPATH
ldpath:   db "LD_LIBRARY_PATH="
procexe:  db "/proc/self/exe",0
%endif
memname:  db "kkrieger",0
payload:  incbin PAYLOAD
file_end:

section .bss

dataArea: resb da_size
%ifdef LIBPATH
newenv:   resd 16384
envbuf:   resb 4096
%endif
          resb 32                       ; the model reads before the buffer
ubuf:     resb USIZE+8192+64
img:      resb FILESIZE+64
bss_end:
