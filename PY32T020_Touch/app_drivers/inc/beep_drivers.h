#ifndef _BEEP_DRIVERS_H_
#define _BEEP_DRIVERS_H_
#include "app_config.h"

#if APP_BEEP_ENABLE

/**
 * @brief  Initialize the buzzer GPIO pin
 * @param  None
 * @retval None
 */
void BEEP_Init(void);

/**
 * @brief  Turn on the buzzer for a specified duration
 * @param  timeout : On duration in milliseconds
 * @retval None
 */
void BEEP_On(uint8_t timeout);

/**
 * @brief  Buzzer timeout handler - call from SysTick ISR every 1ms to auto-turn-off
 * @param  None
 * @retval None
 */
void BEEP_Timeout(void);

#endif  /* APP_BEEP_ENABLE */
#endif  /* _BEEP_DRIVERS_H_ */
