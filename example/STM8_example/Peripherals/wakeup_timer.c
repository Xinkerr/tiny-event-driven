#include "stm8s_awu.h"
#include "wakeup_timer.h"

//中断 回调函数指针
void (*wakeup_timer_handler)(void) = NULL;

/**
 * @brief 开启定时唤醒
 * 
 * @param[in] time: 唤醒的时间
 * 
 */
void wakeup_timer_enable(AWU_Timebase_TypeDef time)
{
    AWU_LSICalibrationConfig(128000);
    AWU_Init(time);
    AWU_Cmd(ENABLE);
}

/**
 * @brief 注册回调函数
 * 
 * @param[in] fun: 函数地址
 * 
 */
void wakeup_handler_registered(void (*fun)(void))
{
    wakeup_timer_handler = fun;
}