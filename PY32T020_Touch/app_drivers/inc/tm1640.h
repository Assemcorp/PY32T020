#ifndef _TM1640_H_
#define _TM1640_H_

#include "app_config.h"

#if APP_TM1640_ENABLE
#define TM1640_ON		0X08
#define TM1640_OFF		0X00

/**
 * @brief  Initialize TM1640 LED driver
 * @param  None
 * @retval None
 */
void TM1640_Init(void);

/**
 * @brief  Update TM1640 display data
 * @param  display : Pointer to the display data buffer
 * @param  num     : Number of bytes to display
 * @param  Config  : Command instruction used for brightness adjustment and display on/off control
 * @retval None
 */
void TM1640_Display_Update(uint8_t *display, uint8_t num, uint8_t Config);

#endif /* APP_TM1640_ENABLE */

#endif /* _TM1640_H_ */
