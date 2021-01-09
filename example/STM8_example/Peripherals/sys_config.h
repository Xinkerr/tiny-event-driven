#ifndef __SYS_CONFIG_H__
#define __SYS_CONFIG_H__

#include "stm8s_clk.h"

#define HSI_CLK_DIV_1       1
#define HSI_CLK_DVI_2       2
#define HSI_CLK_DIV_4       3
#define HSI_CLK_DIV_8       4

#define SYS_CLK_DIV   HSI_CLK_DIV_1

#if SYS_CLK_DIV == HSI_CLK_DIV_1
#define SYSTEM_CLK_INIT()       CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1)
#define TIM4_CLK_BASE           (uint32_t)125000

#elif SYS_CLK_DIV == HSI_CLK_DIV_2
#define SYSTEM_CLK_INIT()       CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV2)
#define TIM4_CLK_BASE           (uint32_t)62500

#elif SYS_CLK_DIV == HSI_CLK_DIV_4
#define SYSTEM_CLK_INIT()       CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV4)
#define TIM4_CLK_BASE           (uint32_t)31250

#elif SYS_CLK_DIV == HSI_CLK_DIV_8
#define SYSTEM_CLK_INIT()       CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV8)
#define TIM4_CLK_BASE           (uint32_t)15625

#endif

#endif
