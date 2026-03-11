#include "uart_drivers.h"
#if APP_UART_ENABLE
/**
 * @brief  UART_QueueRead
 * @param  None
 * @retval None
 */
static uint8_t UART_QueueRead(SqQueue *Queue, uint8_t *data)
{
    if (Queue->rear == Queue->front)
    {
        return 0;
    }
    *data = Queue->base[Queue->front];
    Queue->front = (Queue->front + 1) % Queue->sq_size;
    return 1;
}
/**
 * @brief  UART_QueueSend
 * @param  None
 * @retval None
 */
static uint8_t UART_QueueSend(UART_TypeDef *UARTx, SqQueue *Queue, uint8_t data)
{
    if (Queue == NULL)
    {
        UARTx->DR = data;
        while ((UARTx->SR & UART_SR_TXE) == 0)
            ;
    }
    else
    {
        /**
 * @brief  Documentation
 */
        while (((Queue->rear + 1) % Queue->sq_size) == Queue->front)
        {
            ;
        }
        Queue->base[Queue->rear] = data;
        Queue->rear = (Queue->rear + 1) % Queue->sq_size;
        /**
 * @brief  Documentation
 */
        UARTx->CR2 |= UART_CR2_TDREIE;
    }
    return 1;
}
/**
 * @brief  UART_IRQHandler
 * @param  None
 * @retval None
 */
static void UART_IRQHandler(UART_TypeDef *UARTx, SqQueue *Queue_rx, SqQueue *Queue_tx)
{
    uint32_t isrflags = UARTx->SR;
    if (isrflags & UART_SR_RXNE && UARTx->CR2 & UART_CR2_RXNEIE)
    {
        uint8_t DATA = UARTx->DR;
        if (((Queue_rx->rear + 1) % Queue_rx->sq_size) == Queue_rx->front)
        {
            /**
 * @brief  Documentation
 */
        }
        else
        {
            Queue_rx->base[Queue_rx->rear] = DATA;
            Queue_rx->rear = (Queue_rx->rear + 1) % Queue_rx->sq_size;
        }
    }
    if (isrflags & UART_SR_TDRE && UARTx->CR2 & UART_CR2_TDREIE)
    {
        /**
 * @brief  Documentation
 */
        if (Queue_tx->rear == Queue_tx->front)
        {
            UARTx->CR2 &= ~UART_CR2_TDREIE;
        }
        else
        {
			UARTx->DR = Queue_tx->base[Queue_tx->front];
            Queue_tx->front = (Queue_tx->front + 1) % Queue_tx->sq_size;
        }
    }
    if (isrflags & UART_SR_ORE)
    {
        UARTx->SR |= UART_SR_ORE;
    }
    if (isrflags & UART_SR_FE)
    {
        UARTx->SR |= UART_SR_FE;
    }
}
#if UART1_ENABLE
static SqQueue uart1_tx;
static SqQueue uart1_rx;
#if (UART1_TX_PIN != NO_PIN)
static uint8_t uart1_tx_fifo[64];
#endif
#if (UART1_RX_PIN != NO_PIN)
static uint8_t uart1_rx_fifo[64];
#endif
#define UART1_SWAP						  0			/**
 * @brief  Documentation
 */
/**
 * @brief  UART1_Init
 * @param  None
 * @retval None
 */												
void UART1_Init(uint32_t BaudRate)
{
	/* Set UART feature */
	LL_UART_InitTypeDef UART_InitStruct = {0};
	/* Enable UART1 peripheral clock */
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART1);
	/* Set baud rate */
	UART_InitStruct.BaudRate = BaudRate;
	/* set word length to 8 bits: Start bit, 8 data bits, n stop bits */
	UART_InitStruct.DataWidth = LL_UART_DATAWIDTH_8B;
	/* 1 stop bit */
	UART_InitStruct.StopBits = LL_UART_STOPBITS_1;
	/* Parity control disabled  */
	UART_InitStruct.Parity = LL_UART_PARITY_NONE;
	/* MSB first disable */
	UART_InitStruct.BitOrder = LL_UART_BITORDER_LSBFIRST;
	/* Initialize UART */
	LL_UART_Init(UART1, &UART_InitStruct);
	 /* Sends an amount of data in non blocking mode. */
	UART1->CR1 |= (UART1_SWAP << 8);
	#if (UART1_TX_PIN != NO_PIN)
	GPIO_Init(UART1_TX_PIN,ALTERNATE | PUSHPULL | GPIO_UART1);
    uart1_tx.base = uart1_tx_fifo;
    uart1_tx.front = uart1_tx.rear = 0;
    uart1_tx.sq_size = sizeof(uart1_tx_fifo);
	#endif
	#if (UART1_RX_PIN != NO_PIN)
	GPIO_Init(UART1_RX_PIN,ALTERNATE | PULL_UP | GPIO_UART1);
	uart1_rx.base = uart1_rx_fifo;
    uart1_rx.front = uart1_rx.rear = 0;
    uart1_rx.sq_size = sizeof(uart1_rx_fifo);
    UART1->CR2 |= UART_CR2_RXNEIE | UART_CR2_LSIE | UART_CR2_BUSYERRIE;
	#endif
	#if UART1_IRQ_ENABLE
	/* Enable UART interrupt */
	NVIC_SetPriority(UART1_IRQn,UART1_IRQ_PRIORITY);
	NVIC_EnableIRQ(UART1_IRQn);
	#endif
}
/**
 * @brief  UART1_IRQHandler
 * @param  None
 * @retval None
 */	
