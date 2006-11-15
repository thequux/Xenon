SECTIONS
{
    . = 0x00100000;
    .mbheader ALIGN (0x04) :
    {
    	*(.mbheader)
    }
    .text :
    {
        *(.text)
    }

    .rodata ALIGN (0x1000) :
    {
        *(.rodata)
    }

    .data ALIGN (0x1000) :
    {
        *(.data)
    }

    .bss :
    {
        _sbss = .;
        *(COMMON)
        *(.bss)
        _ebss = .;
    }
}
