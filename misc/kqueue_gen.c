#ifndef INC
	#error "Must define INC!"
#endif

#define _queue_type int
#define _queue_size 128
#define _queue_name int
#include INC

#define _queue_type char
#define _queue_size 128
#define _queue_name char
#include INC

#undef INC
