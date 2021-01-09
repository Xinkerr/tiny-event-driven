#ifndef __UART_H__
#define __UART_H__
#include "stm8s.h"

/**
 * @brief UART1初始化
 * 
 * @param[in] baudrate: 波特率
 */
void UART1_init(uint16_t baudrate);

/**
 * @brief 打印字符串
 * 
 * @param[in] pdata: 数据地址
 */
void printf_string(uint8_t* pdata);

#endif
