#include <driver.h>
#include <kqueue.h>
#ifndef XE_VIDEO_H
#define XE_VIDEO_H
void k_swrite(char* str, int type);
void k_iwrite( int c, int dest);
void k_cls();
void init_con();

void set_font (void* font, int plane);

void scroll (int lines);

int printf(const char* template, ...);

#define VMEM_C(x,y)  (vmem+(((y)*maxcol_p+(x))*2))

#define maxcol_p	80
#define maxrow_p	25
#define maxcol		(maxcol_p - 1)
#define maxrow		(maxrow_p - 1)

// the amount of memory to allocate for backing a console, in bytes.
// Currently, 20K, which is enough for 128-25=103 lines of scrollback.
#define VMEM_ALLOC 	(160 * 128)
// TODO: make this dynamic. Need kalloc for that.
/* struct console_driver {
	int id; // a unique, opaque identifier
	BOOL allocateConsole(console* con);
	BOOL 
}; */
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
