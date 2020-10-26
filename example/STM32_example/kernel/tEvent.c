/***************************************************************************
*
* Copyright (c) 2019 - 2020, Xinkerr
*
* This file is part of tiny-event-driven.
*
* this is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
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
* see: http://www.gnu.org/licenses/lgpl-3.0.html
*
* Create Date:   2019/8/5
* Modified Date: 2020/10/20
* Version:2.0
* Github: https://github.com/Xinkerr
* Mail: 634326056@qq.com
*
****************************************************************************/

#include "tEvent.h"
#include "ringbuffer.h"

#define _TIMER_ON			1
#define _TIMER_OFF			0
typedef struct
{
	uint8_t id;
	_TIME_INT tick_cnt;         
	_TIME_INT period;
	uint8_t priority:5;            //0~31
    uint8_t running:1;             //ִ��״̬��־ �Ա�ʾ�˶�ʱ���Ƿ���ִ��	
	uint8_t highPri_trigger:1;     //�����ȼ��¼�������־
    uint8_t save_state:1;
}app_timer_t;


static app_timer_t timer_event[EVENT_QUE_SIZE] = {0};

//ringbuffer
static ringbuffer_t event_ringbuf_obj;
static uint8_t event_buffer[EVENT_BUF_SIZE] = {0};


/**
 * @brief ��ʼ��
 *
 * @details ��ʼ������ ��ʼ��TICK��ʱ��
 */
void tEvent_drv_init(void)
{
    ringbuffer_init(&event_ringbuf_obj, event_buffer, EVENT_BUF_SIZE);
	TICK_TIMER_INIT();
//	TICK_TIMER_START();
}

/**
 * @brief TICK��ʱ���� 
 *
 * @details �����ʱ����tick��������ʼ����
 */
void tEvent_tick_start(void)
{
	TICK_TIMER_START();
}

/**
 * @brief TICK��ʱ���� 
 *
 * @details �����ʱ����tick��������ʼ����
 */
void tEvent_tick_stop(void)
{
	TICK_TIMER_STOP();
}

/**
 * @brief  �����¼�
 *
 * @details   �����¼�����ʼ���¼����ƿ飬��ֵ�����ʱ�������¼�ʱ������
 *
 * @param[in] event_id���¼���ID
 * @param[in] period  ���¼�������
 *
 * @return    -1��ʧ��
 *			   0���ɹ�
 */
int8_t tEvent_ctreate(uint8_t event_id, _TIME_INT period)
{
	uint8_t id_index;
	if(event_id == 0 || event_id > EVENT_QUE_SIZE)
	{
		return -1;
	}
	else if(event_id != 1)
	{
		uint8_t i;
        //����һ��ǰ�����ݵ��Ƿ���ڻ�δ�����¼�ID
        //��֤������˳��������
		for(i = 0; i < event_id-1; i++)
		{
			if(timer_event[i].id == 0)
				return -1;
		}
	}
	id_index = event_id - 1;
	timer_event[id_index].id = event_id;
	timer_event[id_index].period = period;
	timer_event[id_index].priority = 0;
	return 0;
}

/**
 * @brief �����ʱ�¼���ʼ
 *
 * @param[in] �¼�ID
 *
 */
int8_t tEvent_timer_start(uint8_t event_id)
{
	uint8_t id_index;
	if(event_id == 0 || event_id > EVENT_QUE_SIZE)
		return -1;
	
	id_index = event_id - 1;
	timer_event[id_index].running = _TIMER_ON;
	return 0;
}

/**
 * @brief �����ʱ�¼�ֹͣ
 *
 * @param[in] �¼�ID
 *
 */
int8_t tEvent_timer_stop(uint8_t event_id)
{
	uint8_t id_index;
	if(event_id == 0 || event_id > EVENT_QUE_SIZE)
		return -1;
	
	id_index = event_id - 1;
	timer_event[id_index].running = _TIMER_OFF;
	timer_event[id_index].tick_cnt = 0;
	return 0;
}

/**
 * @brief ִ�ж�ʱ��tick����
 *
 * @details ����Ӳ����ʱ���ڣ�ÿ��ִ����Ϊtick
 *
 */
