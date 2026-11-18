OUTPUT_FORMAT("elf32-v810")
OUTPUT_ARCH(v810)
ENTRY(_start)

MEMORY
{
    WRAM (rwx) : ORIGIN = 0x05000000, LENGTH = 64K
    ROM  (rx)  : ORIGIN = 0x07000000, LENGTH = 512K
}

SECTIONS
{
    __WRAM_START = ORIGIN(WRAM);
    __ROM_START = ORIGIN(ROM);

    .text : {
        start = .;
        *(.text*)
        *(.rodata*)
        . = start + 0x7fde0;
    } > ROM = 0xFF

    .data : {
        *(.data*)
    } > WRAM AT > ROM

    .bss : {
        *(.bss*)
        *(COMMON)
    } > WRAM




    /* header */

    .vbheader (ORIGIN(ROM) + LENGTH(ROM) - 0x220 - SIZEOF(.vbheader)) : {
        start = .;
        *(.vbheader)
        . = start + 0x20;
    } > ROM = 0xFF


    /* interrupts */

    .int_game_pad_interrupt (ORIGIN(ROM) + LENGTH(ROM) - 0x200 - SIZEOF(.int_game_pad_interrupt)) : {
        start = .;
        *(.int_game_pad_interrupt)
        . = start + 0x10;
    } > ROM = 0xFF

    .int_timer_zero_interrupt (ORIGIN(ROM) + LENGTH(ROM) - 0x1F0 - SIZEOF(.int_timer_zero_interrupt)) : {
        start = .;
        *(.int_timer_zero_interrupt)
        . = start + 0x10;
    } > ROM = 0xFF

    .int_game_pak_interrupt (ORIGIN(ROM) + LENGTH(ROM) - 0x1E0 - SIZEOF(.int_game_pak_interrupt)) : {
        start = .;
        *(.int_game_pak_interrupt)
        . = start + 0x10;
    } > ROM = 0xFF

    .int_communication_interrupt (ORIGIN(ROM) + LENGTH(ROM) - 0x1D0 - SIZEOF(.int_communication_interrupt)) : {
        start = .;
        *(.int_communication_interrupt)
        . = start + 0x10;
    } > ROM = 0xFF

    .int_vip_interrupt (ORIGIN(ROM) + LENGTH(ROM) - 0x1C0 - SIZEOF(.int_vip_interrupt)) : {
        start = .;
        *(.int_vip_interrupt)
        . = start + 0x10;
    } > ROM = 0xFF

    .int_unused1 (ORIGIN(ROM) + LENGTH(ROM) - 0x1B0 - SIZEOF(.int_unused1)) : {
        start = .;
        *(.int_unused1)
        . = start + 0xB0;
    } > ROM = 0xFF

    .int_unused2 (ORIGIN(ROM) + LENGTH(ROM) - 0x100 - SIZEOF(.int_unused2)) : {
        start = .;
        *(.int_unused2)
        . = start + 0x60;
    } > ROM = 0xFF

    .int_floating_point_exception (ORIGIN(ROM) + LENGTH(ROM) - 0xA0 - SIZEOF(.int_floating_point_exception)) : {
        start = .;
        *(.int_floating_point_exception)
        . = start + 0x10;
    } > ROM = 0xFF

    .int_unused3 (ORIGIN(ROM) + LENGTH(ROM) - 0x90 - SIZEOF(.int_unused3)) : {
        start = .;
        *(.int_unused3)
        . = start + 0x10;
    } > ROM = 0xFF

    .int_zero_division_exception (ORIGIN(ROM) + LENGTH(ROM) - 0x80 - SIZEOF(.int_zero_division_exception)) : {
        start = .;
        *(.int_zero_division_exception)
        . = start + 0x10;
    } > ROM = 0xFF

    .int_illegal_opcode_exception (ORIGIN(ROM) + LENGTH(ROM) - 0x70 - SIZEOF(.int_illegal_opcode_exception)) : {
        start = .;
        *(.int_illegal_opcode_exception)
        . = start + 0x10;
    } > ROM = 0xFF

    .int_trap_instruction_less (ORIGIN(ROM) + LENGTH(ROM) - 0x60 - SIZEOF(.int_trap_instruction_less)) : {
        start = .;
        *(.int_trap_instruction_less)
        . = start + 0x10;
    } > ROM = 0xFF

    .int_trap_instruction_greater (ORIGIN(ROM) + LENGTH(ROM) - 0x50 - SIZEOF(.int_trap_instruction_greater)) : {
        start = .;
        *(.int_trap_instruction_greater)
        . = start + 0x10;
    } > ROM = 0xFF

    .int_address_trap (ORIGIN(ROM) + LENGTH(ROM) - 0x40 - SIZEOF(.int_address_trap)) : {
        start = .;
        *(.int_address_trap)
        . = start + 0x10;
    } > ROM = 0xFF

    .int_duplexed_exception (ORIGIN(ROM) + LENGTH(ROM) - 0x30 - SIZEOF(.int_duplexed_exception)) : {
        start = .;
        *(.int_duplexed_exception)
        . = start + 0x10;
    } > ROM = 0xFF

    .int_unused4 (ORIGIN(ROM) + LENGTH(ROM) - 0x20 - SIZEOF(.int_unused4)) : {
        start = .;
        *(.int_unused4)
        . = start + 0x10;
    } > ROM = 0xFF

    .int_reset (ORIGIN(ROM) + LENGTH(ROM) - 0x10 - SIZEOF(.int_reset)) : {
        start = .;
        *(.int_reset)
        . = start + 0x10;
    } > ROM = 0xFF
}