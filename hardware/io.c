#include "ctools.h"

void dbg(char c) {
	#if DEBUG_OUT == DBG_E9
		outb (0xe9, c);
	#elif DEBUG_OUT == DBG_SERIAL
		write_serial(c);
	#elif DEBUG_OUT == DBG_NULL
		;
	#else
		#error "Invalid debug destination"
	#endif
}