void UART1_IRQHandler(void)
{
	__disable_irq();
	UART_IRQHandler(UART1,&uart1_rx,&uart1_tx);
	__enable_irq();
}
#if (UART1_RX_PIN != NO_PIN)
/**
 * @brief  UART1_QueueRead
 * @param  None
 * @retval None
 */	
uint8_t UART1_QueueRead(uint8_t *data)
{
	#if UART1_IRQ_ENABLE
	return UART_QueueRead(&uart1_rx,data);
	#else
    if (UART1->SR & UART_SR_RXNE)
    {
        *data = UART1->DR;
		return 1;
	}
	return 0;
	#endif
}
#endif
#if (UART1_TX_PIN != NO_PIN)
/**
 * @brief  UART1_QueueSend
 * @param  None
 * @retval None
 */	
uint8_t UART1_QueueSend(uint8_t data)
{
	#if UART1_IRQ_ENABLE
	return UART_QueueSend(UART1,&uart1_tx,data);
	#else
	return UART_QueueSend(UART1,NULL,data);
	#endif
}
#endif
#endif

#if UART2_ENABLE
static SqQueue uart2_tx;
static SqQueue uart2_rx;
#if (UART2_TX_PIN != NO_PIN)
static uint8_t uart2_tx_fifo[64];
#endif
#if (UART2_RX_PIN != NO_PIN)
static uint8_t uart2_rx_fifo[64];
#endif
#define UART2_SWAP						  0			/**
 * @brief  Documentation
 */
/**
 * @brief  UART2_Init
 * @param  None
 * @retval None
 */	
void UART2_Init(uint32_t BaudRate)
{
	/* Set UART feature */
	LL_UART_InitTypeDef UART_InitStruct = {0};
	/* Enable UART1 peripheral clock */
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART2);
	/* Set baud rate */
	UART_InitStruct.BaudRate = BaudRate;
	/* set word length to 8 bits: Start bit, 8 data bits, n stop bits */
	UART_InitStruct.DataWidth = LL_UART_DATAWIDTH_8B;
	/* 1 stop bit */
	UART_InitStruct.StopBits = LL_UART_STOPBITS_1;
	/* Parity control disabled  */
	UART_InitStruct.Parity = LL_UART_PARITY_NONE;
	/* MSB first disable */
	UART_InitStruct.BitOrder = LL_UART_BITORDER_LSBFIRST;
	/* Initialize UART */
	LL_UART_Init(UART2, &UART_InitStruct);
	 /* Sends an amount of data in non blocking mode. */
	UART2->CR1 |= (UART2_SWAP << 8);
    /**
 * @brief  Documentation
 */
	#if (UART2_TX_PIN != NO_PIN)
	GPIO_Init(UART2_TX_PIN,ALTERNATE | PUSHPULL | GPIO_UART2);
    uart2_tx.base = uart2_tx_fifo;
    uart2_tx.front = uart2_tx.rear = 0;
    uart2_tx.sq_size = sizeof(uart2_tx_fifo);
	#endif
	#if (UART2_RX_PIN != NO_PIN)
	GPIO_Init(UART2_RX_PIN,ALTERNATE | PULL_UP | GPIO_UART2);
    uart2_rx.base = uart2_rx_fifo;
    uart2_rx.front = uart2_rx.rear = 0;
    uart2_rx.sq_size = sizeof(uart2_rx_fifo);
    UART2->CR2 |= UART_CR2_RXNEIE | UART_CR2_LSIE | UART_CR2_BUSYERRIE;
	#endif
	#if UART2_IRQ_ENABLE
	/* Enable UART interrupt */
	NVIC_SetPriority(UART2_IRQn,UART2_IRQ_PRIORITY);
	NVIC_EnableIRQ(UART2_IRQn);
	#endif
}
/**
 * @brief  UART2_IRQHandler
 * @param  None
 * @retval None
 */	
void UART2_IRQHandler(void)
{
	__disable_irq();
	UART_IRQHandler(UART2,&uart2_rx,&uart2_tx);
	__enable_irq();
}
#if (UART2_RX_PIN != NO_PIN)
/**
 * @brief  UART2_QueueRead
 * @param  None
 * @retval None
 */	
