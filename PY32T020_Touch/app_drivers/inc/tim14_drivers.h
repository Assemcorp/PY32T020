#ifndef _TIM14_DRIVERS_H_
#define _TIM14_DRIVERS_H_
#include "app_config.h"

#if APP_TIM14_ENABLE

/**
 * @brief  Initialize Timer 14
 * @param  None
 * @retval None
 */
void TIM14_Init(void);

/**
 * @brief  Timer 14 interrupt callback function
 * @param  None
 * @retval None
 */
void TIM14_PeriodElapsedCallback(void);

#elif APP_TIM14_PWM_ENABLE

/**
 * @brief  Initialize Timer 14 for PWM output
 * @param  None
 * @retval None
 */
void TIM14_PWM_Init(void);

/**
 * @brief  Set Timer 14 PWM duty cycle
 * @param  CHx     : PWM channel (usually LL_TIM_CHANNEL_CH1 for TIM14)
 * @param  percent : Output duty cycle percentage
 * @retval None
 */
void TIM14_PWM_Pulse(uint32_t CHx, uint16_t percent);

#endif /* APP_TIM14_ENABLE / APP_TIM14_PWM_ENABLE */

#endif /* _TIM14_DRIVERS_H_ */
