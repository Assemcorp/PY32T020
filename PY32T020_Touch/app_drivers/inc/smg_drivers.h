#ifndef _SMG_DRIVERS_H_
#define _SMG_DRIVERS_H_

#include "app_config.h"
#if APP_SMG_ENABLE

/**
 * @brief  Initialize 7-segment display GPIO pins (COM and SEG lines)
 * @param  None
 * @retval None
 */
void SMG_Init(void);

/**
 * @brief  Put 7-segment display into sleep state (set GPIO to low-power configuration)
 * @param  None
 * @retval None
 */
void SMG_Sleep(void);

/**
 * @brief  Wake 7-segment display from sleep and resume scanning
 * @param  None
 * @retval None
 */
void SMG_Wake(void);

/**
 * @brief  7-segment display multiplexed scan routine - call from SysTick ISR every 1ms
 * @param  None
 * @retval None
 */
void SMG_Scan(void);

/**
 * @brief  Set the default power-on display content
 * @param  None
 * @retval None
 */
void SMG_Default(void);

#endif  /* APP_SMG_ENABLE */
#endif  /* _SMG_DRIVERS_H_ */