uint8_t UART2_QueueRead(uint8_t *data)
{
	#if UART2_IRQ_ENABLE
	return UART_QueueRead(&uart2_rx,data);
	#else
    if (UART2->SR & UART_SR_RXNE)
    {
        *data = UART2->DR;
		return 1;
	}
	return 0;
	#endif
}
#endif
#if (UART2_TX_PIN != NO_PIN)
/**
 * @brief  UART2_QueueSend
 * @param  None
 * @retval None
 */	
uint8_t UART2_QueueSend(uint8_t data)
{
	#if UART2_IRQ_ENABLE
	return UART_QueueSend(UART2,&uart2_tx,data);
	#else
	return UART_QueueSend(UART2,NULL,data);
	#endif
}
#endif
#endif

#if UART3_ENABLE
static SqQueue uart3_tx;
static SqQueue uart3_rx;
#if (UART3_TX_PIN != NO_PIN)
static uint8_t uart3_tx_fifo[64];
#endif
#if (UART3_RX_PIN != NO_PIN)
static uint8_t uart3_rx_fifo[64];
#endif

#define UART3_SWAP						  0			/**
 * @brief  Documentation
 */

/**
 * @brief  UART3_Init
 * @param  None
 * @retval None
 */	
void UART3_Init(uint32_t BaudRate)
{
	/* Set UART feature */
	LL_UART_InitTypeDef UART_InitStruct = {0};
	/* Enable UART1 peripheral clock */
    LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_UART3);
	/* Set baud rate */
	UART_InitStruct.BaudRate = BaudRate;
	/* set word length to 8 bits: Start bit, 8 data bits, n stop bits */
	UART_InitStruct.DataWidth = LL_UART_DATAWIDTH_8B;
	/* 1 stop bit */
	UART_InitStruct.StopBits = LL_UART_STOPBITS_1;
	/* Parity control disabled  */
	UART_InitStruct.Parity = LL_UART_PARITY_NONE;
	/* MSB first disable */
	UART_InitStruct.BitOrder = LL_UART_BITORDER_LSBFIRST;
	/* Initialize UART */
	LL_UART_Init(UART3, &UART_InitStruct);
	/* Sends an amount of data in non blocking mode. */
	UART3->CR1 |= (UART3_SWAP << 8);
    /**
 * @brief  Documentation
 */
	#if (UART3_TX_PIN != NO_PIN)
	GPIO_Init(UART3_TX_PIN,ALTERNATE | PUSHPULL | GPIO_UART3);
    uart3_tx.base = uart3_tx_fifo;
    uart3_tx.front = uart3_tx.rear = 0;
    uart3_tx.sq_size = sizeof(uart3_tx_fifo);
	#endif
	#if (UART3_RX_PIN != NO_PIN)
	GPIO_Init(UART3_RX_PIN,ALTERNATE | PULL_UP | GPIO_UART3);
	uart3_rx.base = uart3_rx_fifo;
    uart3_rx.front = uart3_rx.rear = 0;
    uart3_rx.sq_size = sizeof(uart3_rx_fifo);
    UART3->CR2 |= UART_CR2_RXNEIE | UART_CR2_LSIE | UART_CR2_BUSYERRIE;
	#endif
	#if UART3_IRQ_ENABLE
	/* Enable UART interrupt */
	NVIC_SetPriority(UART3_IRQn,UART3_IRQ_PRIORITY);
	NVIC_EnableIRQ(UART3_IRQn);
	#endif
}
/**
 * @brief  UART3_IRQHandler
 * @param  None
 * @retval None
 */	
void UART3_IRQHandler(void)
{
	__disable_irq();
	UART_IRQHandler(UART3,&uart3_rx,&uart3_tx);
	__enable_irq();
}
#if (UART3_RX_PIN != NO_PIN)
/**
 * @brief  UART3_QueueRead
 * @param  None
 * @retval None
 */	
uint8_t UART3_QueueRead(uint8_t *data)
{
	#if UART3_IRQ_ENABLE
	return UART_QueueRead(&uart3_rx,data);
	#else
    if (UART3->SR & UART_SR_RXNE)
    {
        *data = UART3->DR;
		return 1;
	}
	return 0;
	#endif
}
#endif
#if (UART3_TX_PIN != NO_PIN)
/**
 * @brief  UART3_QueueSend
 * @param  None
 * @retval None
 */	
uint8_t UART3_QueueSend(uint8_t data)
{
	#if UART3_IRQ_ENABLE
	return UART_QueueSend(UART3,&uart3_tx,data);
	#else
	return UART_QueueSend(UART3,NULL,data);
	#endif
}
#endif
#endif

#if DEBUG_ENABLE
#if (DEBUG_MODE == 1)
int fputc(int ch, FILE *f)
{
    /* Send a byte to UART */
    UART_QueueSend(printf_UARTx,NULL,(uint8_t)ch);
    return (ch);
}
#endif
#endif

#endif

