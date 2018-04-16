#include <utils.h>

void delay(int c) {
    for (int i = 0; i < c; i++);
}


uint32 change_ending_32b(uint32 data) {
	union Data32 out;
	union Data32 *pdata = (union Data32 *)&data;

	out.byte[0] = pdata->byte[3];
	out.byte[1] = pdata->byte[2];
	out.byte[2] = pdata->byte[1];
	out.byte[3] = pdata->byte[0];

	return out.word;
}
uint16 change_ending_16b(uint16 data) {
	union Data16 out;
	union Data16 *pdata = (union Data16 *)&data;

	out.byte[0] = pdata->byte[1];
	out.byte[1] = pdata->byte[0];

	return out.half_word;
}

