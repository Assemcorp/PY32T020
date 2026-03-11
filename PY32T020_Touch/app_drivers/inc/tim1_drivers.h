#ifndef _TIM1_DRIVERS_H_
#define _TIM1_DRIVERS_H_

#include "app_config.h"

#if APP_TIM1_ENABLE

/**
 * @brief  Initialize Timer 1
 * @param  None
 * @retval None
 */
void TIM1_Init(void);

/**
 * @brief  Timer 1 interrupt callback function
 * @param  None
 * @retval None
 */
void TIM1_PeriodElapsedCallback(void);

#elif APP_TIM1_PWM_ENABLE

/**
 * @brief  Initialize Timer 1 for PWM output
 * @param  None
 * @retval None
 */
void TIM1_PWM_Init(void);

/**
 * @brief  Set Timer 1 PWM duty cycle
 * @param  CHx     : PWM channel (LL_TIM_CHANNEL_CH1 ~ LL_TIM_CHANNEL_CH4)
 * @param  percent : Output duty cycle percentage
 * @retval None
 */
void TIM1_PWM_Pulse(uint32_t CHx, uint16_t percent);

#endif /* APP_TIM1_ENABLE / APP_TIM1_PWM_ENABLE */

#endif /* _TIM1_DRIVERS_H_ */
