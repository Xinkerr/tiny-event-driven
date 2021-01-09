#ifndef __EXTI_H
#define __EXIT_H	 
#include "stm32f10x.h"
	 
//外部中断初始化
void EXTIX_Init(void);	

//EXIT4中断使能设置
void exti4_set(FunctionalState state);
#endif

