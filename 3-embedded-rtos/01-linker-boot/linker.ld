
ENTRY(Reset_Handler)

MEMORY
{
    flash(rx) : ORIGIN = 0x08000000, LENGTH =   1M
    ram(wx)   : ORIGIN = 0x20000000, LENGTH = 128K
}

_stack_top = 0x20000000+128*1024;

SECTIONS
{
    . = 0;
    
    .text :
    {
        /* Startup code must go at address 0 */
        KEEP(*(.isr_vector))
        *(.text)
        . = ALIGN(4);
        *(.rodata)
        
        /* Table of global constructors, for C++ */
        . = ALIGN(4);
        __init_array_start = .;
        KEEP (*(.init_array))
        __init_array_end = .;
    } > flash

    .data :
    {
        _data = .;
        *(.data)
        . = ALIGN(8);
        _edata = .;
    } > ram AT > flash
    _etext = LOADADDR(.data);

    _bss_start = .;
    .bss :
    {
        *(.bss)
        . = ALIGN(8);
    } > ram
    _bss_end = .;

    _end = .;
}
