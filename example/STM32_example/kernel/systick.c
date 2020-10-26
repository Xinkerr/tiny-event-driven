#include "systick.h"
#include <stdlib.h>
#include <stdbool.h>
#include "stm32f10x.h"
#include "stm32f10x_it.h" 

void (*systick_callback)(void);

static uint8_t  fac_us=0;//us延时倍乘数
static uint32_t tick_reload;

void systick_timer_init(uint32_t tick_us, void (*sys_callback)(void))
{
	
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//选择外部时钟  HCLK/8
	fac_us=SystemCoreClock/8000000;	//为系统时钟的1/8
	tick_reload = tick_us*fac_us;
	SysTick->VAL = 0x00;        //清空计数器
	SysTick->LOAD = tick_reload; //时间加载
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;	//开启中断

	systick_callback = sys_callback;
}

void systick_timer_start(void)
{
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ;          //开启定时器
}

void systick_timer_stop(void)
{
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk ;
}

void SysTick_Handler(void)
{
	if(systick_callback != NULL)
		systick_callback();
}