void tEvent_timer_ticking(void)
{
	uint8_t i;
	for(i = 0; i < EVENT_QUE_SIZE; i++)
	{
        //�¼�ID��ʾ������¼����ƿ鶼δʹ��
		if(timer_event[i].id != 0)
		{
            //�жϸ��¼����ƿ��Ƿ�������ʱ��
			if(timer_event[i].running == _TIMER_ON)
			{
				timer_event[i].tick_cnt ++;
                //�ж��Ƿ񵽴��趨��ʱ�䣬�����򴥷��¼�
				if(timer_event[i].tick_cnt >= timer_event[i].period)
				{
					timer_event[i].tick_cnt = 0;
                    
                    #if tEVENT_PRIORITY_ENABLE
					if(timer_event[i].priority == 0)
						ringbuffer_put(&event_ringbuf_obj, &timer_event[i].id, 1);
					else
						timer_event[i].highPri_trigger = 1;
                    #else
                    ringbuffer_put(&event_ringbuf_obj, &timer_event[i].id, 1);
                    #endif
				}
			}
		}
		else
		{
			return;
		}
	}
}

/**
 * @brief  ȡ�������ڵ��¼�
 *
 * @details ����FIFOԭ��ȡ���¼�����������û���¼�ʱ��return IDLE
 *
 * @return  �¼�
 */
uint8_t tEvent_queque_get(void)
{
	uint8_t event_id;
	if(ringbuffer_get(&event_ringbuf_obj, &event_id, 1) == RINGBUF_OK)
	{
		return event_id;
	}
	else
	{
		return IDLE_EVENT;
	}
}

#if tEVENT_PRIORITY_ENABLE
/**
 * @brief  ȡ����ǰ���ȼ���ߵ��¼�
 *
 * @details ��������û�и����ȼ��¼�ʱ��return 0
 *
 * @return    -1��ʧ��
 *			   0���ɹ�
 */
uint8_t tEvent_priority_get(void)
{
	uint8_t i;
	uint8_t index_tmp = 0;
	uint8_t priority_highest = 0;
	for(i = 0; i < EVENT_QUE_SIZE; i++)
	{
		if(timer_event[i].id != 0)
		{
			if(timer_event[i].highPri_trigger)
			{
				if(timer_event[i].priority > priority_highest)
				{
					priority_highest = timer_event[i].priority;
					index_tmp = i;
				}
			}
		}
		else
		{
			break;
		}
	}
	
	if(priority_highest != 0)
	{
		timer_event[index_tmp].highPri_trigger = 0;
		return timer_event[index_tmp].id;
	}
	else
	{
		return 0;
	}
}

/**
 * @brief  �����¼������ȼ�
 *
 * @param[in]  event_id: �¼�ID
 *
 * @param[in]  priority: ���ȼ�0~31����ֵԽ�����ȼ�Խ��
 *
 * @return  �¼�
 */
int8_t tEvent_set_priority(uint8_t event_id, uint8_t priority)
{
    uint8_t id_index;
	if(event_id == 0 || event_id > EVENT_QUE_SIZE)
		return -1;
	
	id_index = event_id - 1;
    timer_event[id_index].priority = priority;
    return 0;
}
#endif

/**
 * @brief  ȡ���¼�
 *
 * @details �и����ȼ��¼�ȡ�������ȼ��¼������ȡ������FIFOȡ���¼���
 *          ����������ȼ��Ķ�����û���¼�ʱ��return IDLE
 *
 * @return  �¼�
 */
uint8_t tEvent_get(void)
{
	uint8_t ret_id;
    #if tEVENT_PRIORITY_ENABLE
	ret_id = tEvent_priority_get();
	if(ret_id)
	{
		return ret_id;
	}
	else
	{
		ret_id = tEvent_queque_get();
		return ret_id;
	}
    #else
    ret_id = tEvent_queque_get();
	return ret_id;    
    #endif
    
}

/**
 * @brief  �����¼�
 *
 * @details ���ȼ�0���¼�ID����FIFO�����У������ȼ��򴥷���־��λ
 */
