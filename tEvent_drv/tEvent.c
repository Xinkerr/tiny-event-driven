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
    uint8_t running:1;             //执行状态标志 以表示此定时器是否在执行	
	uint8_t highPri_trigger:1;     //高优先级事件触发标志
    uint8_t save_state:1;
}app_timer_t;


static app_timer_t timer_event[EVENT_QUE_SIZE] = {0};

//ringbuffer
static ringbuffer_t event_ringbuf_obj;
static uint8_t event_buffer[EVENT_BUF_SIZE] = {0};


/**
 * @brief 初始化
 *
 * @details 初始化队列 初始化TICK定时器
 */
void tEvent_drv_init(void)
{
    ringbuffer_init(&event_ringbuf_obj, event_buffer, EVENT_BUF_SIZE);
	TICK_TIMER_INIT();
//	TICK_TIMER_START();
}

/**
 * @brief TICK定时器开 
 *
 * @details 软件定时器的tick计数器开始工作
 */
void tEvent_tick_start(void)
{
	TICK_TIMER_START();
}

/**
 * @brief TICK定时器开 
 *
 * @details 软件定时器的tick计数器开始工作
 */
void tEvent_tick_stop(void)
{
	TICK_TIMER_STOP();
}

/**
 * @brief  创建事件
 *
 * @details   创建事件，初始化事件控制块，赋值软件定时器触发事件时间周期
 *
 * @param[in] event_id：事件的ID
 * @param[in] period  ：事件的周期
 *
 * @return    -1：失败
 *			   0：成功
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
        //检索一边前面数据的是否存在还未创建事件ID
        //保证创建的顺序连续性
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
 * @brief 软件定时事件开始
 *
 * @param[in] 事件ID
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
 * @brief 软件定时事件停止
 *
 * @param[in] 事件ID
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
 * @brief 执行定时器tick计数
 *
 * @details 放入硬件定时器内，每次执行作为tick
 *
 */
void tEvent_timer_ticking(void)
{
	uint8_t i;
	for(i = 0; i < EVENT_QUE_SIZE; i++)
	{
        //事件ID表示后面的事件控制块都未使用
		if(timer_event[i].id != 0)
		{
            //判断该事件控制块是否打开软件定时器
			if(timer_event[i].running == _TIMER_ON)
			{
				timer_event[i].tick_cnt ++;
                //判断是否到达设定的时间，到达则触发事件
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
 * @brief  取出队列内的事件
 *
 * @details 根据FIFO原则取出事件，当队列里没有事件时，return IDLE
 *
 * @return  事件
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
 * @brief  取出当前优先级最高的事件
 *
 * @details 当队列里没有高优先级事件时，return 0
 *
 * @return    -1：失败
 *			   0：成功
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
 * @brief  设置事件的优先级
 *
 * @param[in]  event_id: 事件ID
 *
 * @param[in]  priority: 优先级0~31，数值越大优先级越高
 *
 * @return  事件
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
 * @brief  取出事件
 *
 * @details 有高优先级事件取出高优先级事件，其次取出根据FIFO取出事件，
 *          当连最低优先级的队列里没有事件时，return IDLE
 *
 * @return  事件
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
 * @brief  放入事件
 *
 * @details 优先级0则将事件ID放入FIFO队列中，高优先级则触发标志置位
 */
int8_t tEvent_put(uint8_t event_id)
{
    #if tEVENT_PRIORITY_ENABLE
	uint8_t id_index;
	if(event_id == 0 || event_id > EVENT_QUE_SIZE)
		return -1;
    id_index = event_id - 1;
    //判断是否为高优先级
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
 * @brief  修改软件定时器的时间周期
 *
 * @param[in] event_id：事件的ID
 * @param[in] period  ：事件的周期
 *
 * @return    -1：失败
 *			   0：成功
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
 * @brief  仅仅修改软件定时器的时间周期，并不把计数器重新计数
 *
 * @param[in] event_id：事件的ID
 * @param[in] period  ：事件的周期
 *
 * @return    -1：失败
 *			   0：成功
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
 * @brief  软件定时器重新开始
 *
 * @param[in] event_id：事件的ID
 * @param[in] period  ：事件的周期
 *
 * @return    -1：失败
 *			   0：成功
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
 * @brief     进入低功耗 休眠模式
 *
 * @details   关闭软件定时器，并执行芯片低功耗指令
 *
 */
void tEvent_sleep(void)
{
    uint8_t i;
    //停止TICK定时器
    tEvent_tick_stop();
    //清除已触发的队列中的事件
    ringbuffer_all_clear(&event_ringbuf_obj);
    //清除已触发的高优先级的事件
    //每个软件定时器的计数值清0
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
    //休眠指令
    SLEEP_COMMAND();
    //TICK定时器开启
    tEvent_tick_start();
}

/**
 * @brief     恢复所有软件定时器的工作
 *
 * @details   在进入休眠模式时，会关闭所有的软件定时器。
 *            通过该程序来恢复休眠之前的软件定时器的工作状态。
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
