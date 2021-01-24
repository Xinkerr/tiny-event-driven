/***************************************************************************
* 功能：LED 500ms间隔亮灭，5秒后休眠。通过按键触发中断唤醒。
* LED和按键代码移植自官方的参考代码。
*
* 本代码仅供参考，如有任何问题概不负责。
* 
* Create Date:   2021/1/24
* Modified Date: 2021/1/24
* Version:1.0
*
****************************************************************************/
#include <stdbool.h>
#include "gpio.h"
#include "sysclk_drv.h"
#include "tEvent.h"

typedef enum
{
    LED_EVENT = 1,
    DEEP_SLEEP
}app_event_t;


static uint8_t app_event;

static void App_LedInit(void)
{
    stc_gpio_cfg_t stcGpioCfg;
    
    ///< 打开GPIO外设时钟门控
    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE); 
    
    ///< 端口方向配置->输出(其它参数与以上（输入）配置参数一致)
    stcGpioCfg.enDir = GpioDirOut;
    ///< 端口上下拉配置->下拉
    stcGpioCfg.enPu = GpioPuDisable;
    stcGpioCfg.enPd = GpioPdEnable;
    
    ///< LED关闭
    Gpio_ClrIO(GpioPortF, GpioPin5);
    
    ///< GPIO IO LED端口初始化
    Gpio_Init(GpioPortF, GpioPin5, &stcGpioCfg);
    
}

static void App_UserKeyInit(void)
{
    stc_gpio_cfg_t stcGpioCfg;
    
    ///< 打开GPIO外设时钟门控
    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);
    
    ///< 端口方向配置->输入
    stcGpioCfg.enDir = GpioDirIn;
    ///< 端口驱动能力配置->高驱动能力
    stcGpioCfg.enDrv = GpioDrvL;
    ///< 端口上下拉配置->无
    stcGpioCfg.enPu = GpioPuDisable;
    stcGpioCfg.enPd = GpioPdDisable;
    ///< 端口开漏输出配置->开漏输出关闭
    stcGpioCfg.enOD = GpioOdDisable;
    ///< 端口输入/输出值寄存器总线控制模式配置->AHB
    stcGpioCfg.enCtrlMode = GpioAHB;
    ///< GPIO IO USER KEY初始化
    Gpio_Init(GpioPortF, GpioPin4, &stcGpioCfg);    
    
    ///< 打开并配置按键端口为下降沿中断
    Gpio_EnableIrq(GpioPortF, GpioPin4, GpioIrqFalling);
    EnableNvic(PORTD_F_IRQn, IrqLevel3, TRUE);
}

/**
 *@brief 事件调度
 *@return void
 */
static void app_event_sched(void)
{
    app_event = tEvent_get();
    switch(app_event)
    {
        case IDLE_EVENT:
            Lpm_GotoSleep(FALSE);
            break;
        
        
        case LED_EVENT:
        {
            static bool state;
            state = !state;
            if(state)
            {
                Gpio_SetIO(GpioPortF, GpioPin5);
            }
            else
            {
                Gpio_ClrIO(GpioPortF, GpioPin5);
            }
        }
            break;
        
        case DEEP_SLEEP:
            //深度休眠
            tEvent_sleep();
            //恢复软件定时器工作
            tEvent_resume_work();
            break;
        
        default:
            break;
    }
}

int main(void)
{
    //系统时钟配置
	sysclk_drv_init();
    //事件驱动框架初始化
	tEvent_drv_init();
    
    App_LedInit();
    App_UserKeyInit();
    
    //创建事件
    tEvent_ctreate(LED_EVENT, 500);
    tEvent_ctreate(DEEP_SLEEP, 5000);
    
    //开启软件定时器
    tEvent_timer_start(LED_EVENT);
    tEvent_timer_start(DEEP_SLEEP);
    
	while(1)
	{
        app_event_sched();
	}
}
