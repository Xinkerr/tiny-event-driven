#ifndef __APP_TIM4_H__
#define __APP_TIM4_H__

#include "stm8s.h"

/**
 * @brief 定时器4初始化
 * 
 * @param[in] time_us: 设定定时时间
 * 
 * @return 0, 成功; -1,失败
 */
int8_t app_tim4_init(uint32_t time_us);

/**
 * @brief 定时器4开启
 */
void app_tim4_start(void);

/**
 * @brief 定时器4停止
 */
void app_tim4_stop(void);

#endif