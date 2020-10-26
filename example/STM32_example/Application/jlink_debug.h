#ifndef __JLINK_DEBUG_H__
#define __JLINK_DEBUG_H__

//JLINK 调试打印等级 
//0,禁用；
//1,仅INFO生效
//2,INFO、DEBUG生效
#define JLINK_DEBUG_LEVEL   2



#if JLINK_DEBUG_LEVEL
#include "Segger_RTT.h"
#include "Segger_RTT_Conf.h"
#endif

#if JLINK_DEBUG_LEVEL == 2
#define JLINK_DEBUG_PRINTF(format, ...)       SEGGER_RTT_printf(0, "[DEBUG] "format"\n" , ##__VA_ARGS__)
#else
#define JLINK_DEBUG_PRINTF(...)
#endif

#if JLINK_DEBUG_LEVEL
#define JLINK_INFO_PRINTF(format, ...)       SEGGER_RTT_printf(0, "[INFO] "format"\n" , ##__VA_ARGS__)
#else
#define JLINK_INFO_PRINTF(...)
#endif


#if JLINK_DEBUG_LEVEL
/**@brief   Jlink SEGGER_RTT 初始化
 * 
 **/
void jlink_RTT_debug_init(void);
#endif

#endif

