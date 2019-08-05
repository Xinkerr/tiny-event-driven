/****************************************************
Date：  2019/8/5
Author: 鄭訫
Github: https://github.com/Xinkerr/tiny-event-driver
****************************************************/


#include "eQueque.h"
#include <string.h>
//#include <assert.h>


#define DEBUG_LOG	0
#if 	DEBUG_LOG	
#include <stdio.h>
#endif

static uint8_t event[MSG_QUEQUE_SIZE] = {0};	

static uint8_t write_index;								
static uint8_t read_index;
static uint8_t queque_size;
static _BOOL	_bMirror;

/**@brief     消息队列初始化
 *
 *
 * @param[in] void
 *
 * @return    void
 */
void msgQueque_init(void)
{
//	assert(MSG_QUEQUE_SIZE > 0);
	
//	memset(event, 0, 8*MSG_QUEQUE_SIZE);
	write_index = 0;
	// write_mirror = 0;
	read_index = 0;
	// read_mirror = 0;
	_bMirror = 0;
	queque_size = MSG_QUEQUE_SIZE;
}

/**@brief     消息队列的状态
 *
 * @details   检测消息的队列的状态，用于是否可以写入或读取
 *
 * @param[in] void
 *
 * @return    msgQUEQUE_ERROR：消息队列传入错误
 *			  msgQUEQUE_EMPTY：消息队列空
 *			  msgQUEQUE_FULL ：消息队列满
 *			  msgQUEQUE_NORMAL：消息队列正常
 */
queque_state_m msgQueque_status(void)
{
	if(write_index == read_index)
	{
		if(_bMirror == 0)
		{
			#if 	DEBUG_LOG
        	printf("quequq empty\n");
        	#endif
			return msgQUEQUE_EMPTY;
		}
		else
		{
			#if 	DEBUG_LOG
        	printf("quequq full\n");
        	#endif
			return msgQUEQUE_FULL;
		}
	}

	return msgQUEQUE_NORMAL;
}

/**@brief     加入消息队列
 *
 * @details   将具体的数据内容写入消息队列中
 *
 * @param[in] msgEvent:  消息事件（指向消息的来源、原因，或是消息的名称，或是消息的标志）
 *
 * @return    -1：失败
 *			   0：成功
 */
int8_t msgQueque_put(uint8_t msgEvent)
{
	queque_state_m msg_status;
	msg_status = msgQueque_status();
	//有空间、无异常下加入消息队列数据
	if(msg_status == msgQUEQUE_NORMAL || msg_status == msgQUEQUE_EMPTY)
	{
		event[write_index] = msgEvent;

		if(write_index == queque_size - 1)
		{
			_bMirror = !_bMirror;
			write_index = 0;
		}
		else
		{
			write_index ++;
		}
		#if 	DEBUG_LOG
		printf("write_index:%u\n", write_index);
		#endif
	}
	else
		return QUE_FAIL;

	return QUE_SUCCESS;
}

/**@brief     取出消息队列
 *
 * @details   取出消息队列内的数据
 *
 * @param[in] msgEvent: 消息事件（指向消息的来源、原因，或是消息的名称，或是消息的标志）
 *
 * @return    -1：失败
 *			   0：成功
 */
int8_t msgQueque_get(uint8_t* msgEvent)
{
	queque_state_m msg_status;
	msg_status = msgQueque_status();
	if(msg_status == msgQUEQUE_NORMAL || msg_status == msgQUEQUE_FULL)
	{
		*msgEvent = event[read_index];

		if(read_index == queque_size - 1)
		{
			_bMirror = !_bMirror;
			read_index = 0;
		}
		else
		{
			read_index ++;
		}
		#if 	DEBUG_LOG
		printf("read_index:%u\n", read_index);
		#endif
	}
	else
		return QUE_FAIL;

	return QUE_SUCCESS;
}

