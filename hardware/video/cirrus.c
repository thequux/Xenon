// This is part of the GWPC module of Xenon...
//
// Covered under the MIT license
// CirrusFB driver
#include <pci.h>
#include <kalloc.h>
#define VMEM_ADDR(x,y) (((y)*(CON.xres)*3)+(x)*3)

//static unsigned char* cur; // +(1024*3*427) - 341*3 - 1;
unsigned char* lfb; // +(1024*3*427) - 341*3 - 1;
static unsigned int dflt_cur[] = {
	//shape
	// 000000_0
	// 000000_0
	0x000000fc, //  1
	0x000000fc, //  2
	0x000000fc, //  3
	0x000000fc, //  4
	0x000000fc, //  5
	0x000000fc, //  6
	0x000000fc, //  7
	0x000000fc, //  8
	0x000000fc, //  9
	0x000000fc, // 10
	0x000000fc, // 11
	0x000000fc, // 12
	0x00000000, // 13
	0x00000000, // 14
	0x00000000, // 15
	0x00000000, // 16
	0x00000000, // 17
	0x00000000, // 18
	0x00000000, // 19
	0x00000000, // 20
	0x00000000, // 21
	0x00000000, // 22
	0x00000000, // 23
	0x00000000, // 24
	0x00000000, // 25
	0x00000000, // 26
	0x00000000, // 27
	0x00000000, // 28
	0x00000000, // 29
	0x00000000, // 30
	0x00000000, // 31
	0x00000000, // 32
	//mask
	0x00000000, //  1
	0x00000000, //  2
	0x00000000, //  3
	0x00000000, //  4
	0x00000000, //  5
	0x00000000, //  6
	0x00000000, //  7
	0x00000000, //  8
	0x00000000, //  9
	0x00000000, // 10
	0x00000000, // 11
	0x00000000, // 12
	0x00000000, // 13
	0x00000000, // 14
	0x00000000, // 15
	0x00000000, // 16
	0x00000000, // 17
	0x00000000, // 18
	0x00000000, // 19
	0x00000000, // 20
	0x00000000, // 21
	0x00000000, // 22
	0x00000000, // 23
	0x00000000, // 24
	0x00000000, // 25
	0x00000000, // 26
	0x00000000, // 27
	0x00000000, // 28
	0x00000000, // 29
	0x00000000, // 30
	0x00000000, // 31
	0x00000000 // 32
};	
//static struct color bgcolor, fgcolor;

//#define GRAPHICS_ADDR_REG	0x3CE
//#define GRAPHICS_DATA_REG	0x3CF
//#define SEQ_ADDR_REG		0x3C4
//#define SEQ_DATA_REG		0x3C5
//#define CRTC_ADDR_REG		0x3D4
//#define CRTC_DATA_REG		0X3D5
#define vga_write_misc(a,d) outb(a,d)
#include <ctools.h>
#include <video.h>

// Tools for ROPs (raster operation)
#define ROP_fg_base		0x01
#define ROP_bg_base		0x00

inline void ROP_setrgb_08(int base, int rgb) {
	outb(base, rgb & 0xff);
}
inline void ROP_setrgb_16(int base, int rgb) {
	outb(base, rgb & 0xff);
	outb(base+0x10, ((rgb) >>  8) & 0xff);
}
inline void ROP_setrgb_24(int base, int rgb) {
	outb(base, rgb & 0xff);
	outb(base+0x10, ((rgb) >>  8) & 0xff);
	outb(base+0x12, ((rgb) >> 16) & 0xff);
}
inline void ROP_setrgb_32(int base, int rgb) {
	outb(base, rgb & 0xff);
	outb(base+0x10, ((rgb) >>  8) & 0xff);
	outb(base+0x12, ((rgb) >> 16) & 0xff);
	outb(base+0x14, ((rgb) >> 24) & 0xff);
}
#define ROP_setrgb_08_qux(base,rgb)	outb(base,	((rgb)      ) & 0xff)
#define ROP_setrgb_16_qux(base,rgb)	ROP_setrgb_08_qux(base,rgb); \
	 				outb(base+0x10, ((rgb) >>  8) & 0xff)
