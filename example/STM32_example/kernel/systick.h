#ifndef __SYSTICK_H__
#define __SYSTICK_H__
#include <stdint.h>
void systick_timer_init(uint32_t tick_us, void (*sys_callback)(void));
void systick_timer_start(void);
void systick_timer_stop(void);

#endif

