#include <ctools.h>
#include <video.h>
#define maxcol_p	80
#define maxrow_p	25
#define maxcol		(maxcol_p - 1)
#define maxrow		(maxrow_p - 1)

extern char default_font[];
extern volatile unsigned char* vmem;
int scroll_p;

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
	outb (CRTC_DATA_REG, (msl & 0xe0) | 15);
	vga_write_crt(0x0a, 0x05);
	vga_write_crt(0x0b, 0x05);
	
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

void set_cur (struct console *THIS) {
	// if delay is non-zero, just cache position; do not access hardware
	// If delay is 0, update console from cache only.
	
	int np;
	char nph, npl;
	np = (THIS->ypos-0) * maxcol_p + THIS->xpos;
	nph = ((np & 0xff00) >> 8);
	npl = np & 0xff;
	int reg = ((inb(0x3cc)&0x01)?0x3D4:0x3B4);
	outb (reg, 0x0f);
	outb (reg+1, npl);
	outb (reg, 0x0e);
	outb (reg+1, nph);

}
void scroll(struct console *THIS __attribute__((unused)), int lines) {
	int l1 = 0, l2 = lines;
	while (l2 < maxrow) {
		for (int i = 0; i < maxcol; i++) {
			VMEM_C(i, l1)[0] = VMEM_C(i, l2)[0];
			VMEM_C(i, l1)[1] = VMEM_C(i, l2)[1];
		}
//			vmem[l1 * maxcol_p * 2 + i] = vmem[l2*maxcol_p*2 + i];
		l1++;
		l2++;
	}

	while (l1 < maxrow) {
		for (int i = 0; i < maxcol; i++) {
			VMEM_C(i, l1)[0] = ' ';
			VMEM_C(i, l1)[1] = 0x07;
//			vmem[l1 * maxcol_p * 2 + i] = ' ';
//			vmem[l1 * maxcol_p * 2 + i+1] = 0x07;
		}
		l1 ++;
	}

	VMEM_C(maxcol, scroll_p+1)[0] = (unsigned char)0xb1;
	scroll_p += lines;
	VMEM_C(maxcol, scroll_p+1)[0] = (unsigned char)0xDB;
	
}
static void k_putchar_vga(struct console * THIS, uchar c) {
	
	switch (c) {
/*		case '\n':
			y += 1;
			x  = 0;
			if (y == maxrow) {
				scroll(1);
				y--;
			}
			set_cur(x,y,1);
			return;*/
		default:
			//p = (y * maxcol + x) << 1;
			VMEM_C(THIS->xpos,THIS->ypos)[1] = ((unsigned char)THIS->bg.index << 4) | (unsigned char)THIS->fg.index;
			VMEM_C(THIS->xpos,THIS->ypos)[0] = c; //THIS->xpos+'0';
			break;
	}
}
static void k_cls() {
        for (int i = 0; i < maxrow; i++) {
                for (int j = 0; j < maxcol; j++) {
                        VMEM_C(j,i)[0] = ' ';
                        VMEM_C(j,i)[1] = 0x07;
                }
        }
        //for (int i = 0; i < maxcol*maxrow*2; i+=2) {
        //      vmem[i] = ' ';
        //      vmem[i+1] = (unsigned char)0x07;
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

static void init_vga_text() {
	set_font (default_font,0);
	set_font (default_font,1);
	CON.putchar = k_putchar_vga;
	CON.cls = k_cls;
	CON.mv_cur = set_cur;
	CON.scroll = scroll;
	// make sure that planes are correct...
	char seq3;
	outb (SEQ_ADDR_REG, 0x03);
	seq3 = inb (SEQ_DATA_REG);
	outb (SEQ_DATA_REG, 0x20);
	CON.cls(&CON);
	k_cls();
}

REGISTER_INIT(init_vga_text);
