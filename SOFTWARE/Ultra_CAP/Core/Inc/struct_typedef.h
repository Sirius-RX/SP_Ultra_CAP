#ifndef __STRUCT_TYPEDEF_H__
#define __STRUCT_TYPEDEF_H__


/* exact-width unsigned integer types */
typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
typedef unsigned char bool_t;
typedef float fp32;
typedef double fp64;

typedef signed char int8_t;
typedef signed short int int16_t;
typedef signed int int32_t;
typedef signed long long int64_t;

typedef unsigned char       uint8;  /*  8 bits */
typedef unsigned short int  uint16; /* 16 bits */
typedef unsigned long int   uint32; /* 32 bits */
typedef unsigned long long  uint64; /* 64 bits */

typedef char                int8;   /*  8 bits */
typedef short int           int16;  /* 16 bits */
typedef long  int           int32;  /* 32 bits */
typedef long  long          int64;  /* 64 bits */

typedef volatile int8       vint8;  /*  8 bits */
typedef volatile int16      vint16; /* 16 bits */
typedef volatile int32      vint32; /* 32 bits */
typedef volatile int64      vint64; /* 64 bits */

typedef volatile uint8      vuint8;  /*  8 bits */
typedef volatile uint16     vuint16; /* 16 bits */
typedef volatile uint32     vuint32; /* 32 bits */
typedef volatile uint64     vuint64; /* 64 bits */
typedef struct Dtype
{
        unsigned long b0: 1;
        unsigned long b1: 1;
        unsigned long b2: 1;
        unsigned long b3: 1;
        unsigned long b4: 1;
        unsigned long b5: 1;
        unsigned long b6: 1;
        unsigned long b7: 1;
        unsigned long b8: 1;
        unsigned long b9: 1;
        unsigned long b10: 1;
        unsigned long b11: 1;
        unsigned long b12: 1;
        unsigned long b13: 1;
        unsigned long b14: 1;
        unsigned long b15: 1;
        unsigned long b16: 1;
        unsigned long b17: 1;
        unsigned long b18: 1;
        unsigned long b19: 1;
        unsigned long b20: 1;
        unsigned long b21: 1;
        unsigned long b22: 1;
        unsigned long b23: 1;
        unsigned long b24: 1;
        unsigned long b25: 1;
        unsigned long b26: 1;
        unsigned long b27: 1;
        unsigned long b28: 1;
        unsigned long b29: 1;
        unsigned long b30: 1;
        unsigned long b31: 1;
    
} Dtype;    //sizeof(Dtype) ? 4


#define BIT0                 ((uint16_t)0x0001)  /* Bit 0     */
#define BIT1                 ((uint16_t)0x0002)  /* Bit 1     */
#define BIT2                 ((uint16_t)0x0004)  /* Bit 2     */
#define BIT3                 ((uint16_t)0x0008)  /* Bit 3     */
#define BIT4                 ((uint16_t)0x0010)  /* Bit 4     */
#define BIT5                 ((uint16_t)0x0020)  /* Bit 5     */
#define BIT6                 ((uint16_t)0x0040)  /* Bit 6     */
#define BIT7                 ((uint16_t)0x0080)  /* Bit 7     */
#define BIT8                 ((uint16_t)0x0100)  /* Bit 8     */
#define BIT9                 ((uint16_t)0x0200)  /* Bit 9     */
#define BIT10                ((uint16_t)0x0400)  /* Bit 10    */
#define BIT11                ((uint16_t)0x0800)  /* Bit 11    */
#define BIT12                ((uint16_t)0x1000)  /* Bit 12    */
#define BIT13                ((uint16_t)0x2000)  /* Bit 13    */
#define BIT14                ((uint16_t)0x4000)  /* Bit 14    */
#define BIT15                ((uint16_t)0x8000)  /* Bit 15    */


#endif