int8_t tEvent_put(uint8_t event_id)
{
    #if tEVENT_PRIORITY_ENABLE
	uint8_t id_index;
	if(event_id == 0 || event_id > EVENT_QUE_SIZE)
		return -1;
    id_index = event_id - 1;
    //�ж��Ƿ�Ϊ�����ȼ�
    if(timer_event[id_index].priority > 0)
        timer_event[id_index].highPri_trigger = 1;
    else
        ringbuffer_put(&event_ringbuf_obj, &event_id, 1);
    #else
    if(event_id == 0 || event_id > EVENT_QUE_SIZE)
		return -1;
    ringbuffer_put(&event_ringbuf_obj, &event_id, 1);
    #endif
    return 0;
}



#if tEVENT_TIMER_MODIFY1_ENABLE
/**
 * @brief  �޸������ʱ����ʱ������
 *
 * @param[in] event_id���¼���ID
 * @param[in] period  ���¼�������
 *
 * @return    -1��ʧ��
 *			   0���ɹ�
 */
int8_t tEvent_timer_modify(uint8_t event_id, _TIME_INT period)
{
	uint8_t id_index;
	if(event_id == 0 || event_id > EVENT_QUE_SIZE)
		return -1;
	
	id_index = event_id - 1;
	timer_event[id_index].tick_cnt = 0;
	timer_event[id_index].period = period;
	return 0;
}
#endif

#if tEVENT_TIMER_MODIFY2_ENABLE
/**
 * @brief  �����޸������ʱ����ʱ�����ڣ������Ѽ��������¼���
 *
 * @param[in] event_id���¼���ID
 * @param[in] period  ���¼�������
 *
 * @return    -1��ʧ��
 *			   0���ɹ�
 */
int8_t tEvent_timer_Justmodify(uint8_t event_id, _TIME_INT period)
{
	uint8_t id_index;
	if(event_id == 0 || event_id > EVENT_QUE_SIZE)
		return -1;
	
	id_index = event_id - 1;
	timer_event[id_index].period = period;
	return 0;
}
#endif

#if tEVENT_RESTART_ENABLE
/**
 * @brief  �����ʱ�����¿�ʼ
 *
 * @param[in] event_id���¼���ID
 * @param[in] period  ���¼�������
 *
 * @return    -1��ʧ��
 *			   0���ɹ�
 */
int8_t tEvent_timer_restart(uint8_t event_id)
{
	uint8_t id_index;
	if(event_id == 0 || event_id > EVENT_QUE_SIZE)
		return -1;
	
	id_index = event_id - 1;
	timer_event[id_index].tick_cnt = 0;
	timer_event[id_index].running = 1;
	return 0;
}
#endif

//--------------------------------------SLEEP MODE-------------------------------------------

#if tEVENT_SLEEP_MODE_ENABLE

/**
 * @brief     ����͹��� ����ģʽ
 *
 * @details   �ر������ʱ������ִ��оƬ�͹���ָ��
 *
 */
void tEvent_sleep(void)
{
    uint8_t i;
    //ֹͣTICK��ʱ��
    tEvent_tick_stop();
    //����Ѵ����Ķ����е��¼�
    ringbuffer_all_clear(&event_ringbuf_obj);
    //����Ѵ����ĸ����ȼ����¼�
    //ÿ�������ʱ���ļ���ֵ��0
    for(i = 0; i < EVENT_QUE_SIZE; i++)
    {
        if(timer_event[i].id != 0)
        {
            timer_event[i].tick_cnt = 0;
            timer_event[i].highPri_trigger = 0;
            timer_event[i].save_state = timer_event[i].running;
            timer_event[i].running = 0;
        }
        else 
            break;
    }
    //����ָ��
    SLEEP_COMMAND();
    //TICK��ʱ������
    tEvent_tick_start();
}

/**
 * @brief     �ָ����������ʱ���Ĺ���
 *
 * @details   �ڽ�������ģʽʱ����ر����е������ʱ����
 *            ͨ���ó������ָ�����֮ǰ�������ʱ���Ĺ���״̬��
 *
 */
void tEvent_resume_work(void)
{
    uint8_t i;
    for(i = 0; i < EVENT_QUE_SIZE; i++)
    {
        if(timer_event[i].id != 0)
        {
            timer_event[i].running = timer_event[i].save_state;
            timer_event[i].save_state = 0;
        }
        else 
            break;
    }
}

#endif
