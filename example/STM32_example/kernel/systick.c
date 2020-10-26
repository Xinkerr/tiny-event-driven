#include "systick.h"
#include <stdlib.h>
#include <stdbool.h>
#include "stm32f10x.h"
#include "stm32f10x_it.h" 

void (*systick_callback)(void);

static uint8_t  fac_us=0;//us��ʱ������
static uint32_t tick_reload;

void systick_timer_init(uint32_t tick_us, void (*sys_callback)(void))
{
	
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//ѡ���ⲿʱ��  HCLK/8
	fac_us=SystemCoreClock/8000000;	//Ϊϵͳʱ�ӵ�1/8
	tick_reload = tick_us*fac_us;
	SysTick->VAL = 0x00;        //��ռ�����
	SysTick->LOAD = tick_reload; //ʱ�����
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;	//�����ж�

	systick_callback = sys_callback;
}

void systick_timer_start(void)
{
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ;          //������ʱ��
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
