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
