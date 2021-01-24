#include "flash.h"
#include "sysclk_drv.h"

/**
 *@brief ϵͳʱ������
 *@return void
 */
void sysclk_drv_init(void)
{
	//ʱ�ӷ�Ƶ����
    Sysctrl_SetHCLKDiv(SysctrlHclkDiv1);
    Sysctrl_SetPCLKDiv(SysctrlPclkDiv1);

    ///< RCHʱ�Ӳ�ͬƵ�ʵ��л�����Ҫ�Ƚ�ʱ���л���RCL
    Sysctrl_SetRCLTrim(SysctrlRclFreq32768);
    Sysctrl_SetRCLStableTime(SysctrlRclStableCycle64);
    Sysctrl_ClkSourceEnable(SysctrlClkRCL, TRUE);
    Sysctrl_SysClkSwitch(SysctrlClkRCL);
    
    ///< ����Ŀ��Ƶ�ʵ�RCH��TRIMֵ
    Sysctrl_SetRCHTrim(SysctrlRchFreq24MHz);
    ///< ʹ��RCH
    Sysctrl_ClkSourceEnable(SysctrlClkRCH, TRUE);
    ///< ʱ���л���RCH
    Sysctrl_SysClkSwitch(SysctrlClkRCH);
    
    ///< HCLK������24M���˴�����FLASH���ȴ�����Ϊ0 cycle
    Flash_WaitCycle(FlashWaitCycle0);
}

/**
 *@brief systick��ʱ����ʼ��
 *@return void
 */
void systick_init(void)
{
	//��0
	SysTick->VAL = 0;
	//ѡ��ʱ��Դ HCLK
	SysTick->CTRL |= 0x04;
	SysTick->LOAD = SYSTICK;
}


/**
 *@brief systick ����
 *@return void
 */
void systick_enable(void)
{
	//systick��ʱ��ʹ�ܣ��ж�ʹ��
	SysTick->CTRL |= 0x03;	
}

/**
 *@brief systick �ر�
 *@return void
 */
void systick_disable(void)
{
	//systick��ʱ��ʹ�ܣ��ж�ʹ��
	SysTick->CTRL &= (~0x03);	
}


