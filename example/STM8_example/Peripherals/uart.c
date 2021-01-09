#include "stm8s_uart1.h"
#include "uart.h"

/**
 * @brief UART1初始化
 * 
 * @param[in] baudrate: 波特率
 */
void UART1_init(uint16_t baudrate)
{   
    UART1_Init(baudrate ,            //配置通讯波特率
               UART1_WORDLENGTH_8D , //配置8位宽度
               UART1_STOPBITS_1 ,    //配置1位停止位
               UART1_PARITY_NO ,     //配置无校验
               UART1_SYNCMODE_CLOCK_DISABLE , //
               UART1_MODE_TXRX_ENABLE //设置USART1发送和接收模式
               );
    
    //UART1_ITConfig(UART1_IT_RXNE , ENABLE);   //使能接收中断
    UART1_Cmd(ENABLE);    //使能USART1
}

/**
 * @brief UART1发送1个字节数据
 * 
 * @param[in] byte_data: 数据
 */
void UART1_send_byte(uint8_t byte_data)
{
    while(UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);        //判断发送数据寄存器是否为空
    UART1_SendData8(byte_data);         
}

/**
 * @brief 打印字符串
 * 
 * @param[in] pdata: 数据地址
 */
void printf_string(uint8_t* pdata)
{
    while(*pdata != 0)
    {
        UART1_send_byte(*pdata);
        pdata++;
    }
}

