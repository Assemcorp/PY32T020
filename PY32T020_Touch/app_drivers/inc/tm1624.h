#ifndef _TM1624_H_
#define _TM1624_H_

#include "app_config.h"

#if APP_TM1624_ENABLE
#define TM1624_ON		0X08
#define TM1624_OFF		0X00

/**
 * @brief  Initialize TM1624 LED driver
 * @param  None
 * @retval None
 */
void TM1624_Init(void);

/**
 * @brief  Update TM1624 display data
 * @param  display : Pointer to the display data buffer
 * @param  num     : Number of bytes to display
 * @param  Config  : Command instruction used for brightness adjustment and display on/off control
 * @retval None
 */
void TM1624_Display_Update(uint8_t *display, uint8_t num, uint8_t Config);

/**
 * @brief  Read key scan data from TM1624
 * @param  data : Pointer to the buffer to store received key data
 * @retval Key read status
 */
uint8_t TM1624_Read_Key(uint8_t *data);

#endif /* APP_TM1624_ENABLE */

#endif /* _TM1624_H_ */
