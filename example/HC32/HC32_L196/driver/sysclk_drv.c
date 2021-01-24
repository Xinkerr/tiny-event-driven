#include "flash.h"
#include "sysclk_drv.h"

/**
 *@brief 系统时钟配置
 *@return void
 */
void sysclk_drv_init(void)
{
	//时钟分频设置
    Sysctrl_SetHCLKDiv(SysctrlHclkDiv1);
    Sysctrl_SetPCLKDiv(SysctrlPclkDiv1);

    ///< RCH时钟不同频率的切换，需要先将时钟切换到RCL
    Sysctrl_SetRCLTrim(SysctrlRclFreq32768);
    Sysctrl_SetRCLStableTime(SysctrlRclStableCycle64);
    Sysctrl_ClkSourceEnable(SysctrlClkRCL, TRUE);
    Sysctrl_SysClkSwitch(SysctrlClkRCL);
    
    ///< 加载目标频率的RCH的TRIM值
    Sysctrl_SetRCHTrim(SysctrlRchFreq24MHz);
    ///< 使能RCH
    Sysctrl_ClkSourceEnable(SysctrlClkRCH, TRUE);
    ///< 时钟切换到RCH
    Sysctrl_SysClkSwitch(SysctrlClkRCH);
    
    ///< HCLK不超过24M：此处设置FLASH读等待周期为0 cycle
    Flash_WaitCycle(FlashWaitCycle0);
}

/**
 *@brief systick定时器初始化
 *@return void
 */
void systick_init(void)
{
	//清0
	SysTick->VAL = 0;
	//选择时钟源 HCLK
	SysTick->CTRL |= 0x04;
	SysTick->LOAD = SYSTICK;
}


/**
 *@brief systick 开启
 *@return void
 */
void systick_enable(void)
{
	//systick定时器使能，中断使能
	SysTick->CTRL |= 0x03;	
}

/**
 *@brief systick 关闭
 *@return void
 */
void systick_disable(void)
{
	//systick定时器使能，中断使能
	SysTick->CTRL &= (~0x03);	
}


