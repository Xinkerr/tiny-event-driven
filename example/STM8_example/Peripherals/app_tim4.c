
#include "app_tim4.h"
#include "sys_config.h"
uint32_t period;
/**
 * @brief 定时器4初始化
 * 
 * @param[in] time_us: 设定定时时间
 * 
 * @return 0, 成功; -1,失败
 */
int8_t app_tim4_init(uint32_t time_us)
{
    
    period = TIM4_CLK_BASE / time_us;
    if(period > 0xff)
        return -1;
    TIM4_TimeBaseInit(TIM4_PRESCALER_128, (uint8_t)period);
    TIM4_ARRPreloadConfig(ENABLE);         
    return 0;
}

/**
 * @brief 定时器4开启
 */
void app_tim4_start(void)
{
    TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);
    TIM4_Cmd(ENABLE);
}

/**
 * @brief 定时器4停止
 */
void app_tim4_stop(void)
{
    TIM4_Cmd(DISABLE);
    TIM4_ITConfig(TIM4_IT_UPDATE, DISABLE);
}