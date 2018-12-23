
#ifndef T
#error "Specify the queue type"
#endif

#ifndef TEMPLATE_TYPE
#error "Specify the queue template type"
#endif

#ifndef TEMPLATE_FUNCTION
#error "Specify the queue template function"
#endif



/*
 * queue_T_Init - 初始化队列
 *
 * @q: 目标队列
 * @buf: 队列缓存
 * @size: 队列长度
 */
void TEMPLATE_FUNCTION(queue,init)(TEMPLATE_TYPE(queue) *q, T *buf, int size) {
	q->stor_begin = buf;
	q->stor_end = q->stor_begin + size;

	q->begin = q->stor_begin;
	q->end = Null;
}
/*
 * queue_T_empty - 查询队列是否为空
 *
 * @q: 目标队列
 */
BOOL TEMPLATE_FUNCTION(queue,empty)(const TEMPLATE_TYPE(queue) *q) {
	return (Null == q->end) ? True : False;
}
/*
 * queue_T_full - 查询队列是否为满
 *
 * @q: 目标队列
 */
BOOL TEMPLATE_FUNCTION(queue,full)(const TEMPLATE_TYPE(queue) *q) {
	return (q->begin == q->end) ? True : False;
}
/*
 * queue_T_size - 查询队列大小
 *
 * @q: 目标队列
 */
int TEMPLATE_FUNCTION(queue, size)(const TEMPLATE_TYPE(queue) *q) {
	return (q->stor_end - q->stor_begin);
}
/*
 * queue_T_count - 查询队列长度
 *
 * @q: 目标队列
 */
int TEMPLATE_FUNCTION(queue, count)(const TEMPLATE_TYPE(queue) *q) {
	if (Null == q->end)
		return 0;
	else if (q->begin < q->end)
		return (q->end - q->begin);
	else
		return (q->stor_end - q->begin) + (q->end - q->stor_begin);
}
/*
 * queue_T_clear - 清空队列
 *
 * @q: 目标队列
 */
void TEMPLATE_FUNCTION(queue, clear)(TEMPLATE_TYPE(queue) *q) {
	q->begin = q->stor_begin;
	q->end = Null;
}
/*
 * queue_T_enqueue - 将数据插入队尾
 *
 * @q: 目标队列
 * @data: 目标数据
 */
BOOL TEMPLATE_FUNCTION(queue, enqueue)(TEMPLATE_TYPE(queue) *q, T data) {
	// 队列已满
	if (q->begin == q->end) {
		if (False == q->overwrite)
			return False;
		(q->begin)++;
		if (q->begin == q->stor_end)
			q->begin = q->stor_begin;
	}
	// 队列为空
	if (Null == q->end)
		q->end = q->begin;

	*(q->end) = data;
	(q->end)++;
	if (q->end == q->stor_end)
		q->end = q->stor_begin;

	return True;
}
/*
 * queue_T_dequeue - 从队首取出数据
 *
 * @q: 目标队列
 * @buf: 目标数据
 */
BOOL TEMPLATE_FUNCTION(queue, dequeue)(TEMPLATE_TYPE(queue) *q, T *buf) {
	// 队列为空
	if (Null == q->end)
		return False;

	*buf = *(q->begin);

	q->begin++;
	if (q->begin == q->stor_end)
		q->begin = q->stor_begin;
	if (q->begin == q->end)
		q->end = Null;

	return True;
}
/*
 * queue_T_pop - 从队尾取出数据
 *
 * @q: 目标队列
 * @buf: 目标数据
 */
BOOL TEMPLATE_FUNCTION(queue, pop)(TEMPLATE_TYPE(queue) *q, T *buf) {
	// 队列为空
	if (Null == q->end)
		return False;

	if (q->end == q->stor_begin) {
		*buf = *((q->stor_end) - 1);
		q->end = (q->stor_end) - 1;
	} else {
		*buf = *((q->end) - 1);
		q->end = (q->end) - 1;
	}

	if (q->begin == q->end)
		q->end = Null;

	return True;
}
/*
 * queue_T_head - 窥视队首数据
 *
 * @q: 目标队列
 * @buf: 目标数据
 */
BOOL TEMPLATE_FUNCTION(queue, head)(const TEMPLATE_TYPE(queue) *q, T *buf) {
	if (Null == q->end)
		return False;

	*buf = *(q->begin);

	return True;
}
/*
 * queue_T_tail - 窥视队尾数据
 *
 * @q: 目标队列
 * @buf: 目标数据
 */
BOOL TEMPLATE_FUNCTION(queue, tail)(const TEMPLATE_TYPE(queue) *q, T *buf) {
	if (Null == q->end)
		return False;

	if (q->end == q->stor_begin) {
		*buf = *((q->stor_end) - 1);
	} else {
		*buf = *((q->end) - 1);
	}

	return True;
}
