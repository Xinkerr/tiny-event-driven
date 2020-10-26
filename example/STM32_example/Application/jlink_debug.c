
#include "jlink_debug.h"


#if JLINK_DEBUG_LEVEL
/**@brief   Jlink SEGGER_RTT ≥ı ºªØ
 * 
 **/
void jlink_RTT_debug_init(void)
{
    SEGGER_RTT_Init();
//    SEGGER_RTT_printf(0, "jlink_RTT_debug_init \r\n");
    JLINK_INFO_PRINTF("jlink_RTT_debug_init \r\n");
}
#endif



