; Embedded game data for the Linux build (NASM, elf32).
; KKDATA is the exported werkkzeug document (.kx), passed with -D on the
; command line; by default the one extracted from the original pno0001.exe.

                bits    32
                section .data

%ifndef KKDATA
%define KKDATA "pno0001_release.kx"
%endif

                global  kkrieger_data
                global  kkrieger_data_size
kkrieger_data:  incbin  KKDATA
kkrieger_data_end:
                align   4
kkrieger_data_size: dd  kkrieger_data_end - kkrieger_data
