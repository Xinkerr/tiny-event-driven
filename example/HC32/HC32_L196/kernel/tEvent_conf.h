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
#define tEVENT_PRIORITY_ENABLE              0

//�͹������߹���
#define tEVENT_SLEEP_MODE_ENABLE            1
/****************************************************************************************************/

/******************************************��ֲ����**************************************************/
#include <stdint.h>
#include "sysclk_drv.h"
#include "lpm.h"

//�δ�ʱ������

#define TICK_TIMER_INIT()                   systick_init()					
#define TICK_TIMER_START()                  systick_enable()					
#define TICK_TIMER_STOP()                   systick_disable()                   
#define SLEEP_COMMAND()                     Lpm_GotoDeepSleep(FALSE)

//�����ʱ���ļ���ֵ�Ͷ�ʱ����ֵ������
typedef uint16_t _TIME_INT;

//����¼���
#define EVENT_QUE_SIZE					    10 
//�¼�FIFO��������С ����һ�ε����ȼ��¼����뻺����ռ��2���ֽ�
#define EVENT_BUF_SIZE                      16
/****************************************************************************************************/
#endif

