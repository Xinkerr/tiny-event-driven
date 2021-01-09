#ifndef __WAKEUP_TIMER_H__
#define __WAKEUP_TIMER_H__

#include <string.h>
#include "stm8s_awu.h"

extern void (*wakeup_timer_handler)(void);

/**
 * @brief 开启定时唤醒
 * 
 * @param[in] time: 唤醒的时间
 * 
 */
void wakeup_timer_enable(AWU_Timebase_TypeDef time);

/**
 * @brief 注册回调函数
 * 
 * @param[in] fun: 函数地址
 * 
 */
void wakeup_handler_registered(void (*fun)(void));
#endif