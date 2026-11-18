.section .text
.align 1
.balign 1

.global _start
_start:
    # set sp to top of wram
    movhi   hi(0x05010000), r0, sp
    movea   lo(0x05010000), sp, sp

    # reset gp and tp
    mov     r0, gp
    mov     r0, tp

    # to c!
    jal     _main

.global _halt
_halt:
    halt
    jr      _halt
