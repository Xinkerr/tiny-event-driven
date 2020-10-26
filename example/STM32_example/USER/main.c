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
* LICENSE: LGPL V2.1
*
* Date: 2020/10/25
* Version:1.0
*
****************************************************************************/
#include "stm32f10x.h"
#include "led.h"
#include "exti.h"
#include "tEvent.h"
#include "jlink_debug.h"

//�����¼�����
typedef enum
{
    LED_BLINK_EVENT = 1,
    LOWPOWER_EVENT,
    EXINT4_EVENT,
    HIGH_PRIORITY_TEST_EVENT
}event_num_t;


void EXTI4_IRQHandler(void)
{	 
	EXTI_ClearITPendingBit(EXTI_Line4);  //���LINE4�ϵ��жϱ�־λ 
    //˳��Ϊ1. EXINT4_EVENT 2. HIGH_PRIORITY_TEST_EVENT
    tEvent_put(EXINT4_EVENT);
    tEvent_put(HIGH_PRIORITY_TEST_EVENT);
}

//�¼�����
static void event_sched(void)
{
    uint8_t event = tEvent_get();
    
    switch(event)
    {
        case IDLE_EVENT:
            
            break;
        
        case LED_BLINK_EVENT:   //LED��˸�¼�
            LED0 = !LED0;
            JLINK_DEBUG_PRINTF("led_blink_event!");
            break;
        
        case LOWPOWER_EVENT:    //����͹����¼�
            JLINK_DEBUG_PRINTF("lowpower_event!");
            //ʹ���ж� ���ڻ���
            exti4_set(ENABLE);
            tEvent_sleep();
            //�ر��ж�
            exti4_set(DISABLE);
            tEvent_resume_work();
            break;
        
        case EXINT4_EVENT:
            JLINK_DEBUG_PRINTF("exint4_event!");
            break;
        
        case HIGH_PRIORITY_TEST_EVENT:
            //���Ը����ȼ�
            JLINK_DEBUG_PRINTF("HIGH_PRIORITY_TEST_EVENT!");
            break;
    }
}



int main(void)
{	
    SystemInit();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
    //Jlink_segger_rtt��ʼ��
    jlink_RTT_debug_init();
     
    //�¼������ܹ���ʼ��
    tEvent_drv_init();
    //�δ�ʱ������
    tEvent_tick_start();
    //LED��ʼ��
    LED_Init();
    //�ⲿ�жϳ�ʼ��
    EXTIX_Init();    
     
    //�����¼�
    tEvent_ctreate(LED_BLINK_EVENT, 500);
    tEvent_ctreate(LOWPOWER_EVENT, 5000);
    tEvent_ctreate(EXINT4_EVENT, 0);
    tEvent_ctreate(HIGH_PRIORITY_TEST_EVENT, 0);
    //�趨���ȼ�
    tEvent_set_priority(HIGH_PRIORITY_TEST_EVENT, 1);
    //����ʱ���¼��������ʱ��
    tEvent_timer_start(LED_BLINK_EVENT);
    tEvent_timer_start(LOWPOWER_EVENT);

	while(1)
	{   
        event_sched();
	}
}