#define ROP_setrgb_24_qux(base,rgb)	ROP_setrgb_16_qux(base,rgb); \
					outb(base+0x12, ((rgb) >> 16) & 0xff)
#define ROP_setrgb_32_qux(base,rgb)	ROP_setrgb_24_qux(base,rgb); \
					outb(base+0x14, ((rgb) >> 24) & 0xff)

static int cur_x, cur_y;

void vga_write_hdr (unsigned char val){
	unsigned char dummy;
	outb (0x3c6, 0x00);
	outb (0x3c6, 0xff);
	inb(0x3c6);
	inb(0x3c6);
	inb(0x3c6);
	inb(0x3c6);
	outb(0x3c6, val);
	inb(0x3c8);
	return;
	
	outb (0x3c6, 0x00);
	spin(400);
	dummy = inb (0x3c8);
	spin(400);
	dummy = inb (0x3c6);
	spin(400);
	dummy = inb (0x3c6);
	spin(400);
	dummy = inb (0x3c6);
	spin(400);
	dummy = inb (0x3c6);
	spin(400);

	outb(0x3c6, val);
}

void init_chip() {
	outb (CRTC_ADDR_REG, 0x11);
	outb (CRTC_DATA_REG, 0x69);
	vga_write_crt(0x51, 0x00);
	spin(100);
	vga_write_gfx(0x2f, 0x00);
	vga_write_gfx(0x33, 0x00);
	vga_write_gfx(0x31, 0x00);
	outb (0x4ce8, 0x10);
	outb (0x102, 0x01);
	outb (0x4ce8, 0x08);
	outb (0x3c3, 0x01);
	vga_write_seq(0x00, 0x03);
	vga_write_seq(0x01, 0x21);
	outb (0x3c2, 0xc1);
	vga_write_seq(0x06, 0x12); // unlock
	vga_write_gfx(0x31, 0x04);
	vga_write_seq(0x15, 0x04); // 4 megs
	vga_write_seq(0x0f, 0x98); // who knows? DRAM, according to qemu
	vga_write_seq(0x02, 0xff);
	vga_write_seq(0x03, 0x00);
	vga_write_seq(0x04, 0x0e);
	vga_write_seq(0x07, 0x20);

	vga_write_seq(0x10, 0x00); // graphics cursor X
	vga_write_seq(0x11, 0x00);
	vga_write_seq(0x12, 0x00);
	vga_write_seq(0x13, 0x00);

	vga_write_crt(0x08, 0x00);
	vga_write_crt(0x0a, 0x20);
	vga_write_crt(0x0b, 0x00);
	vga_write_crt(0x0c, 0x00);
	vga_write_crt(0x0d, 0x00);
	vga_write_crt(0x0e, 0x00);
	vga_write_crt(0x0f, 0x00);

	vga_write_crt(0x14, 0x00);
	vga_write_crt(0x17, 0xc3);
	vga_write_crt(0x18, 0x00);
	vga_write_crt(0x1b, 0x02);

	vga_write_gfx(0x00, 0x00);
	vga_write_gfx(0x01, 0x00);
	vga_write_gfx(0x02, 0x00);
	vga_write_gfx(0x03, 0x00);
	vga_write_gfx(0x04, 0x00);
	vga_write_gfx(0x05, 0x00);
	vga_write_gfx(0x06, 0x01);
	vga_write_gfx(0x07, 0x0f);
	vga_write_gfx(0x08, 0xff);
	vga_write_gfx(0x0b, 0x28);
	vga_write_gfx(0x0c, 0xff);
	vga_write_gfx(0x0d, 0x00);
	vga_write_gfx(0x0e, 0x00);

	vga_write_att(0x00, 0x00);
	vga_write_att(0x01, 0x01);
	vga_write_att(0x02, 0x02);
	vga_write_att(0x03, 0x03);
	vga_write_att(0x04, 0x04);
	vga_write_att(0x05, 0x05);
	vga_write_att(0x06, 0x06);
	vga_write_att(0x07, 0x07);
	vga_write_att(0x08, 0x08);
	vga_write_att(0x09, 0x09);
	vga_write_att(0x0a, 0x0a);
	vga_write_att(0x0b, 0x0b);
	vga_write_att(0x0c, 0x0c);
	vga_write_att(0x0d, 0x0d);
	vga_write_att(0x0e, 0x0e);
	vga_write_att(0x0f, 0x0f);
	vga_write_att(0x10, 0x01);
	vga_write_att(0x11, 0x00);
	vga_write_att(0x12, 0x0f);
	vga_write_att(0x14, 0x00);

	outb (0x3c6, 0xff);
	outb (0x3c2, 0xc3);

	vga_write_gfx(0x31, 0x04);
	vga_write_gfx(0x31, 0x00);

	vga_write_hdr(0x00);
}
static int abs(int foo) { return (foo>0)?foo:-foo;}
static void bestclock (long freq, long *best, long *nom,
                       long *den, long *div, long maxfreq)
{
        long n, h, d, f;

        *nom = 0;
        *den = 0;
        *div = 0;


        if (freq < 8000)
                freq = 8000;

        if (freq > maxfreq)
                freq = maxfreq;

        *best = 0;
        f = freq * 10;

        for (n = 32; n < 128; n++) {
                d = (143181 * n) / f;
                if ((d >= 7) && (d <= 63)) {
                        if (d > 31)
                                d = (d / 2) * 2;
                        h = (14318 * n) / d;
                        if (abs (h - freq) < abs (*best - freq)) {
                                *best = h;
                                *nom = n;
                                if (d < 32) {
                                        *den = d;
                                        *div = 0;
                                } else {
                                        *den = d / 2;
                                        *div = 1;
                                }
                        }
                }
               d = ((143181 * n) + f - 1) / f;
                if ((d >= 7) && (d <= 63)) {
                        if (d > 31)
                                d = (d / 2) * 2;
                        h = (14318 * n) / d;
                        if (abs (h - freq) < abs (*best - freq)) {
                                *best = h;
                                *nom = n;
                                if (d < 32) {
                                        *den = d;
                                        *div = 0;
                                } else {
                                        *den = d / 2;
                                        *div = 1;
                                }
                        }
                }
        }
}
int set_parm(int xres, int yres, int bpp, int refresh) {
	(void)xres;
	(void)yres;
	(void)bpp;
	(void)refresh;
	// line_length	w*3
	// max_clock	85500
	// bpp		24
	// freq		85500 KHz
	// pixClock	11695 ps
	//
	// nom		125
	// den		21
	// div		0
	// mclk		153900
	// sr1f		86
	// MCLK_final	86
	// xres -> 1024
	int nom;
	switch (bpp) {
	case 16: nom = 2; break;
	case 24: nom = 3; break;
	//case 32: nom = 4; break;
	default: printf("mode %dx%dx%d rejected: invalid depth\n", xres, yres, bpp); return -1;
	}
	// assume max of 4M of video mem...
	if (xres * nom * yres > 0x400000) {
		printf("mode %dx%dx%d too large to fit in video mem\n", xres, yres, bpp);
	}
	// Parameters checked... update CON
	switch (bpp) {
	case 16:  CON.bpp = 16;
		  CON.roff = 10; CON.rlen = 5;
		  CON.goff = 5;  CON.glen = 5;
		  CON.boff = 0;  CON.blen = 5;
		  break;
	case 24:
	case 32:  CON.bpp = bpp;
		  CON.roff = 16; CON.rlen = 8;
		  CON.goff = 8;  CON.glen = 8;
		  CON.boff = 0;  CON.blen = 8;
		  break;
	}
	CON.yres = yres;
	CON.xres = xres;
	CON.llen = xres * nom;

	struct mode vmode = calc_gtf(xres, yres, refresh);
//	           1000000
	int freq = 1000000 / vmode.pclk;
	int maxclock = 85500; // nom = 2 or 3.
	if (freq > maxclock) {
		printf ("frequncy too great\n");
		return -1;
	}
	long rfreq, rnom, rden, rdiv, rmclk_div;
	bestclock(freq, &rfreq, &rnom, &rden, &rdiv, maxclock);
	// 928
	long mclk;
	mclk = ((((bpp / 8) * freq * 2) / 4) * 12) / 10;
	if (mclk < 50000) mclk = 50000;

	mclk = (((mclk * 16) / 14318)+1)/2;
	switch (freq) {
        case 24751 ... 25249:
                rmclk_div = 2;
                break;
        case 49501 ... 50499:
                rmclk_div = 1;
		break;
        default:
                rmclk_div = 0;
                break;
        }
	vga_write_crt(0x11, 0x20); // is this correct? VGADOC says 0x40
	vga_write_crt(0x00,vmode.hfl / 8 - 5);
	vga_write_crt(0x01,xres / 8 - 1);
	vga_write_crt(0x02,xres / 8);
	vga_write_crt(0x03,128+((vmode.hfl / 8)&32));
	vga_write_crt(0x04,vmode.hss);
	vga_write_crt(0x05,(vmode.hse & 31) + (((vmode.hfl / 8)&32)?128:0));
	vga_write_crt(0x06,(vmode.vfl - 2)&0xff);
	char tmp = 16;
	if ((vmode.vfl-2)&256) tmp |= 1;
	if ((yres-1)    &256) tmp |= 2;
	if ((vmode.vss-1)&256) tmp |= 4;
	if ((vmode.vse-1)&256) tmp |= 8;
	if ((vmode.vfl-2)&512) tmp |= 32;
	if ((vmode.vss-1)&512) tmp |= 64;
	if ((vmode.vse-1)&512) tmp |= 128;
	vga_write_crt(0x07,tmp);
	
	tmp = 0x40;
	if (yres & 512) tmp |= 0x20;
	vga_write_crt(0x09,tmp);
	vga_write_crt(0x10,(vmode.vss-1)&0xff);
	vga_write_crt(0x11,((vmode.vse-1) & 0x15) + 32 + 64);
	vga_write_crt(0x12,(yres-1)&0xff);
	
	vga_write_crt(0x15,yres & 0xff);
	vga_write_crt(0x16,(vmode.vfl-2)&0xff);
	vga_write_crt(0x18,0xff);
	tmp = 0;
	tmp |= (vmode.hfl / 4) & 0x30;
	tmp |= ((vmode.vfl-2)/4) & 0xc0;
	vga_write_crt(0x1A,tmp);
	vga_write_seq(0x0b,rnom);
	vga_write_seq(0x1B,(rden << 1)| ((rdiv != 0)?1:0));
	vga_write_crt(0x17,(yres>= 1024)?0xc7:0xc3);
	vga_write_crt(0x19,0x00);
	vga_write_seq(0x03,0x00);
	vga_write_misc(0x3c2,0x83);
	vga_write_crt(0x08,0x00);
	vga_write_crt(0x0a,0x00);
	vga_write_crt(0x0b,0x1f);
	if (bpp == 16) {
		vga_write_seq(0x07,0x27);
		vga_write_hdr(0xc0);
	} else {
		vga_write_seq(0x07, 0x25);
		vga_write_hdr(0xc5);
	}
	int offset = xres *3/ 8;
	CON.offset = offset;
	vga_write_gfx(0x05,0x64);
	vga_write_misc(0x3c6,0xff);
	vga_write_seq(0x02,0x0a);
	vga_write_seq(0x04,0xff);

	//vga_write_crt(0x13,0x00);
	//vga_write_crt(0x1B,0x22 ); // was 0x3b
	vga_write_crt(0x13,(offset & 0xff) | 0x00);
	vga_write_crt(0x1B,0x2b | ((offset & 0x100)?0x10:0) ); // was 0x3b
	vga_write_crt(0x1D,0x00);
	vga_write_crt(0x0e,0x00);
	vga_write_crt(0x0f,0x00);
	vga_write_crt(0x14,0x00);
	vga_write_att(0x10,0x01);
	vga_write_att(0x11,0x00);
	vga_write_att(0x12,0x0f);
	vga_write_att(0x33,0x00);
	vga_write_att(0x14,0x00);
	//attr_on();
	vga_write_gfx(0x00,0x00);
	vga_write_gfx(0x01,0x00);
	vga_write_gfx(0x02,0x00);
	vga_write_gfx(0x03,0x00);
	vga_write_gfx(0x04,0x00);
	vga_write_gfx(0x06,0x01);
	vga_write_gfx(0x07,0x0f);
	vga_write_gfx(0x08,0xff);
	vga_write_seq(0x12,0x00);
	vga_write_seq(0x01,0x01);
	return 0;
}

