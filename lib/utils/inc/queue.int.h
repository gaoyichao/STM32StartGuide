#ifndef QUEUE_INIT_H
#define QUEUE_INIT_H

#include <types.h>

#define T uint8
#define TEMPLATE_TYPE(a) a ##_uint8
#define TEMPLATE_FUNCTION(a,b) a ##_uint8_## b
#include "queue.h.h"
#undef TEMPLATE_FUNCTION
#undef TEMPLATE_TYPE
#undef T

#endif
