#ifndef __EQUEQUE_H__
#define __EQUEQUE_H__
#include <stdint.h>
#include <stdbool.h>
//#include "type8.h"

#define MSG_QUEQUE_SIZE				16//需0< SIZE <256
typedef bool						_BOOL;//如果用8051则可以用bit

#define QUE_SUCCESS					0
#define QUE_FAIL					-1

typedef enum
{
	msgQUEQUE_EMPTY = 0,			
	msgQUEQUE_FULL,
	msgQUEQUE_NORMAL,
	msgQUEQUE_ERROR
}queque_state_m;


//消息队列初始化
void msgQueque_init(void);
//消息队列的状态
queque_state_m msgQueque_status(void);
//加入消息
int8_t msgQueque_put(uint8_t msgEvent);
//取出消息
int8_t msgQueque_get(uint8_t* msgEvent);

#endif
