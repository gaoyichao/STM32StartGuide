#ifndef TYPES_H
#define TYPES_H

typedef signed char             int8;
typedef signed short            int16;
typedef signed long             int32;

typedef signed char const       cint8;
typedef signed short const      cint16;
typedef signed long const       cint32;

typedef unsigned char           uint8;
typedef unsigned short          uint16;
typedef unsigned long           uint32;
typedef unsigned long long      uint64;

typedef unsigned char const     ucint8;
typedef unsigned short const    ucint16;
typedef unsigned long const     ucint32;
typedef unsigned long long const ucint64;

typedef unsigned char   BOOL;

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL 0
#endif

#define U8Bit(n)    ((uint8)(1 << n))
#define U16Bit(n)   ((uint16)(1 << n))
#define U32Bit(n)   ((uint32)(1 << n))

union Data32 {
    uint32 word;
    uint16 half_word[2];
    uint8 byte[4];
};

union Data16 {
    uint16 half_word;
    uint8 byte[2];
};

/*
* offsetof - ��ȡһ���ṹ��ĳ����Ա��ƫ����
*
* @type: �ṹ������
* @member: ��Ա����
*/
#define OffsetOf(type, member) ((unsigned long) &((type *)0)->member)
/*
* container_of - ���ݳ�Ա��ַ@ptr�ͽṹ������,��ȡ���ڽṹ��ĵ�ַ
*
* @ptr: �ṹ���Աָ��
* @type: �ṹ������
* @member: ��Ա����
*/
#define ContainerOf(ptr, type, member) ((type *)((uint8 *)(ptr) - OffsetOf(type, member)))



#endif
