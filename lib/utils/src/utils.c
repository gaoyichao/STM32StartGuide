#include <utils.h>

void delay(int c) {
    for (int i = 0; i < c; i++);
}


/*
 * HexChar2Uint8 - 16进制字符转换为整型数据
 */
uint8 HexChar2Uint8(uint8 hexChar) {
    switch (hexChar) {
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
        hexChar -= '0';
        break;
    case 'a': case 'A':
        hexChar = 0x0A;
        break;
    case 'b': case 'B':
        hexChar = 0x0B;
        break;
    case 'c': case 'C':
        hexChar = 0x0C;
        break;
    case 'd': case 'D':
        hexChar = 0x0D;
        break;
    case 'e': case 'E':
        hexChar = 0x0E;
        break;
    case 'f': case 'F':
        hexChar = 0x0F;
        break;
    }
    
    return hexChar;
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

