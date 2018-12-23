
#ifndef T
#error "Specify the queue type"
#endif

#ifndef TEMPLATE_TYPE
#error "Specify the queue template type"
#endif

#ifndef TEMPLATE_FUNCTION
#error "Specify the queue template function"
#endif


typedef struct TEMPLATE_TYPE(queue) {
	T *begin;
	T *end;
	T *stor_begin;
	T *stor_end;

	BOOL overwrite;	// 如果队列已满,是否覆盖队首数据
} TEMPLATE_TYPE(queue);

void TEMPLATE_FUNCTION(queue,init)(TEMPLATE_TYPE(queue) *q, T *buf, int size);
BOOL TEMPLATE_FUNCTION(queue,empty)(const TEMPLATE_TYPE(queue) *q);
BOOL TEMPLATE_FUNCTION(queue,full)(const TEMPLATE_TYPE(queue) *q);
int TEMPLATE_FUNCTION(queue, size)(const TEMPLATE_TYPE(queue) *q);
int TEMPLATE_FUNCTION(queue, count)(const TEMPLATE_TYPE(queue) *q);

void TEMPLATE_FUNCTION(queue, clear)(TEMPLATE_TYPE(queue) *q);
BOOL TEMPLATE_FUNCTION(queue, enqueue)(TEMPLATE_TYPE(queue) *q, T data);
BOOL TEMPLATE_FUNCTION(queue, dequeue)(TEMPLATE_TYPE(queue) *q, T *buf);
BOOL TEMPLATE_FUNCTION(queue, pop)(TEMPLATE_TYPE(queue) *q, T *buf);

BOOL TEMPLATE_FUNCTION(queue, head)(const TEMPLATE_TYPE(queue) *q, T *buf);
BOOL TEMPLATE_FUNCTION(queue, tail)(const TEMPLATE_TYPE(queue) *q, T *buf);
