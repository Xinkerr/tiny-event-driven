/***************************************************************************
*
* Copyright (c) 2019, Xinkerr
*
* This file is part of tiny event driver.
*
* tiny event driver is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* tiny event driver is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with tiny event driver.  If not, see <https://www.gnu.org/licenses/>.
*	
* LICENSE: LGPL V3.0
* see: http://www.gnu.org/licenses/lgpl-3.0.html
*
* Date:    2019/8/5
* Author:  ���M
* Version: 1.0
* Github:  https://github.com/Xinkerr/tiny-event-driver
* Mail:    634326056@qq.com
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
****************************************************************************/

#include "tEvent.h"

#define _TIMER_ON			1
#define _TIMER_OFF			0
typedef struct
{
	uint8_t id:7;
	uint8_t running:1;             //ִ��״̬��־ �Ա�ʾ�˶�ʱ���Ƿ���ִ��	
	_TIME_INT tick_cnt;         
	_TIME_INT period;
}app_timer_t;


static app_timer_t timer_event[EVENT_QUE_SIZE] = {0};

/**@brief ��ʼ��
 *
 * @details ��ʼ������ ��ʼ��TICK��ʱ��
 */
void tEvent_init(void)
{
	
	msgQueque_init();
	TICK_TIMER_INIT();
	TICK_TIMER_START();
}

///**@brief TICK��ʱ���� 
// *
// * @details �����ʱ����tick��������ʼ����
// */
//void tEvent_tick_start(void)
//{
//	TICK_TIMER_START();
//}

/**@brief  ��������ʱ��ʱ���¼�
 *
 * @param[in] event_id���¼���ID
 * @param[in] period  ���¼�������
 *
 * @return    -1��ʧ��
 *			   0���ɹ�
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

/**@brief  �޸������ʱ����ʱ������
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

/**@brief  �����ʱ�����¿�ʼ
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
	timer_event[id_index].running = _TIMER_ON;
	return 0;
}

/**@brief �����ʱ�¼���ʼ
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

/**@brief �����ʱ�¼�ֹͣ
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

/**@brief ִ�ж�ʱ��tick����
 *
 * @details ����Ӳ����ʱ���ڣ�ÿ��ִ����Ϊtick
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

/**@brief  ȡ���¼�
 *
 * @details ��������û���¼�ʱ��return IDLE
 *
 * @return  �¼�
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

///**@brief  �����¼�
// *
// * @details ���¼�ID���������
// */
//void tEvent_queque_put(uint8_t event_id)
//{
//	msgQueque_put(event_id);
//}




