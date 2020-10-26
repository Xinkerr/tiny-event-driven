#ifndef __TEVENT_CONF_H__
#define __TEVENT_CONF_H__

/******************************************��������**************************************************/
//�����ʱ���¼����Ĺ���
#define tEVENT_RESTART_ENABLE               0

//�޸������ʱ���Ķ�ʱ����ֵ����������ֵ��Ϊ0�����¼����Ĺ���
#define tEVENT_TIMER_MODIFY1_ENABLE         0

//���޸������ʱ���Ķ�ʱ����ֵ������ֵ����
#define tEVENT_TIMER_MODIFY2_ENABLE         0

//���������ȼ�����
#define tEVENT_PRIORITY_ENABLE              1

//�͹������߹���
#define tEVENT_SLEEP_MODE_ENABLE            1
/****************************************************************************************************/

/******************************************��ֲ����**************************************************/
#include <stdint.h>

//�δ�ʱ������
#include "systick.h"
#include "stm32f10x.h"
#define TICK_TIMER_INIT()					systick_timer_init(1000, tEvent_timer_ticking)
#define TICK_TIMER_START()					systick_timer_start()
#define TICK_TIMER_STOP()                   systick_timer_stop()
#define SLEEP_COMMAND()                     {RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);\
                                             PWR_EnterSTOPMode(PWR_Regulator_LowPower,PWR_STOPEntry_WFI);\
                                             __WFI();\
                                             SystemInit();}

//�����ʱ���ļ���ֵ�Ͷ�ʱ����ֵ������
typedef uint16_t _TIME_INT;

//����¼���
#define EVENT_QUE_SIZE					    10 
//�¼�FIFO��������С ����һ�ε����ȼ��¼����뻺����ռ��2���ֽ�
#define EVENT_BUF_SIZE                      16
/****************************************************************************************************/
#endif

