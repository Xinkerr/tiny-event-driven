#ifndef __TEVENT_H__
#define __TEVENT_H__
#include "eQueque.h"
#include <stdint.h>
#include <stdbool.h>
//#include "type8.h"

//******************添加TICK定时器相关头文件和对应函数************************************
#include "systick.h"
#define TICK_TIMER_INIT()					systick_timer_init(1000, tEvent_timer_ticking)
#define TICK_TIMER_START()					systick_timer_start()
//*****************************************************************************************

typedef uint16_t _TIME_INT;
#define EVENT_QUE_SIZE					3   //范围0~127
#define IDLE							0

void tEvent_init(void);

//void tEvent_tick_start(void);

int8_t tEvent_timer_ctreate(uint8_t event_id, _TIME_INT period);

int8_t tEvent_timer_modify(uint8_t event_id, _TIME_INT period);

int8_t tEvent_timer_start(uint8_t event_id);

int8_t tEvent_timer_restart(uint8_t event_id);

int8_t tEvent_timer_stop(uint8_t event_id);

void tEvent_timer_ticking(void);

uint8_t tEvent_queque_get(void);

//放入事件
#define tEvent_queque_put(event_id)		msgQueque_put(event_id)

#endif

