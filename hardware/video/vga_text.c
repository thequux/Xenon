#include <ctools.h>
#include <video.h>


static void init_vga_text() {
	set_font (default_font,0);
	set_font (default_font,1);
	// make sure that planes are correct...
	outb (SEQ_ADDR_REG, 0x03);
	seq3 = inb (SEQ_DATA_REG);
	outb (SEQ_DATA_REG, 0x20);
}

void set_font(void* font, int plane) {
	unsigned int seg;
	char seq4, seq2, gc4, gc5, gc6;
	outb(SEQ_ADDR_REG, 0x04);
	seq4 = inb (SEQ_DATA_REG);
	outb(SEQ_DATA_REG, seq4 | 0x04);

	outb (SEQ_ADDR_REG, 0x02);
	seq2 = inb (SEQ_DATA_REG);
	outb(SEQ_DATA_REG, 0x04); // write plane 2
	
	outb (GRAPHICS_ADDR_REG, 0x04);
	gc4 = inb (GRAPHICS_DATA_REG);
	outb (GRAPHICS_DATA_REG, 0x02); // read plane 2

	outb (GRAPHICS_ADDR_REG, 0x05);
	gc5 = inb (GRAPHICS_DATA_REG);
	outb (GRAPHICS_DATA_REG, gc5 & ~0x1b); //turn off even/odd.

	outb (GRAPHICS_ADDR_REG, 0x06);
	gc6 = inb (GRAPHICS_DATA_REG);
	outb (GRAPHICS_DATA_REG, gc6 & ~0x02);


	//Where is the graphics segment?
	switch ( (gc6 >> 2) & 0x03) {
		case 0:
		case 1:
			seg = 0xA0000;
			break;
		case 2:
			seg = 0xB0000;
			break;
		case 3:
			seg = 0xB8000;
			break;
		default:
			k_swrite("VIDEO SEGMENT ERROR", OUT_STD);
			panic();
			seg = 0;
	}
	if (font == NULL)
		font = (void*)seg;
	
	memcpy ((unsigned char*)seg + plane * 8192, font, 8192);
	
	// Set height
	outb (CRTC_ADDR_REG, 0x09);
	unsigned char msl = inb (CRTC_DATA_REG);
	outb (CRTC_DATA_REG, (msl & 0xe0) | 11);
	
	outb (SEQ_ADDR_REG, 0x01);
	outb (SEQ_DATA_REG, inb(SEQ_DATA_REG | 0x01));
	//restore regs.
	outb (SEQ_ADDR_REG, 0x02);
	outb (SEQ_DATA_REG, seq2);

	outb (SEQ_ADDR_REG, 0x04);
	outb (SEQ_DATA_REG, seq4);

	outb (GRAPHICS_ADDR_REG, 0x04);
	outb (GRAPHICS_DATA_REG, gc4);

	outb (GRAPHICS_ADDR_REG, 0x05);
	outb (GRAPHICS_DATA_REG, gc5);

	outb (GRAPHICS_ADDR_REG, 0x06);
	outb (GRAPHICS_DATA_REG, gc6);
	//printf ("  %x->%x\n", font, (char*)seg + plane * 8192);
}

void set_cur (int x, int y, char delay) {
	// if delay is non-zero, just cache position; do not access hardware
	// If delay is 0, update console from cache only.
	static char pos_hi=0, pos_lo=0; // data written to console
	static char pos_cx=0, pos_cy=0; // data cached
	static char up = 1;		// new data
	static char force = 0x11;	// force write
	if (delay) {
		if (pos_cx == x && pos_cy == y)
			return; // no sense in updating!
		pos_cx = x;
		pos_cy = y;
		up = 1;
	} else {
		if (!force && !up)
			return;
		up = 0;
		int np;
		char nph, npl;
		np = pos_cy * maxcol_p + pos_cx;
		nph = ((np & 0xff00) >> 8);
		npl = np & 0xff;
		if (nph ^ pos_hi)
			force |= 0x10;
		if (npl ^ pos_lo)
			force |= 0x01;
		pos_lo = npl;
		pos_hi = nph;

		if (!force)
			return; // no updates!
		int reg = ((inb(0x3cc)&0x01)?0x3D4:0x3B4);
		if (force & 0x01) {
			outb (reg, 0x0f);
			outb (reg+1, pos_lo);
		}
		if (force & 0x10) {
			outb (reg, 0x0e);
			outb (reg+1, pos_hi);
		}
		force = 0;
	}
}
void scroll(int lines) {
	int l1 = 0, l2 = lines;
	while (l2 < maxrow) {
		for (int i = 0; i < maxcol * 2; i++)
			vmem[l1 * maxcol_p * 2 + i] = vmem[l2*maxcol_p*2 + i];
		l1++;
		l2++;
	}

	while (l1 < maxrow) {
		for (int i = 0; i < maxcol * 2; i+=2) {
			vmem[l1 * maxcol_p * 2 + i] = ' ';
			vmem[l1 * maxcol_p * 2 + i+1] = 0x07;
		}
		l1 ++;
	}

	VMEM_C(maxcol, scroll_p+1)[0] = (unsigned char)0xb1;
	scroll_p += lines;
	VMEM_C(maxcol, scroll_p+1)[0] = (unsigned char)0xDB;
	
}
void k_putchar_vga(char c, int type, char attr) {
	static int x = 0;
	static int y = 0;
	
	if (type == OUT_DBG) {
		dbg(c);
	} else if (type == OUT_STD) {
		switch (c) {
			case '\n':
				y += 1;
				x  = 0;
				if (y == maxrow) {
					scroll(1);
					y--;
				}
				set_cur(x,y,1);
				return;
			default:
				//p = (y * maxcol + x) << 1;
				VMEM_C(x,y)[1] = (unsigned char)attr;
				VMEM_C(x,y)[0] = c;
				x++;
				if (x == maxcol) {
					x = 0;
					y++;
				}
				if (y == maxrow) {
					scroll (1);
					y--;
				}
				set_cur (x,y,1);
				break;
		}
	}
}
REGISTER_INIT(init_vga_text);
