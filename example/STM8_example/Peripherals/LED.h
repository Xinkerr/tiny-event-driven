#ifndef __LED_H__
#define __LED_H__

#define LED1_GPIO           GPIOD , GPIO_PIN_2
#define LED1_GPIO_MODE      GPIO_MODE_OUT_PP_HIGH_SLOW
#define LED1_OFF            GPIO_WriteHigh(LED1_GPIO)
#define LED1_ON             GPIO_WriteLow(LED1_GPIO)

typedef enum
{
    OFF = 0,
    ON
}led_state_t;

/**
 * @brief LED初始化
 */
void LED_init(void);

/**
 * @brief LED控制
 * 
 * @param[in]   newState: LED状态 0,关闭; 1,开启
 */
void LED1_Control(led_state_t newState);

#endif