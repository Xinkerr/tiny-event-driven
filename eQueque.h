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

#ifndef __EQUEQUE_H__
#define __EQUEQUE_H__
#include <stdint.h>
#include <stdbool.h>
//#include "type8.h"

#define MSG_QUEQUE_SIZE				16//需0< SIZE <256
typedef bool						_BOOL;//如果用8051则可以用bit

#define QUE_SUCCESS					0
#define QUE_FAIL					-1

typedef enum
{
	msgQUEQUE_EMPTY = 0,			
	msgQUEQUE_FULL,
	msgQUEQUE_NORMAL,
	msgQUEQUE_ERROR
}queque_state_m;


//消息队列初始化
void msgQueque_init(void);
//消息队列的状态
queque_state_m msgQueque_status(void);
//加入消息
int8_t msgQueque_put(uint8_t msgEvent);
//取出消息
int8_t msgQueque_get(uint8_t* msgEvent);

#endif
