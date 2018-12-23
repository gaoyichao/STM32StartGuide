#include <queue.int.h>

#define T uint8
#define TEMPLATE_TYPE(a) a ##_uint8
#define TEMPLATE_FUNCTION(a,b) a ##_uint8_## b
#include "queue.c.h"
#undef TEMPLATE_FUNCTION
#undef TEMPLATE_TYPE
#undef T
