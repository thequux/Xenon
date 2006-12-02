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

#define GRAPHICS_ADDR_REG	0x3CE
#define GRAPHICS_DATA_REG	0x3CF
#define SEQ_ADDR_REG		0x3C4
#define SEQ_DATA_REG		0x3C5
#define CRTC_ADDR_REG		0x3D4
#define CRTC_DATA_REG		0X3D5
#define vga_write_misc(a,d) outb(a,d)
#include <ctools.h>
#include <video.h>
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

void init_vga() {
	init_chip();
	set_parm(0,0,0);
	init_chip();
	set_parm(0,0,0);
	unsigned char* lfb = ((unsigned char*)0xe0000000)  + 0x140000; // +(1024*3*427) - 341*3 - 1;
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
		for (int j = 0; j < 256; j++) {
			for (int k = 0; k < 256; k++) {
				lfb[VMEM_ADDR(j+256,k+256)]   = i;
				lfb[VMEM_ADDR(j+256,k+256)+1] = j;
				lfb[VMEM_ADDR(j+256,k+256)+2] = k;
			}
		}
	}
	for (int i = 255; i >= 0; i-= 2) {
		for (int j = 0; j < 256; j++) {
			for (int k = 0; k < 256; k++) {
				lfb[VMEM_ADDR(j+256,k+256)]   = i;
				lfb[VMEM_ADDR(j+256,k+256)+1] = j;
				lfb[VMEM_ADDR(j+256,k+256)+2] = k;
			}
		}
	}
	}
	while (1);
	unsigned char tmp = 0;
	while (1) {
	lfb[1024 * 3+1] = tmp;
	tmp = ~tmp;
	spin(10000000);
	}
}
