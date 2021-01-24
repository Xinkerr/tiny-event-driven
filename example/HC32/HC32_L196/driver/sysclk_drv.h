#ifndef __SYSCLK_DRV_H__
#define	__SYSCLK_DRV_H__
#include "sysctrl.h"

#define SYSTICK         24000

/**
 *@brief ϵͳʱ������
 *@return void
 */
void sysclk_drv_init(void);

/**
 *@brief systick��ʱ����ʼ��
 *@return void
 */
void systick_init(void);

/**
 *@brief systick ����
 *@return void
 */
void systick_enable(void);

/**
 *@brief systick �ر�
 *@return void
 */
void systick_disable(void);
#endif

