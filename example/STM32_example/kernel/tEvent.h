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
 * @brief 初始化
 *
 * @details 初始化队列 初始化TICK定时器
 */
void tEvent_drv_init(void);

/**
 * @brief TICK定时器开 
 *
 * @details 软件定时器的tick计数器开始工作
 */
void tEvent_tick_start(void);

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
int8_t tEvent_ctreate(uint8_t event_id, _TIME_INT period);

/**
 * @brief 软件定时事件开始
 *
 * @param[in] 事件ID
 *
 */
int8_t tEvent_timer_start(uint8_t event_id);

/**
 * @brief 软件定时事件停止
 *
 * @param[in] 事件ID
 *
 */
int8_t tEvent_timer_stop(uint8_t event_id);

/**
 * @brief 执行定时器tick计数
 *
 * @details 放入硬件定时器内，每次执行作为tick
 *
 */
void tEvent_timer_ticking(void);

/**
 * @brief  取出事件
 *
 * @details 当连最低优先级的队列里没有事件时，return IDLE
 *
 * @return  事件
 */
uint8_t tEvent_get(void);

/**
 * @brief  放入事件
 *
 * @details 优先级0则将事件ID放入FIFO队列中，高优先级则触发标志置位
 */
int8_t tEvent_put(uint8_t event_id);

#if tEVENT_PRIORITY_ENABLE
/**
 * @brief  设置事件的优先级
 *
 * @param[in]  event_id: 事件ID
 *
 * @param[in]  priority: 优先级0~63，数值越大优先级越高
 *
 * @return  事件
 */
int8_t tEvent_set_priority(uint8_t event_id, uint8_t priority);
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
int8_t tEvent_timer_restart(uint8_t event_id);
#endif

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
int8_t tEvent_timer_modify(uint8_t event_id, _TIME_INT period);
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
int8_t tEvent_timer_Justmodify(uint8_t event_id, _TIME_INT period);
#endif

#if tEVENT_SLEEP_MODE_ENABLE
/**
 * @brief     进入低功耗 休眠模式
 *
 * @details   关闭软件定时器，并执行芯片低功耗指令
 *
 */
void tEvent_sleep(void);

/**
 * @brief     恢复所有软件定时器的工作
 *
 * @details   在进入休眠模式时，会关闭所有的软件定时器。
 *            通过该程序来恢复休眠之前的软件定时器的工作状态。
 *
 */
void tEvent_resume_work(void);
#endif

#endif