/*void disp_char(uchar val) ;
void cirrus_write (struct console* THIS, char* buf, int len) {
	(void)THIS;
	(void)buf;
	(void)len;
	for (int i = 0; i < len; i++) {
		disp_char(buf[i]);
	}
}*/
static void draw_cursor (int x, int y, int w, int h) {
	for (int j = 0; j<h; j++) {
		unsigned char* buf = lfb+VMEM_ADDR(x,j+y);
		for (int i = 0; i < w; i++) {
			*buf ^= 0xff;
			buf++;
			*buf ^= 0xff;
			buf++;
			*buf ^= 0xff;
			buf++;
		}
	}
}
static void mv_cur (struct console* THIS) {
	// make sure hardware cursor is on...
	
	vga_write_seq (0x12, 0x01);
	vga_write_seq (0x13, 0x00);
	int xpos = (THIS->xpos) * font->w;
	int ypos = (THIS->ypos-1) * (font->h-1) + font->h - 2;

	vga_write_seq (0x10 | (xpos & 0x07) << 5, (xpos >> 3) & 0xff);
	vga_write_seq (0x11 | ((ypos & 0x07) << 5), (ypos >> 3) & 0xff);
	return;
	draw_cursor ((THIS->old_xpos+1) * (font->w)- 1,
		     (THIS->old_ypos )* (font->h-1),
		     1,
		     font->h-1);
	draw_cursor ((THIS->xpos+1) * (font->w) - 1,
	             (THIS->ypos) * (font->h-1),
		     1,
		     font->h-1);
	THIS->old_xpos = THIS->xpos;
	THIS->old_ypos = THIS->ypos;
}

