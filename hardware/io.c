#include "ctools.h"
#include "video.h"
void dbg(char c) {
	#if DEBUG_OUT == DBG_E9
		outb (0xe9, c);
	#elif DEBUG_OUT == DBG_SERIAL
		write_serial(0, c);
	#elif DEBUG_OUT == DBG_NULL
		;
	#elif DEBUG_OUT == DBG_VGA
		printf ("%c", c);
	#else
		#error "Invalid debug destination"
	#endif
}

