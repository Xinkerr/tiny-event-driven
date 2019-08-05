/****Version 1.0.1****/

#ifndef __TYPE8_H__
#define __TYPE8_H__
typedef unsigned char         uchar;
typedef unsigned int          uint;

#if(!defined(__bool_true_false_are_defined) || !defined(_STDBOOL))
typedef unsigned char         bool;
#define true				  1
#define false				  0
#endif

typedef unsigned char         UINT8;
typedef unsigned short int    UINT16;
typedef unsigned long         UINT32;

typedef char				  INT8;
typedef short int			  INT16;
typedef long				  INT32;

typedef unsigned char         uint8;
typedef unsigned short int    uint16;
typedef unsigned long         uint32;

typedef char				  int8;
typedef short int			  int16;
typedef long				  int32;

#if(!defined(__stdint_h) || !defined(_STDINT_H))
typedef unsigned char         uint8_t;
typedef unsigned short int    uint16_t;
typedef unsigned long         uint32_t;

typedef char				  int8_t;
typedef short int			  int16_t;
typedef long				  int32_t;
#endif

typedef unsigned char		  u8;
typedef unsigned int		  u16;
typedef unsigned long		  u32;

typedef char				  s8;
typedef short int			  s16;
typedef long				  s32;

#ifndef SET
#define SET						1
#endif

#ifndef CLR
#define CLR						0
#endif

#ifndef HIGH
#define HIGH					1
#endif

#ifndef LOW
#define LOW						0
#endif

#define	SET_BIT(SFR,NUM)		(SFR|=(1<<NUM))             //位置1
#define	CLR_BIT(SFR,NUM)		(SFR&=~(1<<NUM))	        //位清0
#define READ_BIT(SFR,NUM)       ((SFR>>NUM)&1)              //读位

#define SET_BIT0(res)			\
	(res |= 0x01)
#define SET_BIT1(res)			\
	(res |= 0x02)
#define SET_BIT2(res)			\
	(res |= 0x04)
#define SET_BIT3(res)			\
	(res |= 0x08)
#define SET_BIT4(res)			\
	(res |= 0x10)
#define SET_BIT5(res)			\
	(res |= 0x20)
#define SET_BIT6(res)			\
	(res |= 0x40)
#define SET_BIT7(res)			\
	(res |= 0x80)

#define CLR_BIT0(res)			\
	(res &= 0xfe)
#define CLR_BIT1(res)			\
	(res &= 0xfd)
#define CLR_BIT2(res)			\
	(res &= 0xfb)
#define CLR_BIT3(res)			\
	(res &= 0xf7)
#define CLR_BIT4(res)			\
	(res &= 0xef)
#define CLR_BIT5(res)			\
	(res &= 0xdf)
#define CLR_BIT6(res)			\
	(res &= 0xbf)
#define CLR_BIT7(res)			\
	(res &= 0x7f)

#define READ_BIT0(res)          \
    (res & 0x01)
#define READ_BIT1(res)          \
    ((res>>1) & 0X01)
#define READ_BIT2(res)          \
    ((res>>2) & 0X01)
#define READ_BIT3(res)          \
    ((res>>3) & 0X01)
#define READ_BIT4(res)          \
    ((res>>4) & 0X01)
#define READ_BIT5(res)          \
    ((res>>5) & 0X01)
#define READ_BIT6(res)          \
    ((res>>6) & 0X01)
#define READ_BIT7(res)          \
    ((res>>7) & 0X01)


#ifndef ERROR
#define ERROR					-1
#endif // ERROR
#ifndef SUCCESS
#define SUCCESS					0
#endif // SUCCESS
#endif
