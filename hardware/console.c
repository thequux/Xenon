#include "ctools.h"
#include "video.h"
#include "kqueue.h"
#define GRAPHICS_ADDR_REG 0x3CE
#define GRAPHICS_DATA_REG 0x3CF
#define SEQ_ADDR_REG		0x3C4
#define SEQ_DATA_REG		0x3C5

void parse_csi(char** str, char* action, int vals[16], int* nread);
static int gattr;
extern volatile unsigned char* vmem;
//extern unsigned char font[];
int scroll_p;
int vmem_base = 1;
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
	vmem = get_vmem_base();
//	k_cls();
	char seq3;
	set_font (NULL,1);
	memset((void*)vmem, 0x1f, 160);
	// make sure that planes are correct...
	outb (SEQ_ADDR_REG, 0x03);
	seq3 = inb (SEQ_DATA_REG);
	outb (SEQ_DATA_REG, 0x20);

	// set up split...
	int reg = ((inb(0x3cc)&0x01)?0x3D4:0x3B4);
	printf("%x\n",reg);

	outb (reg, 0x0d); // start_low
	outb (reg+1, 80);
	outb (reg, 0x0c); // start_high
	outb (reg+1, 0x00);

	outb (reg, 0x18);	// lc main
	outb (reg+1, 0x7f);
	
	outb (reg, 0x07);	
	char rt = inb (reg+1);
	outb (reg+1, rt | 0x10); // lc[8]

	outb (reg, 0x09);
	rt = inb (reg+1);
	outb (reg+1, rt & (~0x40)); // lc[9]
	
	char save;
	char att10;
	__asm__ ("cli");	//  for safety
		        inb (0x3da);
		save =  inb (0x3C0);
		;	outb(0x3c0, 0x10);
		att10 =	inb (0x3C1);
			outb(0x3C0, att10 &  ~0x20);
			outb(0x3C0, save);
			inb (0x3da);
	
	__asm__ ("sti");
	/*;
	//attr[0x10][5] = 1
	__asm__ ("cli\n\t"	// this is critical!
		 "pusha\n\t"
		 "movw $0x3DA, %dx\n\t"
		 "inb %dx, %al\n\t"
		 "outb %al, $0xEB\n\t"	//delay
		 "movw $0x3C0, %dx\n\t"
		 "inb %dx, %al\n\t"
		 "outb %al, $0xEB\n\t"	// delay
		 "pushw %ax\n\t"
		 "movb $0x10, %al\n\t"
		 "outb %al, $0xEB\n\t"	// delay
		 "outb %al, %dx\n\t"
		 "movw $0x3C1, %dx\n\t"
		 "outb %al, $0xEB\n\t"	// delay
		 "inb %dx, %al\n\t"
		 "or $0x20, %al\n\t"
		 "movw $0x3C0, %dx\n\t"
		 "outb %al, $0xEB\n\t"	// delay
		 "outb %al, %dx\n\t"
		 "popw %ax\n\t"
		 "outb %al, $0xEB\n\t"
		 "outb %al, %dx\n\t"	// delay
		 "popa\n\t"
		 "sti"
		 );
	*/
	k_cls();
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
	}
	if (font == NULL)
		font = (void*)seg;
	
	memcpy ((unsigned char*)seg + plane * 8192, font, 8192);
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
	static char force = 0x11;	// force write
	if (delay) {
		if (pos_cx == x && pos_cy == y)
			return; // no sense in updating!
		pos_cx = x;
		pos_cy = y;
	} else {
		int np;
		char nph, npl;
		np = (pos_cy + vmem_base) * maxcol_p + pos_cx;
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
	//int l1 = 0, l2 = lines;
	//while (l2 < maxrow) {
	//	for (int i = 0; i < maxcol * 2; i++)
	//		vmem[l1 * maxcol_p * 2 + i] = vmem[l2*maxcol_p*2 + i];
	//	l1++;
	//	l2++;
	//}

	//while (l1 < maxrow) {
	//	for (int i = 0; i < maxcol * 2; i+=2) {
	//		vmem[l1 * maxcol_p * 2 + i] = ' ';
	//		vmem[l1 * maxcol_p * 2 + i+1] = 0x07;
	//	}
	//	l1 ++;
	//}
	int reg = ((inb(0x3cc)&0x01)?0x3D4:0x3B4);
	vmem_base += lines - 1;
	vmem_base %= 199;
	vmem_base++;
	int vm2 = vmem_base * 80;
	scroll_p += lines;
	outb (reg, 0x0d); // start_low
	outb (reg+1, vm2 & 0xff);
	outb (reg, 0x0c); // start_high
	outb (reg+1, (vm2 & 0xff00) >> 8);


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

void k_putchar(char c, int type, char code) {
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
				VMEM_C(x,y)[1] = (unsigned char)code;
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
			    	case 0:  attr = 0x07;
					 break;
			    	case 1:	 attr |= 0x08;
					 break;
				case 2:  break;
				case 3:  break;
				case 5:  attr |= 0x80;
				case 7:  if (!(flags & ATTR_RV)) {
						attr = (attr & 0x88) | ((attr << 4) & 0x70) | ((attr >> 4)& 0x7);
						flags |= ATTR_RV;
					 }
					 break;
				case 10: break;
				case 11: break;
				case 12: break;
				case 21:
				case 22: attr &= ~0x08;
					 break;
				case 24: break;
				case 25: attr &= ~0x80;
				case 27: if (flags & ATTR_RV) {
						attr = (attr & 0x88) | ((attr << 4) & 0x70) | ((attr >> 4)& 0x7);
						flags &= ~ATTR_RV;
					 }
					 break;
				// Colors {{{
				case 30: attr = (attr & 0xf8) | 0x00; break;
				case 31: attr = (attr & 0xf8) | 0x04; break;
				case 32: attr = (attr & 0xf8) | 0x02; break;
				case 33: attr = (attr & 0xf8) | 0x06; break;
				case 34: attr = (attr & 0xf8) | 0x01; break;
				case 35: attr = (attr & 0xf8) | 0x05; break;
				case 36: attr = (attr & 0xf8) | 0x03; break;
				case 37: attr = (attr & 0xf8) | 0x07; break;
				case 38: attr = (attr & 0xf8) | 0x07; break;
				case 39: attr = (attr & 0xf8) | 0x07; break;

				case 40: attr = (attr & 0x8f) | 0x00; break;
				case 41: attr = (attr & 0x8f) | 0x40; break;
				case 42: attr = (attr & 0x8f) | 0x20; break;
				case 43: attr = (attr & 0x8f) | 0x60; break;
				case 44: attr = (attr & 0x8f) | 0x10; break;
				case 45: attr = (attr & 0x8f) | 0x50; break;
				case 46: attr = (attr & 0x8f) | 0x30; break;
				case 47: attr = (attr & 0x8f) | 0x70; break;
				case 49: attr = (attr & 0x8f) | 0x00; break;
				// }}}
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
	    k_putchar(*str++, type, attr);
	}
	set_cur (0,0,0); // update console
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
	// should be at 0
	for (int s = 0; s < maxcol+1; s++) {
		vmem[s*2] = ' ';
		vmem[s*2 + 1] = (unsigned char) 0x1f;
		//VMEM_C(s,-1)[0] = ' ';
		//VMEM_C(s,-1)[1] = (unsigned char)0x1f;
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
	vmem[10] =  (unsigned char)0xb3;
	vmem[22] = (unsigned char) 0xb3;
	VMEM_C(5,  -1)[0] = (unsigned char)0xb3;
	VMEM_C(11, -1)[0] = (unsigned char)0xb3;
	//vm2[10] = (unsigned char)0xb3;
	//vm2[20] = (unsigned char)0xb3;
}
// vim: foldmethod=syntax
