; framedump.asm - code cave for pno0001_unpacked.exe (2004 .kkrieger)
;
; The call to IDirect3DDevice9::Present in sSystem_::Render (0x804400:
; "push ebx x4 / push eax / call [ecx+0x44]") is redirected here. At the
; times listed in Targets (ms since the first frame) the backbuffer
; (1024x768 A8R8G8B8) is written to shot_NN.raw in the current directory.
;
; nasm -f bin -o framedump.bin framedump.asm
;
; -DPLAYTEST -DKEYS='dd ms,0x100,vk, ms,0x101,vk, ...' additionally injects
; key presses and logs the player position to pos.bin (see playtest)

        bits    32
        org     HOOKVA

%define IAT_GetProcAddress   0x81f040
%define IAT_GetModuleHandleA 0x81f048
%define IAT_timeGetTime      0x81f0b8

hook:                                   ; eax = device, ecx = vtable, ebx = 0
        pushad
        push    eax
        call    dumper
        popad
        pop     edx                     ; return address (0x804405)
        push    ebx
        push    ebx
        push    ebx
        push    ebx
        push    eax
        push    edx
        jmp     [ecx+0x44]              ; real Present, returns to caller

; void __stdcall dumper(IDirect3DDevice9 *dev)
dumper:
        push    ebp
        mov     ebp,esp
        sub     esp,32                  ; [ebp-4] bb, [ebp-8] sys, [ebp-16] lr, [ebp-20] h, [ebp-24] written
        push    esi
        push    edi
        push    ebx

        call    [IAT_timeGetTime]
        cmp     dword [Started],0
        jne     .s
        mov     [Start],eax
        mov     dword [Started],1
.s:     sub     eax,[Start]
%ifdef PLAYTEST
        push    eax
        push    dword [ebp+8]
        push    eax
        call    playtest
        pop     eax
%endif
        mov     ecx,[NextIdx]
        cmp     ecx,NTARGETS
        jae     .done
        cmp     eax,[Targets+ecx*4]
        jb      .done
        inc     dword [NextIdx]

        ; file name: shot_NN.raw
        mov     eax,ecx
        xor     edx,edx
        mov     ebx,10
        div     ebx
        add     al,'0'
        add     dl,'0'
        mov     [FileName+5],al
        mov     [FileName+6],dl

        call    resolve

        mov     esi,[ebp+8]             ; device
        ; GetBackBuffer(dev,0,0,D3DBACKBUFFER_TYPE_MONO,&bb)
        lea     eax,[ebp-4]
        push    eax
        push    0
        push    0
        push    0
        push    esi
        mov     eax,[esi]
        call    [eax+0x48]
        ; CreateOffscreenPlainSurface(dev,1024,768,A8R8G8B8,SYSTEMMEM,&sys,0)
        lea     eax,[ebp-8]
        push    0
        push    eax
        push    2
        push    21
        push    768
        push    1024
        push    esi
        mov     eax,[esi]
        call    [eax+0x90]
        ; GetRenderTargetData(dev,bb,sys)
        push    dword [ebp-8]
        push    dword [ebp-4]
        push    esi
        mov     eax,[esi]
        call    [eax+0x80]
        ; sys->LockRect(&lr,0,D3DLOCK_READONLY)
        lea     eax,[ebp-16]
        push    0x10
        push    0
        push    eax
        mov     eax,[ebp-8]
        push    eax
        mov     eax,[eax]
        call    [eax+0x34]
        ; h = CreateFileA(name,GENERIC_WRITE,0,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0)
        push    0
        push    0x80
        push    2
        push    0
        push    0
        push    0x40000000
        push    FileName
        call    [pCreateFileA]
        mov     [ebp-20],eax
        ; WriteFile(h,pBits,pitch*768,&written,0)
        push    0
        lea     eax,[ebp-24]
        push    eax
        mov     eax,[ebp-16]            ; pitch
        imul    eax,eax,768
        push    eax
        push    dword [ebp-12]          ; pBits
        push    dword [ebp-20]
        call    [pWriteFile]
        push    dword [ebp-20]
        call    [pCloseHandle]
        ; sys->UnlockRect(); sys->Release(); bb->Release()
        mov     eax,[ebp-8]
        push    eax
        mov     eax,[eax]
        call    [eax+0x38]
        mov     eax,[ebp-8]
        push    eax
        mov     eax,[eax]
        call    [eax+0x08]
        mov     eax,[ebp-4]
        push    eax
        mov     eax,[eax]
        call    [eax+0x08]
.done:
        pop     ebx
        pop     edi
        pop     esi
        leave
        ret     4

