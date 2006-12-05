// This is part of the GWPC module of Xenon...
//
// Covered under the MIT license
// CirrusFB driver
/*
                .var    = {
                        .xres           = 800,
                        .yres           = 600,
                        .xres_virtual   = 800,
                        .yres_virtual   = 600,
                        .bits_per_pixel = 8,
                        .red            = { .length = 8 },
                        .green          = { .length = 8 },
                        .blue           = { .length = 8 },
                        .width          = -1,
                        .height         = -1,
                        .pixclock       = 20000,
                        .left_margin    = 128,
                        .right_margin   = 16,
                        .upper_margin   = 24,
                        .lower_margin   = 2,
                        .hsync_len      = 96,
                        .vsync_len      = 6,
                        .vmode          = FB_VMODE_NONINTERLACED
                 }
*/
#define VMEM_ADDR(x,y) (((y)*1024*3)+(x)*3)

//static unsigned char* cur; // +(1024*3*427) - 341*3 - 1;
static unsigned char* lfb; // +(1024*3*427) - 341*3 - 1;
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
void set_parm(int w, int h, int bpp) {
	(void)w;
	(void)h;
	(void)bpp;
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
	vga_write_crt(0x00,0xA3);
	vga_write_crt(0x01,0x7F);
	vga_write_crt(0x02,0x80);
	vga_write_crt(0x03,0x88);
	vga_write_crt(0x04,0x84);
	vga_write_crt(0x05,0x95);
	vga_write_crt(0x06,0x24);
	vga_write_crt(0x07,0xFD);
	
	vga_write_crt(0x09,0x60);
	vga_write_crt(0x10,0x02);
	vga_write_crt(0x11,0x69);
	vga_write_crt(0x12,0xFF);
	
	vga_write_crt(0x15,0x00);
	vga_write_crt(0x16,0x24);
	vga_write_crt(0x18,0xff);
	vga_write_crt(0x1A,0xC0);
	vga_write_seq(0x0b,0x7d);
	vga_write_seq(0x1B,0x2A);
	vga_write_crt(0x17,0xc3);
	vga_write_crt(0x19,0x00);
	vga_write_seq(0x03,0x00);
	vga_write_misc(0x3c2,0x03);
	vga_write_crt(0x08,0x00);
	vga_write_crt(0x0a,0x00);
	vga_write_crt(0x0b,0x1f);
	vga_write_seq(0x07,0x25);
	vga_write_gfx(0x05,0x64);
	vga_write_misc(0x3c6,0xff);
	vga_write_hdr(0xc5);
	vga_write_seq(0x02,0x0a);
	vga_write_seq(0x04,0xff);
	vga_write_crt(0x13,0x80);
	vga_write_crt(0x1B,0x3b);
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
	int xpos = (THIS->xpos+1) * font->w;
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
	// Cirrus ROP
	//
	outb (GRAPHICS_ADDR_REG, 0x31);
	while (inb(GRAPHICS_DATA_REG)&0x08)
		/*do nothing */;
	// pitch = line length
	vga_write_gfx (0x24, 0x00);
	vga_write_gfx (0x25, 0x0C);
	vga_write_gfx (0x26, 0x00);
	vga_write_gfx (0x27, 0x0C);

	// num of pixels -1
	vga_write_gfx (0x20, 0xff);
	vga_write_gfx (0x21, 0x0b);

	vga_write_gfx (0x22, 0xff);
	vga_write_gfx (0x23, 0x02);

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
//	for (long int i = 0; i < 1024 * 768 * 3; i++) {
//		lfb[i] =  0;
//	}
	THIS->xpos = 0;
	THIS->ypos = 0;
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
	// draw the chrome
	int beg = 756;
	for (int y = beg; y < beg+13; y++) {
		uchar* vmem_l = lfb+VMEM_ADDR(0,y);
		for (int x = 0; x < 1024; x++) {
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

void init_vga() {
	char pal[] = {0x00, 0x00, 0x00, 0xff, 0xff, 0xff};
	init_chip();
	set_parm(0,0,0);
	init_chip();
	set_parm(0,0,0);
	lfb = ((unsigned char*)0xe0000000)  + 0x140000; // +(1024*3*427) - 341*3 - 1;
	
	//setup cursor
	vga_write_seq (0x12, 0x02);
	vga_write_pel (0x00, 0x00, pal);
	vga_write_pel (0x0f, 0x0f, pal+3);
	vga_write_att (0x00, 0x00);
	vga_write_att (0x0f, 0xff);
	vga_write_seq (0x12, 0x01);
	memcpy(((unsigned char*)0xe03fc000), dflt_cur, 256);
	cur_x = 0;
	CON.xpos = 0;
	CON.ypos = 0;
	cur_y = 0;
	CON.read = NULL;
//	CON.write = cirrus_write;
	CON.putchar = disp_char;
	CON.cls = cirrus_cls;
	CON.mv_cur = mv_cur;
	
	draw_cursor ((font->w - 2),
		     0,
		     2,
		     font->h+1);

#if 0
	for (int i = 0; i < 20; i++) {
		lfb[i*3+0] = 0x80;
		lfb[i*3+1] = 0x80;
		lfb[3*i+2] = 0x80;
	}
//	for (int i = 0; i < 20; i++) {
//		lfb[i*3+0+ 1024 *2] = 0x80;
//		lfb[i*3+1+ 1024 *2] = 0x80;
//		lfb[i*3+2+ 1024 *2] = 0x80;
//	}

	for (int ct = 0; ct < 4;  ct++) {
	for (int i = 0; i < 2; i++) {
		lfb[i*3+0+ 1024 * 3 * ct] = 0x80;
		lfb[i*3+1+ 1024 * 3*ct] = 0x80;
		lfb[i*3+2+ 1024 * 3*ct] = 0x80;
	}
	}


	//unsigned char bytes[] = {0x00,0x00,0xff};
	for (int j=0; j< 768;j+= 1 ) { //; 1024*2) {
	//for (int i = 0; i < 1024*3; i+=1) {
	//	lfb[i+j]= bytes[i%3];
	//}
	lfb[VMEM_ADDR(512,j)+2] = 0x00;
	lfb[VMEM_ADDR(512,j)+1] = 0x80;
	lfb[VMEM_ADDR(512,j)+0] = 0xff;
//	lfb[j*1024*3 + 512 * 3 + 2] = 0x00 ;
//	lfb[j*1024*3 + 512 * 3 + 1] = 0x80;
//	lfb[j*1024*3 + 512 * 3 + 0] = 0xff;
//	spin(10000000);
	}
	while (1) {
	for (int i = 0; i < 256; i+=2) {
		unsigned char* lfb_l = lfb + VMEM_ADDR(256,256);
		for (int j = 0; j < 256; j++) {
			for (int k = 0; k < 256; k++) {
				*lfb_l++ = i;
				*lfb_l++ = j;
				*lfb_l++ = k;
//				lfb[VMEM_ADDR(j+256,k+256)]   = i;
//				lfb[VMEM_ADDR(j+256,k+256)+1] = j;
//				lfb[VMEM_ADDR(j+256,k+256)+2] = k;
			}
			lfb_l += 2304;
		}
	}
	for (int i = 255; i >= 0; i-= 2) {
		unsigned char* lfb_l = lfb + VMEM_ADDR(256,256);
		for (int j = 0; j < 256; j++) {
			for (int k = 0; k < 256; k++) {
				*lfb_l++ = i;
				*lfb_l++ = j;
				*lfb_l++ = k;
//				lfb[VMEM_ADDR(j+256,k+256)]   = i;
//				lfb[VMEM_ADDR(j+256,k+256)+1] = j;
//				lfb[VMEM_ADDR(j+256,k+256)+2] = k;
			}
			lfb_l += 2304;
		}
	}
	}
#endif
}
