/***************************************************************************
*
* Copyright (c) 2020, Xinkerr
*
* This file is part of example.
*
* Disclaimer:
* AUTHOR MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
* REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS),
* ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING,
* WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED
* WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED
* WARRANTY OF NONINFRINGEMENT.
* AUTHOR SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT,
* NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT
* LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION,
* LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR
* INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA,
* SAVINGS OR PROFITS,
* EVEN IF Disclaimer HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
* INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED
* FROM, THE SOFTWARE.
*
* LICENSE: LGPL V3.0
*
* Date: 2020/11/1
* Version:1.0
*
****************************************************************************/
#include <stdio.h>
#include "sys_config.h"
#include "tEvent.h"
#include "LED.h"
#include "uart.h"
#include "wakeup_timer.h"

//事件ID
typedef enum
{
    LED_EVENT = 1,
    ENTER_SLEEP_EVENT,
    HIGH_PRIORITY_EVENT,
    WAKEUP_EVENT
}event_id_t;

void assert_failed(u8* file, u32 line)
{ 
    /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* Infinite loop */
    while (1)
    {
    }
}

//唤醒时的回调函数
void wakeup_callback(void)
{
    tEvent_put(WAKEUP_EVENT);
    tEvent_put(HIGH_PRIORITY_EVENT);
}

//事件驱动调度
void event_sched(void)
{
    //获取事件
    uint8_t event = tEvent_get();
    switch (event)
    {
    case IDLE_EVENT:
        break;
    //LED闪烁事件
    case LED_EVENT:     
    {
        static uint8_t state = 0;
        state = !state;
        LED1_Control((led_state_t)state);
        printf_string("LED_EVENT!\r\n");
    }
        break;
    //进入低功耗事件
    case ENTER_SLEEP_EVENT: 
        printf_string("ENTER_SLEEP_EVENT!\r\n");
        //开启自动唤醒
        wakeup_timer_enable(AWU_TIMEBASE_30S);
        //进入低功耗
        tEvent_sleep();
        //软件定时器恢复工作
        tEvent_resume_work();
        printf_string("WAKEUP\r\n");
        break;
    //高优先级测试事件
    case HIGH_PRIORITY_EVENT:
        printf_string("HIGH_PRIORITY_EVENT!\r\n");
        break;
    //唤醒事件
    case WAKEUP_EVENT:
        printf_string("WAKEUP_EVENT!\r\n");
        break;

    default:
        break;
    }
}

void main( void )
{
    //系统时钟初始化
    SYSTEM_CLK_INIT();
    //LED端口初始化
    LED_init();
    //串口初始化
    UART1_init(9600);
    //事件驱动框架初始化
    tEvent_drv_init();
    //事件驱动的滴答定时器初始化
    tEvent_tick_start();
    //注册唤醒回调函数
    wakeup_handler_registered(wakeup_callback);
    //创建事件
    tEvent_ctreate(LED_EVENT, 500);
    tEvent_ctreate(ENTER_SLEEP_EVENT, 5000); 
    tEvent_ctreate(HIGH_PRIORITY_EVENT, 0);
    tEvent_ctreate(WAKEUP_EVENT, 0);
    //设定事件优先级
    tEvent_set_priority(HIGH_PRIORITY_EVENT, 1);
    //开启软件定时器
    tEvent_timer_start(LED_EVENT);
    tEvent_timer_start(ENTER_SLEEP_EVENT);
    //使能系统总中断
    enableInterrupts();   
    while(1)
    {
        event_sched();
    }
}
