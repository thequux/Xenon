#include <types.h>
#include <driver.h>
#include <kqueue.h>
#ifndef XE_VIDEO_H
#define XE_VIDEO_H
void k_swrite(char* str, int type);
void k_iwrite( int c, int dest);
//void k_cls();
void init_con();

void set_font (void* font, int plane);

void scroll (int lines);

int printf(const char* template, ...);

#define GRAPHICS_ADDR_REG	0x3CE
#define GRAPHICS_DATA_REG	0x3CF
#define SEQ_ADDR_REG		0x3C4
#define SEQ_DATA_REG		0x3C5
#define CRTC_ADDR_REG		0x3D4
#define CRTC_DATA_REG		0X3D5
#define VMEM_C(x,y)  ((char*)(0xb8000+(((y)*maxcol_p+(x))*2)))


// the amount of memory to allocate for backing a console, in bytes.
// Currently, 20K, which is enough for 128-25=103 lines of scrollback.
#define VMEM_ALLOC 	(160 * 128)

static inline void vga_write_gfx(unsigned char addr, unsigned char data) {
	outb (GRAPHICS_ADDR_REG, addr);
	outb (GRAPHICS_DATA_REG, data);
}

static inline void vga_write_seq(unsigned char addr, unsigned char data) {
	outb (SEQ_ADDR_REG, addr);
	outb (SEQ_DATA_REG, data);
}

static inline void vga_write_crt(unsigned char addr, unsigned char data) {
	outb (CRTC_ADDR_REG, addr);
	outb (CRTC_DATA_REG, data);
}

static inline void vga_write_att(unsigned char addr, unsigned char data) {
		__asm__ ("cli");   // this is critical!
        	inb (0x3da);	// Read ISR1 to reset flipflop.
char addr0 = 	inb (0x3c0);	// read current address
		spin(500);
		outb (0x3c0, addr);
		spin(500);
		outb (0x3c0, data);
		spin(500);
		outb (0x3c0, addr0);
		__asm__ volatile ("sti");
}

static inline void vga_write_pel(unsigned char start, unsigned char end, char* vals) {
	asm ("cli");
	outb(0x3c8, start);
	while ((start++) <= end) {
		outb(0x3c9, *vals++);
		outb(0x3c9, *vals++);
		outb(0x3c9, *vals++);
	}
	asm("sti");
}
// TODO: make this dynamic. Need kalloc for that.
/* struct console_driver {
	int id; // a unique, opaque identifier
	BOOL allocateConsole(console* con);
	BOOL 
}; */
struct color {
	uchar r;
	uchar g;
	uchar b;
	uchar index;
};
struct CSI {
	int vals[16];
	BOOL esc;
	char pos;
	char term;
	int nv;
};
extern struct console {
	void (*read) (struct console* THIS, char* buffer, int len);
	//void (*write)(struct console* THIS, char* buffer, int len);
	void (*putchar)(struct console* THIS, uchar buf);
	void (*cls)  (struct console* THIS);
	void (*mv_cur) (struct console* THIS);
	//Data
	struct color fg;
	struct color bg;
	int xpos; // chars
	int ypos; // chars
	int w; // pixels
	int h; // pixels
	BOOL intense;
	// private...
	int old_xpos, old_ypos;
	// CSI parsing
	BOOL esc;
	struct CSI csibuf;
		
} CON;


extern struct font_t {
	u8_t w;		// width in pixels
	u8_t h;		// height in pixels
	u8_t w_byte;	// the number of bytes in a scanline
	u8_t glyph_size;// the number of bytes in a glyph
	u16_t nGlyphs;	// the number of glyphs
	u8_t chkxor;	// the checkxor of the font; 
			// the 8 bit checkxor if the entire font should be 0.
			// Use this to make it so.
	u8_t reserved;
	u8_t glyphs[];	// the glyph data.
} *font;
#if 0
struct console {
	// virtual functions:
	void (*scroll)(struct console* THIS, int dy, BOOL clear);
		// scroll the display; update video mem if appropriate.
	void (*blit)(struct console* THIS, char* dest, int len);
		// write to hardware.
		// used only on console switching
	void (*cls)(struct console* THIS);
		// do whatever is necessary to clear the display.
	void (*write)(struct console* THIS, char buf);
		// write a single charcter to the display; do any special
		// parsing necessary (eg, ANSI escapes...)
	char (*read)(struct console* THIS);
		// return the next avaliable character, or 0 if no data
	BOOL (*dataAvaliable)(struct console* THIS); 
		// return FALSE if no data is ready, TRUE otherwise

	// Callbacks. Set, but do not call.
	void (*update)(struct console* THIS);
	        // I call this when updates are necessary.
	        // Set to update callback; NULL if not applicable.
	
	// data members
	int id;            // An opaque, unique identifier across all consoles
	int console_num;   // The console number. Under driver control
	void* driver;      // the driver data. 
	// Non-console code must treat these as private.
	void* cbData;      // Treated as opaque by generic console code.
	                   // Intended for driver-specific data.
	char* vmem_base;   // The base of allocated memory.
	char* vmem_disp;   // the currently visible portion
	char* vmem_active; // The portion that would be visible at the current
			   // scroll position
	int vmem_len;      // The amount of video memory allocated. Currently
			   // this is always VMEM_ALLOC, but it will change
	char attr;
	int xcur;
	int ycur;
	int rows;
	int columns;

	struct kqueue_char_128 inputBuf; // buffer for avaliable input
	struct kqueue_char_128 escape; // Buffer for incomplete escape sequences
	BOOL inESC;
	// This may be set by console-switching code ONLY.
	// Any driver may read it; in fact, update probably needs to read it.
	BOOL active;
};
#endif

extern struct color colors[];
#endif
