/***************************************************************************
* ���ܣ�LED 500ms�������5������ߡ�ͨ�����������жϻ��ѡ�
* LED�Ͱ���������ֲ�Թٷ��Ĳο����롣
*
* ����������ο��������κ�����Ų�����
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
    
    ///< ��GPIO����ʱ���ſ�
    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE); 
    
    ///< �˿ڷ�������->���(�������������ϣ����룩���ò���һ��)
    stcGpioCfg.enDir = GpioDirOut;
    ///< �˿�����������->����
    stcGpioCfg.enPu = GpioPuDisable;
    stcGpioCfg.enPd = GpioPdEnable;
    
    ///< LED�ر�
    Gpio_ClrIO(GpioPortF, GpioPin5);
    
    ///< GPIO IO LED�˿ڳ�ʼ��
    Gpio_Init(GpioPortF, GpioPin5, &stcGpioCfg);
    
}

static void App_UserKeyInit(void)
{
    stc_gpio_cfg_t stcGpioCfg;
    
    ///< ��GPIO����ʱ���ſ�
    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);
    
    ///< �˿ڷ�������->����
    stcGpioCfg.enDir = GpioDirIn;
    ///< �˿�������������->����������
    stcGpioCfg.enDrv = GpioDrvL;
    ///< �˿�����������->��
    stcGpioCfg.enPu = GpioPuDisable;
    stcGpioCfg.enPd = GpioPdDisable;
    ///< �˿ڿ�©�������->��©����ر�
    stcGpioCfg.enOD = GpioOdDisable;
    ///< �˿�����/���ֵ�Ĵ������߿���ģʽ����->AHB
    stcGpioCfg.enCtrlMode = GpioAHB;
    ///< GPIO IO USER KEY��ʼ��
    Gpio_Init(GpioPortF, GpioPin4, &stcGpioCfg);    
    
    ///< �򿪲����ð����˿�Ϊ�½����ж�
    Gpio_EnableIrq(GpioPortF, GpioPin4, GpioIrqFalling);
    EnableNvic(PORTD_F_IRQn, IrqLevel3, TRUE);
}

/**
 *@brief �¼�����
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
            //�������
            tEvent_sleep();
            //�ָ������ʱ������
            tEvent_resume_work();
            break;
        
        default:
            break;
    }
}

int main(void)
{
    //ϵͳʱ������
	sysclk_drv_init();
    //�¼�������ܳ�ʼ��
	tEvent_drv_init();
    
    App_LedInit();
    App_UserKeyInit();
    
    //�����¼�
    tEvent_ctreate(LED_EVENT, 500);
    tEvent_ctreate(DEEP_SLEEP, 5000);
    
    //���������ʱ��
    tEvent_timer_start(LED_EVENT);
    tEvent_timer_start(DEEP_SLEEP);
    
	while(1)
	{
        app_event_sched();
	}
}
