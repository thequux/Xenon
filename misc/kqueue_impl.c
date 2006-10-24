#define __KEEP_MACROS
#include "kqueue_impl.h"


int CONCAT(fn_pfx,_push) (struct fn_pfx* queue, _queue_type value) {
	if ( queue->len == _queue_size)
		return -1;
	queue->buf[queue->head] = value;
	queue->head++;
	queue->head %= _queue_size;
	queue->len++;
	return 0;
}

int CONCAT(fn_pfx,_pop)  (struct fn_pfx* queue, _queue_type *value) {
	if (queue->len == 0)
		return -1;
	*value = queue->buf[queue->tail];
	queue->tail ++;
	queue->tail %= _queue_size;
	queue->len--;
	return 0;
}

int CONCAT(fn_pfx,_clear) (struct fn_pfx* queue) {
	queue->len = 0;
	queue->head = 0;
	queue->tail = 0;
	return 0;
}

void CONCAT(fn_pfx,_init) (struct fn_pfx* queue) {
	queue->head = 0;
	queue->tail = 0;
	queue->len = 0;
	queue->clear = CONCAT(fn_pfx,_clear);
	queue->push = CONCAT(fn_pfx,_push);
	queue->pop = CONCAT(fn_pfx,_pop);
}

#undef _queue_type
#undef _queue_size
#undef _queue_name
#undef _fn_pfx
#undef CONCAT
#undef CONCAT_2
#undef __KEEP_MACROS
