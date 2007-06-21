SECTIONS
{
    . = 0xC0100000;
    .mbheader ALIGN (0x04) :  AT(ADDR(.mbheader) -0xC0000000)
    {
    	*(.mbheader)
    }
    .text : AT(ADDR(.text) - 0xC0000000)
    {
        *(.text)
    }

    .initcall : AT(ADDR(.initcall) - 0xC0000000)
    {
    	_init_start = .;
	*(.initcall);
	_init_end = .;
    }
    .rodata ALIGN (0x1000) :  AT(ADDR(.rodata) - 0xC0000000)
    {
        *(.rodata)
    }

    .data ALIGN (0x1000) :  AT(ADDR(.data) - 0xC0000000)
    {
        *(.data)
    }

    .bss ALIGN(0x1000) :  AT(ADDR(.bss) - 0xC0000000)
    {
        _sbss = .;
        *(.bss)
        *(COMMON)
        _ebss = .;
    }
    /DISCARD/ : {
    	*(.discard)
    }
    pginfo = 0xffc00000;
}