void cirrus_cls (struct console* THIS) {
	(void)THIS;
#if 1
	// Cirrus ROP
	//
	outb (GRAPHICS_ADDR_REG, 0x31);
	while (inb(GRAPHICS_DATA_REG)&0x08)
		/*do nothing */;
	// pitch = line length
	vga_write_gfx (0x24, (THIS->xres*3) & 0xff);
	vga_write_gfx (0x25, (THIS->xres*3)>>8);
	vga_write_gfx (0x26, (THIS->xres*3) & 0xff);
	vga_write_gfx (0x27, (THIS->xres*3)>>8);

	// num of pixels -1
	vga_write_gfx (0x20, (THIS->xres*3-1)&0xff);
	vga_write_gfx (0x21, (THIS->xres*3-1)>>8);

	vga_write_gfx (0x22, (THIS->yres-1)&0xff);
	vga_write_gfx (0x23, (THIS->yres-1)>>8);

	vga_write_gfx (0x28, 0x00);
	vga_write_gfx (0x29, 0x00);
	vga_write_gfx (0x2a, 0x14);
	
	vga_write_gfx (0x2c, 0x00);
	vga_write_gfx (0x2d, 0x00);
	vga_write_gfx (0x2e, 0x00);

	vga_write_gfx (0x00, 0x00);
	vga_write_gfx (0x00, 0x01); // color

	vga_write_gfx (0x30, 0xc0);
	vga_write_gfx (0x32, 0x0d);
	vga_write_gfx (0x31, 0x02);
#else
	for (long int i = 0; i < CON.xres * CON.yres * 3; i++) {
		lfb[i] =  0;
	}
#endif
	THIS->xpos = 0;
	THIS->ypos = 0;
	// draw the chrome
/*	int bbar[] = {
		0x050d15,
		0x1a2229,
		0x2c333a,
		0x51575f,
		0x645a57,
		0x526072,
		0x4e6a88,
		0x8b99c1,
		0xacb2cb,
		0xe7e1c8,
		0xe6e2ce,
		0xd3d4d6
		};*/
	int bbar2[] = {
		0x6e6e7a,
		0xfafafc,
		0xf6f6f8,
		0xebecf1,
		0xdfdfe9,
		0xd8dbe4,
		0xb6b8c4,
		0xb7b9c5,
		0xbabcc9,
		0xc5c7d3,
		0xcaccd8,
		0xcbced7
		};
	int beg = THIS->yres - 12;
	for (int y = beg; y < beg+13; y++) {
		uchar* vmem_l = lfb+VMEM_ADDR(0,y);
		for (int x = 0; x < THIS->xres; x++) {
			*vmem_l++ =  bbar2[y-beg] & 0xff;
			*vmem_l++ = (bbar2[y-beg] >> 8) & 0xff;
			*vmem_l++ = (bbar2[y-beg] >> 16) & 0xff;
		}
	}
}

