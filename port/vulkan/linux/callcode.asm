; kkCallCode(code, para, count): copy `count` dwords to the stack and call
; `code` (stdcall operator handlers pop their own arguments; esp is restored
; from ebp anyway, so a mismatch in argument count is harmless).
                bits    32
                section .text
                global  kkCallCode
kkCallCode:     push    ebp
                mov     ebp,esp
                push    esi
                push    edi
                push    ebx
                mov     eax,[ebp+8]         ; code
                mov     esi,[ebp+12]        ; para
                mov     ecx,[ebp+16]        ; count
                lea     edx,[ecx*4]
                sub     esp,edx
                and     esp,-16             ; SysV i386 alignment for the callee
                mov     edi,esp
                cld
                rep     movsd
                call    eax
                lea     esp,[ebp-12]
                pop     ebx
                pop     edi
                pop     esi
                pop     ebp
                ret
