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
* Author:  鄭訫
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

#ifndef __TEVENT_H__
#define __TEVENT_H__
#include "eQueque.h"
#include <stdint.h>
#include <stdbool.h>
//#include "type8.h"

//******************添加TICK定时器相关头文件和对应函数************************************
#include "systick.h"
#define TICK_TIMER_INIT()					systick_timer_init(1000, tEvent_timer_ticking)
#define TICK_TIMER_START()					systick_timer_start()
//*****************************************************************************************

typedef uint16_t _TIME_INT;
#define EVENT_QUE_SIZE					3   //范围0~127
#define IDLE							0

void tEvent_init(void);

//void tEvent_tick_start(void);

int8_t tEvent_timer_ctreate(uint8_t event_id, _TIME_INT period);

int8_t tEvent_timer_modify(uint8_t event_id, _TIME_INT period);

int8_t tEvent_timer_start(uint8_t event_id);

int8_t tEvent_timer_restart(uint8_t event_id);

int8_t tEvent_timer_stop(uint8_t event_id);

void tEvent_timer_ticking(void);

uint8_t tEvent_queque_get(void);

//放入事件
#define tEvent_queque_put(event_id)		msgQueque_put(event_id)

#endif

