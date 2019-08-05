#include "tEvent.h"

#define _TIMER_ON			1
#define _TIMER_OFF			0
typedef struct
{
	uint8_t id:7;
	uint8_t running:1;             //执行状态标志 以表示此定时器是否在执行	
	_TIME_INT tick_cnt;         
	_TIME_INT period;
}app_timer_t;


static app_timer_t timer_event[EVENT_QUE_SIZE] = {0};

/**@brief 初始化
 *
 * @details 初始化队列 初始化TICK定时器
 */
void tEvent_init(void)
{
	
	msgQueque_init();
	TICK_TIMER_INIT();
	TICK_TIMER_START();
}

///**@brief TICK定时器开 
// *
// * @details 软件定时器的tick计数器开始工作
// */
//void tEvent_tick_start(void)
//{
//	TICK_TIMER_START();
//}

/**@brief  添加软件定时器时间事件
 *
 * @param[in] event_id：事件的ID
 * @param[in] period  ：事件的周期
 *
 * @return    -1：失败
 *			   0：成功
 */
int8_t tEvent_timer_ctreate(uint8_t event_id, _TIME_INT period)
{
	uint8_t id_index;
	if(event_id == 0 || event_id > EVENT_QUE_SIZE)
	{
		return -1;
	}
	else if(event_id != 1)
	{
		uint8_t i;
		for(i = 0; i < event_id-1; i++)
		{
			if(timer_event[i].id == 0)
				return -1;
		}
	}
	id_index = event_id - 1;
	timer_event[id_index].id = event_id;
	timer_event[id_index].period = period;
	return 0;
}

/**@brief  修改软件定时器的时间周期
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

/**@brief  软件定时器重新开始
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
	timer_event[id_index].running = _TIMER_ON;
	return 0;
}

/**@brief 软件定时事件开始
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

/**@brief 软件定时事件停止
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

/**@brief 执行定时器tick计数
 *
 * @details 放入硬件定时器内，每次执行作为tick
 *
 */
void tEvent_timer_ticking(void)
{
	uint8_t i;
	for(i = 0; i < EVENT_QUE_SIZE; i++)
	{
		if(timer_event[i].id != 0)
		{
			if(timer_event[i].running == _TIMER_ON)
			{
				timer_event[i].tick_cnt ++;
				if(timer_event[i].tick_cnt == timer_event[i].period)
				{
					timer_event[i].tick_cnt = 0;
					msgQueque_put(timer_event[i].id);
				}
			}
		}
		else
		{
			return;
		}
	}
}

/**@brief  取出事件
 *
 * @details 当队列里没有事件时，return IDLE
 *
 * @return  事件
 */
uint8_t tEvent_queque_get(void)
{
	uint8_t event_id;
	if(msgQueque_get(&event_id) == QUE_SUCCESS)
	{
		return event_id;
	}
	else
	{
		return IDLE;
	}
}

///**@brief  放入事件
// *
// * @details 把事件ID放入队列中
// */
//void tEvent_queque_put(uint8_t event_id)
//{
//	msgQueque_put(event_id);
//}