%ifdef PLAYTEST
; void __stdcall playtest(int t,IDirect3DDevice9 *dev)
; - posts the key events of KeyTable (WM_KEYDOWN/UP to the focus window)
; - every 250 ms appends (t, PlayerPos x,y,z) to pos.bin; PlayerPos is
;   KKriegerGame+0x14948 (OnTick 0x81dd4c copies it into shot events),
;   the game object pointer is at 0x14a0998
%define GAMEPTR   0x14a0998
%define PLAYERPOS 0x14948
playtest:
        push    ebp
        mov     ebp,esp
        sub     esp,32
        push    esi
        push    edi
        push    ebx
        call    resolve
.key:   mov     ecx,[KeyIdx]
        cmp     ecx,NKEYS
        jae     .nokey
        imul    ecx,ecx,12
        mov     eax,[ebp+8]
        cmp     eax,[KeyTable+ecx]
        jb      .nokey
        inc     dword [KeyIdx]
        ; hwnd = GetCreationParameters(dev,&p).hFocusWindow
        lea     eax,[ebp-32]
        push    eax
        mov     eax,[ebp+12]
        push    eax
        mov     eax,[eax]
        call    [eax+0x24]
        mov     ecx,[KeyIdx]
        dec     ecx
        imul    ecx,ecx,12
        push    0
        push    dword [KeyTable+ecx+8]  ; vk
        push    dword [KeyTable+ecx+4]  ; msg
        push    dword [ebp-24]          ; hFocusWindow
        call    [pPostMessageA]
        jmp     .key
.nokey:
        mov     eax,[ebp+8]
        cmp     eax,[NextLog]
        jb      .ret
        add     eax,250
        mov     [NextLog],eax
        mov     esi,[GAMEPTR]
        test    esi,esi
        jz      .ret
        mov     eax,[ebp+8]
        mov     [ebp-16],eax
        mov     eax,[esi+PLAYERPOS]
        mov     [ebp-12],eax
        mov     eax,[esi+PLAYERPOS+4]
        mov     [ebp-8],eax
        mov     eax,[esi+PLAYERPOS+8]
        mov     [ebp-4],eax
        cmp     dword [LogHandle],0
        jne     .open
        ; CreateFileA("pos.bin",GENERIC_WRITE,FILE_SHARE_READ,0,CREATE_ALWAYS,0x80,0)
        push    0
        push    0x80
        push    2
        push    0
        push    1
        push    0x40000000
        push    LogName
        call    [pCreateFileA]
        mov     [LogHandle],eax
.open:  push    0
        lea     eax,[ebp-20]
        push    eax
        push    16
        lea     eax,[ebp-16]
        push    eax
        push    dword [LogHandle]
        call    [pWriteFile]
.ret:   pop     ebx
        pop     edi
        pop     esi
        leave
        ret     8
%endif

; resolve kernel32 functions once
resolve:
        cmp     dword [pCreateFileA],0
        jne     .r
        push    Kernel32
        call    [IAT_GetModuleHandleA]
        mov     ebx,eax
        push    sCreateFileA
        push    ebx
        call    [IAT_GetProcAddress]
        mov     [pCreateFileA],eax
        push    sWriteFile
        push    ebx
        call    [IAT_GetProcAddress]
        mov     [pWriteFile],eax
        push    sCloseHandle
        push    ebx
        call    [IAT_GetProcAddress]
        mov     [pCloseHandle],eax
%ifdef PLAYTEST
        push    User32
        call    [IAT_GetModuleHandleA]
        push    sPostMessageA
        push    eax
        call    [IAT_GetProcAddress]
        mov     [pPostMessageA],eax
%endif
.r:     ret

        align   4
Started dd 0
Start   dd 0
NextIdx dd 0
pCreateFileA dd 0
pWriteFile   dd 0
pCloseHandle dd 0
Targets:
%ifdef TARGETS
        dd      TARGETS
%else
        dd      2000,5000,10000,15000,20000,25000,30000,40000,50000,60000,70000,75000,80000
%endif
NTARGETS equ ($-Targets)/4
FileName db "shot_00.raw",0
%ifdef PLAYTEST
        align   4
KeyIdx  dd 0
NextLog dd 0
LogHandle dd 0
pPostMessageA dd 0
KeyTable:                               ; ms, WM_KEYDOWN/WM_KEYUP, vk
        KEYS
NKEYS equ ($-KeyTable)/12
LogName db "pos.bin",0
User32  db "user32.dll",0
sPostMessageA db "PostMessageA",0
%endif
Kernel32 db "kernel32.dll",0
sCreateFileA db "CreateFileA",0
sWriteFile   db "WriteFile",0
sCloseHandle db "CloseHandle",0
