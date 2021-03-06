#ifndef __TEVENT_CONF_H__
#define __TEVENT_CONF_H__

/******************************************功能配置**************************************************/
//软件定时重新计数的功能
#define tEVENT_RESTART_ENABLE               0

//修改软件定时器的定时周期值，并将计数值赋为0，重新计数的功能
#define tEVENT_TIMER_MODIFY1_ENABLE         0

//仅修改软件定时器的定时周期值，其他值不变
#define tEVENT_TIMER_MODIFY2_ENABLE         0

//启动高优先级机制
#define tEVENT_PRIORITY_ENABLE              0

//低功耗休眠功能
#define tEVENT_SLEEP_MODE_ENABLE            1
/****************************************************************************************************/

/******************************************移植配置**************************************************/
#include <stdint.h>
#include "sysclk_drv.h"
#include "lpm.h"

//滴答定时器部分

#define TICK_TIMER_INIT()                   systick_init()					
#define TICK_TIMER_START()                  systick_enable()					
#define TICK_TIMER_STOP()                   systick_disable()                   
#define SLEEP_COMMAND()                     Lpm_GotoDeepSleep(FALSE)

//软件定时器的计数值和定时周期值的类型
typedef uint16_t _TIME_INT;

//最多事件数
#define EVENT_QUE_SIZE					    10 
//事件FIFO缓冲区大小 触发一次低优先级事件加入缓冲区占用2个字节
#define EVENT_BUF_SIZE                      16
/****************************************************************************************************/
#endif

