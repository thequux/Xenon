TARGET(elf_i386);
SECTIONS
{
	. = 0x100 ;
	.text : {
		*(.text)
	}
	/DISCARD/ :
	{
		*(.discard)
	}
}
