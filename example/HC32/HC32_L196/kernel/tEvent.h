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

#ifndef __TEVENT_H__
#define __TEVENT_H__

#include "tEvent_conf.h"
 
#define  IDLE_EVENT							0

/**
 * @brief ��ʼ��
 *
 * @details ��ʼ������ ��ʼ��TICK��ʱ��
 */
void tEvent_drv_init(void);

/**
 * @brief TICK��ʱ���� 
 *
 * @details �����ʱ����tick��������ʼ����
 */
void tEvent_tick_start(void);

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
int8_t tEvent_ctreate(uint8_t event_id, _TIME_INT period);

/**
 * @brief �����ʱ�¼���ʼ
 *
 * @param[in] �¼�ID
 *
 */
int8_t tEvent_timer_start(uint8_t event_id);

/**
 * @brief �����ʱ�¼�ֹͣ
 *
 * @param[in] �¼�ID
 *
 */
int8_t tEvent_timer_stop(uint8_t event_id);

/**
 * @brief ִ�ж�ʱ��tick����
 *
 * @details ����Ӳ����ʱ���ڣ�ÿ��ִ����Ϊtick
 *
 */
void tEvent_timer_ticking(void);

/**
 * @brief  ȡ���¼�
 *
 * @details ����������ȼ��Ķ�����û���¼�ʱ��return IDLE
 *
 * @return  �¼�
 */
uint8_t tEvent_get(void);

/**
 * @brief  �����¼�
 *
 * @details ���ȼ�0���¼�ID����FIFO�����У������ȼ��򴥷���־��λ
 */
int8_t tEvent_put(uint8_t event_id);

#if tEVENT_PRIORITY_ENABLE
/**
 * @brief  �����¼������ȼ�
 *
 * @param[in]  event_id: �¼�ID
 *
 * @param[in]  priority: ���ȼ�0~63����ֵԽ�����ȼ�Խ��
 *
 * @return  �¼�
 */
int8_t tEvent_set_priority(uint8_t event_id, uint8_t priority);
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
int8_t tEvent_timer_restart(uint8_t event_id);
#endif

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
int8_t tEvent_timer_modify(uint8_t event_id, _TIME_INT period);
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
int8_t tEvent_timer_Justmodify(uint8_t event_id, _TIME_INT period);
#endif

#if tEVENT_SLEEP_MODE_ENABLE
/**
 * @brief     ����͹��� ����ģʽ
 *
 * @details   �ر������ʱ������ִ��оƬ�͹���ָ��
 *
 */
void tEvent_sleep(void);

/**
 * @brief     �ָ����������ʱ���Ĺ���
 *
 * @details   �ڽ�������ģʽʱ����ر����е������ʱ����
 *            ͨ���ó������ָ�����֮ǰ�������ʱ���Ĺ���״̬��
 *
 */
void tEvent_resume_work(void);
#endif

#endif

