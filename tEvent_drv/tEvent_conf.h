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
#define tEVENT_SLEEP_MODE_ENABLE            0
/****************************************************************************************************/

/******************************************��ֲ����**************************************************/
//#include <stdint.h>

//�δ�ʱ������

#define TICK_TIMER_INIT()					
#define TICK_TIMER_START()					
#define TICK_TIMER_STOP()                   
#define SLEEP_COMMAND()                     

//�����ʱ���ļ���ֵ�Ͷ�ʱ����ֵ������
typedef uint16_t _TIME_INT;

//����¼���
#define EVENT_QUE_SIZE					    10 
//�¼�FIFO��������С ����һ�ε����ȼ��¼����뻺����ռ��2���ֽ�
#define EVENT_BUF_SIZE                      16
/****************************************************************************************************/
#endif

