#ifndef _APP_DRIVERS_H_
#define _APP_DRIVERS_H_
#include "app_config.h"

extern volatile uint32_t EXTI_Flag;    // External interrupt event flag (set in EXTI ISR)

/**
 * @brief  Initialize all peripheral drivers (GPIO, UART, ADC, TIM, etc.)
 * @param  None
 * @retval None
 */
void app_drivers_init(void);

/**
 * @brief  Main driver polling loop - call inside while(1) to process module tasks
 * @param  None
 * @retval None
 */
void app_drivers_loop(void);

/**
 * @brief  Driver 1ms timer callback - call from SysTick ISR every 1ms
 * @param  None
 * @retval None
 */
void app_drivers_timer(void);

/**
 * @brief  Approximate NOP-based delay (not cycle-accurate)
 * @param  nus : Delay time in microseconds
 * @retval None
 */
void nop_delay_xus(uint16_t nus);

/**
 * @brief  Precise microsecond delay using SysTick timer
 * @param  nus : Delay time in microseconds
 * @retval None
 */
void delay_us(uint16_t nus);

/**
 * @brief  Millisecond delay using SysTick timer
 * @param  nms : Delay time in milliseconds
 * @retval None
 */
void delay_ms(uint16_t nms);

/**
 * @brief  UART receive timeout handler - call from SysTick ISR every 1ms
 *         Signals end-of-frame when bus has been idle for more than 5ms
 * @param  None
 * @retval None
 */
void UART_TimeOut(void);

/**
 * @brief  UART task handler - polls the receive queue and echoes data back
 *         after 5ms of receive idle time
 * @param  None
 * @retval None
 */
void UART_Loop(void);

/**
 * @brief  ADC state machine handler - when adc_state == 2 the full sequence is
 *         complete and ADCxConvertedData[x] holds the result for channel x
 * @param  None
 * @retval None
 */
void ADC_Loop(void);

extern uint16_t adc_tick;     // ADC conversion tick counter

/**
 * @brief  Display a decimal number on the 7-segment display
 * @param  num : Value to display (decimal)
 * @retval None
 */
void SMG_Show(uint16_t num);

/**
 * @brief  Update touch key LED indicators based on active key bits
 * @param  led_bit : Bitmask of keys to light up
 *                   (bit0 = TK0 LED, bit1 = TK1 LED, ...)
 * @retval None
 */
void LED_Show(uint16_t led_bit);

#endif  /* _APP_DRIVERS_H_ */
