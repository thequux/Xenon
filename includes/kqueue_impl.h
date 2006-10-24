/***********************************************************
 * Implementation of a generic queue in kernel mode...     *
 *                                                         *
 * To instantiate queues of various types,                 *
 * #define _queue_type <typename>                          *
 * #define _queue_name <suffix>                            *
 * #define _queue_size <length of queue>                   *
 * #include <this file>                                    *
 *                                                         *
 * Lather, rinse, repeat for each desired queue type.      *
 ***********************************************************/

#ifndef _queue_type
	#error _queue_type must be defined
#endif
#ifndef _queue_size
	#error _queue_size must be defined
#endif
#ifndef _queue_name
	#error _queue_name must be defined
#endif
#define CONCAT_2(x,y) x##y
#define CONCAT(x,y) CONCAT_2(x,y)
#define fn_pfx CONCAT(CONCAT(kqueue_,_queue_name),CONCAT(_,_queue_size))
struct fn_pfx;
struct CONCAT(CONCAT(kqueue_,_queue_name),CONCAT(_,_queue_size)) {
	/// Push value onto the end of queue
	int (*push) (struct fn_pfx* queue, _queue_type value); 
	
	/// Pop the tail off queue and put it in *value
	int (*pop) (struct fn_pfx* queue, _queue_type* value); 
	
	/// Clear the queue. Doesn't actually delete values.
	int (*clear) (struct fn_pfx* queue);
	
	/// The actual values
	_queue_type buf[_queue_size];

	/// The index one after the last element (to be removed)
	int head;
	/// The index of the first element (to be removed)
	int tail;
	/// int len
	int len;

	// If head == tail, the queue is empty.
	// If head == tail - 1, the queue is full.
	// If head < tail, the length is head - tail + _queue_size
	// If head > tail, the length is head - tail
};

void CONCAT(fn_pfx,_init) (struct fn_pfx* queue);
#ifndef __KEEP_MACROS
#undef _queue_type
#undef _queue_size
#undef _queue_name
#undef CONCAT
#undef CONCAT_2
#undef fn_pfx
#endif
