; Program entry for the size build (-nostartfiles): glibc's i386 start.S
; without the crt1/crti/crtbegin baggage. __libc_start_main runs the
; init_array itself (glibc >= 2.34).
                bits    32
                section .text
                global  _start
                extern  __libc_start_main
                extern  main
%ifdef HASHIMPORT
                extern  ResolveImports
%endif
_start:
%ifdef HASHIMPORT
                push    edx                 ; rtld_fini
                call    ResolveImports      ; imports by hash (linux/imports.cpp)
                pop     edx
%endif
                xor     ebp,ebp
                pop     esi                 ; argc
                mov     ecx,esp             ; argv
                and     esp,-16
                push    eax                 ; padding
                push    esp                 ; stack end
                push    edx                 ; rtld_fini
                xor     eax,eax
                push    eax                 ; fini
                push    eax                 ; init
                push    ecx
                push    esi
                push    main
                call    __libc_start_main
                hlt

                section .rodata
                global  _IO_stdin_used      ; "new" stdio ABI (i386 has the 2.0 compat one)
_IO_stdin_used: dd      0x20001
                section .data
                global  __dso_handle
__dso_handle:   dd      0
