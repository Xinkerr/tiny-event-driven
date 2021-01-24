#ifndef __SYSCLK_DRV_H__
#define	__SYSCLK_DRV_H__
#include "sysctrl.h"

#define SYSTICK         24000

/**
 *@brief 系统时钟配置
 *@return void
 */
void sysclk_drv_init(void);

/**
 *@brief systick定时器初始化
 *@return void
 */
void systick_init(void);

/**
 *@brief systick 开启
 *@return void
 */
void systick_enable(void);

/**
 *@brief systick 关闭
 *@return void
 */
void systick_disable(void);
#endif

