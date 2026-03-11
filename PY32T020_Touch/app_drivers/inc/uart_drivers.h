#ifndef _UART_DRIVERS_H_
#define _UART_DRIVERS_H_

#include "app_config.h"

#if APP_UART_ENABLE
typedef struct SqQueue
{
    uint8_t *base;
    uint8_t front, rear;
    uint8_t sq_size;
} SqQueue;
#if UART1_ENABLE
/**
 * @brief  Initialize UART1 with specified baud rate
 * @param  BaudRate : Communication baud rate
 * @retval None
 */												
void UART1_Init(uint32_t BaudRate);
#if (UART1_RX_PIN != NO_PIN)
/**
 * @brief  Read a byte from the UART1 receive queue
 * @param  data : Pointer to store the received byte
 * @retval 0 : Queue is empty
 * @retval 1 : Data valid
 */	
uint8_t UART1_QueueRead(uint8_t *data);
#endif
#if (UART1_TX_PIN != NO_PIN)
/**
 * @brief  Send a byte via UART1
 * @param  data : Byte to send
 * @retval 0 : Transmission failed
 * @retval 1 : Transmission successful
 */	
uint8_t UART1_QueueSend(uint8_t data);
#endif
#endif
#if UART2_ENABLE
/**
 * @brief  Initialize UART2 with specified baud rate
 * @param  BaudRate : Communication baud rate
 * @retval None
 */	
void UART2_Init(uint32_t BaudRate);
#if (UART2_RX_PIN != NO_PIN)
/**
 * @brief  Read a byte from the UART2 receive queue
 * @param  data : Pointer to store the received byte
 * @retval 0 : Queue is empty
 * @retval 1 : Data valid
 */	
uint8_t UART2_QueueRead(uint8_t *data);
#endif
#if (UART2_TX_PIN != NO_PIN)
/**
 * @brief  Send a byte via UART2
 * @param  data : Byte to send
 * @retval 0 : Transmission failed
 * @retval 1 : Transmission successful
 */	
uint8_t UART2_QueueSend(uint8_t data);
#endif
#endif
#if UART3_ENABLE
/**
 * @brief  Initialize UART3 with specified baud rate
 * @param  BaudRate : Communication baud rate
 * @retval None
 */	
void UART3_Init(uint32_t BaudRate);
#if (UART3_RX_PIN != NO_PIN)
/**
 * @brief  Read a byte from the UART3 receive queue
 * @param  data : Pointer to store the received byte
 * @retval 0 : Queue is empty
 * @retval 1 : Data valid
 */	
uint8_t UART3_QueueRead(uint8_t *data);
#endif
#if (UART3_TX_PIN != NO_PIN)
/**
 * @brief  Send a byte via UART3
 * @param  data : Byte to send
 * @retval 0 : Transmission failed
 * @retval 1 : Transmission successful
 */	
uint8_t UART3_QueueSend(uint8_t data);
#endif
#endif
#endif
#endif
