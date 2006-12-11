#include <ctools.h>
#include <video.h>
#include <kqueue.h>
struct console CON;
// struct font FON;
extern char default_font[];
void parse_csi(char** str, char* action, int vals[16], int* nread);
static int gattr;
extern volatile unsigned char* vmem;
//extern struct font default_font[];
int scroll_p;
//void init_vga();
void* get_vmem_base () {
	char gc6;
	outb (GRAPHICS_ADDR_REG, 0x06);
	gc6 = inb (GRAPHICS_DATA_REG);

	switch ( (gc6 >> 2) & 0x03) {
		case 0:
		case 1:
			return (void*)0xA0000;
			break;
		case 2:
			return (void*)0xB0000;
			break;
		case 3:
			return (void*)0xB8000;
			break;
	}
	return (void*)(~0);

}
void init_con () {
//	init_vga();
	//__asm__ ("cli");
	//__asm__ ("hlt");
	//CON.cls(&CON);
	CON.bg = colors[0];
	CON.fg = colors[7];
	char seq3;
return;

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

void k_iwrite( int c, int dest) {
	char buf0[100];
	char* buf = buf0;
	memset (buf, 0, 100);
	char sign = (c < 0 ? '-':'\0');
	buf += 98;
	if (c<0)
		c = -c;
	if (c==0)
		*buf = '0';
	else {
		while (c) {
			*buf-- = (c%10) + '0';
			c /= 10;
		}
		if (sign) {
			*buf = sign;
		} else
			buf++;
	}
	k_swrite(buf,dest);
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

#define ATTR_RV 0x01

//TODO: add buffer for escape sequences
void k_swrite(char* str, int type) {
	char esc;
	static char attr=0x07;
	gattr = attr;
	static char flags = 0;
	static char in_escape = 0;
	esc=(type==OUT_STD);
	while (*str) {
	    if (esc) {
	    	
		if (*str == '\x1b' || in_escape) {
		    char action;
		    int vals[16];
		    int nread;
		    switch (in_escape) {
		    case 0:
		        str++;
			in_escape =1;
		    case 1:
		    	if (*str != '[') continue;
		    	str++; // first char of CSI
			in_escape = 2;
		    case 2:
		    	if (*str == '[') {// fn key
			    str++;
			    str++;
			    continue;
			}
		    
		   
		    parse_csi(&str, &action, vals, &nread);
		    switch (action) {
		    case 0:
		    	in_escape = 2;
		    	return;
		    case 'm':
		    	for (int i = 0; i < nread; i++) { // {{{
			    switch (vals[i]) {
			    	case 0:  CON.fg = colors[7];
					 CON.bg = colors[0];
					 CON.intense = FALSE;
					 break;
			    	case 1:	 CON.fg = colors[CON.fg.index | 0x08];
					 CON.intense = TRUE;
					 break;
				case 2:  break;
				case 3:  break;
				case 5:  //attr |= 0x80;
					 break;
				case 7:  if (!(flags & ATTR_RV)) {
						struct color tmp = CON.fg;
						CON.fg = CON.bg;
						CON.bg = tmp;
//						attr = (attr & 0x88) | ((attr << 4) & 0x70) | ((attr >> 4)& 0x7);
						flags |= ATTR_RV;
					 }
					 break;
				case 10: break;
				case 11: break;
				case 12: break;
				case 21:
				case 22: CON.fg = colors[CON.fg.index & ~0x08]; 
					 CON.intense = FALSE;
					 break;
				case 24: break;
				case 25: break; //attr &= ~0x80;
				case 27: if (flags & ATTR_RV) {
						struct color tmp;
						tmp = CON.fg;
						CON.fg = CON.bg;
						CON.bg = tmp;
						//attr = (attr & 0x88) | ((attr << 4) & 0x70) | ((attr >> 4)& 0x7);
						flags &= ~ATTR_RV;
					 }
					 break;
				// Colors {{{

				case 30: CON.fg = colors[CON.intense? 8:0]; break;
				case 31: CON.fg = colors[CON.intense?12:4]; break;
				case 32: CON.fg = colors[CON.intense?10:2]; break;
				case 33: CON.fg = colors[CON.intense?14:6]; break;
				case 34: CON.fg = colors[CON.intense? 9:1]; break;
				case 35: CON.fg = colors[CON.intense?13:5]; break;
				case 36: CON.fg = colors[CON.intense?11:3]; break;
				case 37: CON.fg = colors[CON.intense?15:7]; break;
				case 38: CON.fg = colors[CON.intense?15:7]; break;
				case 39: CON.fg = colors[CON.intense?15:7]; break;
					//(attr & 0xf8) | 0x00; break;
/*				case 31: attr = (attr & 0xf8) | 0x04; break;
				case 32: attr = (attr & 0xf8) | 0x02; break;
				case 33: attr = (attr & 0xf8) | 0x06; break;
				case 34: attr = (attr & 0xf8) | 0x01; break;
				case 35: attr = (attr & 0xf8) | 0x05; break;
				case 36: attr = (attr & 0xf8) | 0x03; break;
				case 37: attr = (attr & 0xf8) | 0x07; break;
				case 38: attr = (attr & 0xf8) | 0x07; break;
				case 39: attr = (attr & 0xf8) | 0x07; break; */
				case 40: CON.bg = colors[0]; break;
				case 41: CON.bg = colors[4]; break;
				case 42: CON.bg = colors[2]; break;
				case 43: CON.bg = colors[6]; break;
				case 44: CON.bg = colors[1]; break;
				case 45: CON.bg = colors[5]; break;
				case 46: CON.bg = colors[3]; break;
				case 47: CON.bg = colors[7]; break;
				case 49: CON.bg = colors[0]; break;
/*
				case 40: attr = (attr & 0x8f) | 0x00; break;
				case 41: attr = (attr & 0x8f) | 0x40; break;
				case 42: attr = (attr & 0x8f) | 0x20; break;
				case 43: attr = (attr & 0x8f) | 0x60; break;
				case 44: attr = (attr & 0x8f) | 0x10; break;
				case 45: attr = (attr & 0x8f) | 0x50; break;
				case 46: attr = (attr & 0x8f) | 0x30; break;
				case 47: attr = (attr & 0x8f) | 0x70; break;
				case 49: attr = (attr & 0x8f) | 0x00; break;
*/				// }}}
				default: break;
				}
			} // }}}
		    }
		    gattr = attr;
		    in_escape = 0;
		    continue;
		    }
		}
	    }
	    switch (*str){
	    	case '\n':
			CON.xpos = 0;
			CON.ypos++;
			break;
		case '\t': 
			CON.xpos = ((CON.xpos & ~0x7) + 8);
			break;
		default: CON.xpos++;
	    CON.putchar(&CON, *str);
	    }
	    CON.mv_cur(&CON);
	    str++;

	    //k_putchar(*str++, type, attr);
	}
//	set_cur (0,0,0); // update console
}
void parse_csi(char** str, char* action, int vals[16], int* nread) {
	*nread =0;
	vals[*nread] = 0;
	static struct kqueue_char_128 buf;
	//kqueue_char_128 buf2;
	static int initialized = 0;
	if (!initialized) {
		kqueue_char_128_init(&buf);
		initialized = 1;
	}
	while ((**str >= '0' && **str <= '9') || (**str == ';')) {
		buf.push(&buf,**str);
		(void)(*str)++;
	}
	if (**str != 0) {
		buf.push(&buf, **str);
		(void)(*str)++;
	} else {
		*action = 0;
		return;
	}
	char c;
	while (buf.pop(&buf,&c) == 0) {
		if (c >= '0' && c <= '9') {
			vals[*nread] = (vals[*nread] * 10) + (c - '0');
			continue;
		} else if (c == ';') {
			(void)(*nread)++;
			vals[*nread] = 0;
			continue;
		} else {
			*action = c;
			(void)(*nread)++;
			return;
		}
	}
}
void spin(unsigned long int cycles) {
	while (cycles--) {
		__asm__ ("nop");
	}
}
void k_cls() {
	//set_font();
	//unsigned volatile char* vm2;
	for (int i = 0; i < maxrow; i++) {
		for (int j = 0; j < maxcol; j++) {
			VMEM_C(j,i)[0] = ' ';
			VMEM_C(j,i)[1] = 0x07;
		}
	}
	//for (int i = 0; i < maxcol*maxrow*2; i+=2) {
	//	vmem[i] = ' ';
	//	vmem[i+1] = (unsigned char)0x07;
	//}

	// status line
	//vm2 = vmem + (maxcol_p * maxrow * 2);
	for (int s = 0; s < maxcol+1; s++) {
		VMEM_C(s,maxrow)[0] = ' ';
		VMEM_C(s,maxrow)[1] = (unsigned char)0x1f;
		//*vm2++ = ' ';
		//*vm2++ = (unsigned char)0x1f;
	}
	// scroller
	scroll_p = 0;
	for (int i = 0; i < maxrow; i++) {
		VMEM_C(maxcol, i)[0] = (unsigned char)0xB1;
		VMEM_C(maxcol, i)[1] = (unsigned char)0x70;
	}
	VMEM_C(maxcol, scroll_p + 1)[0] = (unsigned char)0xDB;
	
	VMEM_C(maxcol, 0)[0] = (unsigned char)0x1E;
	VMEM_C(maxcol, maxrow-1)[0] = (unsigned char)0x1F;
	//vm2 = vmem + (maxcol * maxrow * 2);
	VMEM_C(5,  maxrow)[0] = (unsigned char)0xb3;
	VMEM_C(11, maxrow)[0] = (unsigned char)0xb3;
	//vm2[10] = (unsigned char)0xb3;
	//vm2[20] = (unsigned char)0xb3;
}

struct color colors[] = {
	// R,G,B,idx
	{0x00, 0x00, 0x00,  0},
	{0x00, 0x00, 0xff,  1},
	{0x00, 0x80, 0x00,  2},
	{0x00, 0x80, 0x80,  3},
	{0x80, 0x00, 0x00,  4},
	{0x80, 0x00, 0x80,  5},
	{0x80, 0x80, 0x00,  6},
	{0x80, 0x80, 0x80,  7},
	{0x40, 0x40, 0x40,  8},
	{0x40, 0x40, 0xFF,  9},
	{0x00, 0xff, 0x00, 10},
	{0x00, 0xff, 0xff, 11},
	{0xff, 0x00, 0x00, 12},
	{0xff, 0x00, 0xff, 13},
	{0xff, 0xff, 0x00, 14},
	{0xff, 0xff, 0xff, 15}};
// vim: foldmethod=syntax