static void disp_char(struct console *THIS, uchar val) {
	int off_x = THIS->xpos * font->w;
	int off_y = THIS->ypos * (font->h-1);
	uchar* off_addr = lfb + VMEM_ADDR(off_x, off_y);
	(void)off_addr;
	(void)val;
	int b = 0;
	unsigned char* glyph = font->glyphs+(font->glyph_size * val);
	for (int i = 0; i < font->h; i++) {
		unsigned char c = glyph[b];
		for (int j = 0; j < font->w; j++) {
			if (j%8 == 0){
				c = glyph[b++];
			}
			if (c & 0x80) {
				*off_addr++ = THIS->fg.b;
				*off_addr++ = THIS->fg.g;
				*off_addr++ = THIS->fg.r;
			} else {
				*off_addr++ = THIS->bg.b;
				*off_addr++ = THIS->bg.g;
				*off_addr++ = THIS->bg.r;
			}
			c <<= 1;
		}
		off_addr = lfb + VMEM_ADDR(off_x, off_y++);
	}
}
void gee_whiz();
void init_vga() {
	char pal[] = {0x00, 0x00, 0x00, 0xff, 0xff, 0xff};
	init_chip();
	//set_parm(1024,768,24,60);
	set_parm(1024,768,24,60);
	//set_parm(800,600,24,60);

      pginfo.dir[1022].base = 0xe0000000 >> 12;
      pginfo.dir[1022].g = 0;
      pginfo.dir[1022].ps = 1;
      pginfo.dir[1022].pwt = 1;
      pginfo.dir[1022].w = 1;
      pginfo.dir[1022].p = 1;
      asm volatile ("pushl %ecx\n\tmovl %cr3, %ecx\n\tmovl %ecx, %cr3\n\tpopl %ecx");
	lfb =  ((unsigned char*)0xff800000)  + 0x140000; // +(1024*3*427) - 341*3 - 1;
	
	//setup cursor
	vga_write_seq (0x12, 0x02);
	vga_write_pel (0x00, 0x00, pal);
	vga_write_pel (0x0f, 0x0f, pal+3);
	vga_write_att (0x00, 0x00);
	vga_write_att (0x0f, 0xff);
	vga_write_seq (0x12, 0x01);
	memcpy(((unsigned char*)0xffbfc000), dflt_cur, 256);
	cur_x = 0;
	CON.xpos = 0;
	CON.ypos = 0;
	cur_y = 0;
	CON.read = NULL;
//	CON.write = cirrus_write;
	CON.putchar = disp_char;
	CON.cls = cirrus_cls;
	CON.mv_cur = mv_cur;

	CON.cls(&CON);

	draw_cursor ((font->w - 2),
		     0,
		     2,
		     font->h+1);

	//gee_whiz();
}

static void cirrus_init_pci (struct pci_dev *dev) {
	init_vga();
	CON.cls(&CON);
	(void)dev;
//	printf ("CIRRUSFB: %d:%d.%d\n", dev->bus, dev->slot, dev->func);
}
static struct pci_driver cirrus_drv[] __attribute__((unused))= {
	{0x1013,0x00b8,cirrus_init_pci},
	{0,0,NULL},
};
static void cirrus_init(void) {
	register_pci_driver(cirrus_drv);
}
REGISTER_INIT(cirrus_init);
