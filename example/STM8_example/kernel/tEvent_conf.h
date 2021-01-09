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

//�δ�ʱ������
#include "stm8s.h"
#include "app_tim4.h"
#define TICK_TIMER_INIT()					app_tim4_init(1000)
#define TICK_TIMER_START()					app_tim4_start()
#define TICK_TIMER_STOP()                                       app_tim4_stop()
#define SLEEP_COMMAND()                                         asm("HALT");

//�����ʱ���ļ���ֵ�Ͷ�ʱ����ֵ������
typedef uint16_t _TIME_INT;

//����¼���
#define EVENT_QUE_SIZE					    10 
//�¼�FIFO��������С ����һ�ε����ȼ��¼����뻺����ռ��2���ֽ�
#define EVENT_BUF_SIZE                      16
/****************************************************************************************************/
#endif

