#include <ctools.h>
#include <video.h>
#include <kqueue.h>
struct console CON;
// struct font FON;
extern char default_font[];
static int gattr;
extern volatile unsigned char* vmem;
//extern struct font default_font[];
char parse_csi(char in, struct CSI *status);
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
	CON.esc = FALSE;
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


#define ATTR_RV 0x01

//TODO: add buffer for escape sequences
void k_swrite(char* str, int type) { // {{{
	char esc;
	static char attr=0x07;
	gattr = attr;
	static char flags = 0;
//	static char in_escape = 0;
	esc=(type==OUT_STD);

	while (*str) {
	    if (esc) {
		char chr;
		switch (chr =  parse_csi(*str, &CON.csibuf)) {
	    	case 0:
		    break;
		case 1:
		    switch (CON.csibuf.term) {
		    case 'm':
		    	for (int i = 0; i < CON.csibuf.nv; i++) { // {{{
			    switch (CON.csibuf.vals[i]) {
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
		    break;
	    	case '\n':
			CON.xpos = 0;
			CON.ypos++;
			break;
		case '\t': 
			CON.xpos = ((CON.xpos & ~0x7) + 8);
			break;
		default: CON.xpos++;
			 CON.putchar(&CON, *str);
			 break;
	    	}
	        CON.mv_cur(&CON);
	    } 
		//k_putchar(*str++, type, attr);
	    str++;
	}
//	set_cur (0,0,0); // update console
} // }}}
// returns the character to output, or 
// 	0 if none.
// 	1 if end of CSI.
char parse_csi(char in, struct CSI *status) {
	if (in == '\x1b') {
		status->esc = TRUE;
		status->pos = '\x1b';
		return 0;
	}
	if (in == 0x18 || in == 0x1b) {
		status->esc=FALSE;
	}
	if (!status->esc && in != '\x1b')
		return in;
switch (status->pos) { // {{{
	case '\x1b':
		if (in != '[')
			status->esc = FALSE;
		else
			status->pos='[';
		return 0;
	case '[':
		switch (in) {
			case '\x1b':
				status->esc = TRUE;
				status->pos = '\x1b';
				status->nv = 0;
				status->vals[0] = 0;
				return 0;
			case 0x00:
				return 0;
			case 0x18:
			case 0x1a:
				status->esc = FALSE;
				return 0;
			case '0' ... '9':
				status->vals[status->nv] = status->vals[status->nv] * 10 + in - '0';
				return 0;
			case ';':
				status->nv++;
				status->vals[status->nv] = 0;
				return 0;
			default:
				status->nv++;
				status->term = in;
				status->esc = FALSE;
				return 1;
		}
		break;
} // }}}
return 2;
}
//{{{
void spin(unsigned long int cycles) {
	while (cycles--) {
		__asm__ ("nop");
	}
}
//}}}
//{{{
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
	
//}}}
// vim: foldmethod=marker
