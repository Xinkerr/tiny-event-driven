#include "stm8s_gpio.h"
#include "LED.h"

/**
 * @brief LED初始化
 */
void LED_init(void)
{
    GPIO_Init(LED1_GPIO , LED1_GPIO_MODE);  
}

/**
 * @brief LED控制
 * 
 * @param[in]   newState: LED状态 0,关闭; 1,开启
 */
void LED1_Control(led_state_t newState)
{
    if(newState == ON)
    {
        LED1_ON;
    }
    else
    {
        LED1_OFF;
    }
    
}
