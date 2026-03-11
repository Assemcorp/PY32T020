#ifndef _SPI_LED_DRIVERS_H_
#define _SPI_LED_DRIVERS_H_
#include "app_config.h"
#if APP_SPI_LED_ENABLE

/**
 * @brief  Initialize SPI for driving WS2812 type RGB LEDs
 * @param  None
 * @retval None
 */
void SPI_LED_Init(void);

/**
 * @brief  Load RGB data into the transmission buffer
 * @param  offset : LED index in the chain
 * @param  red    : PWM value for red (0-255)
 * @param  green  : PWM value for green (0-255)
 * @param  blue   : PWM value for blue (0-255)
 * @retval None
 */
void SPI_LED_RgbLoad(uint8_t offset, uint8_t red, uint8_t green, uint8_t blue);

/**
 * @brief  Transmit the buffered RGB data via SPI
 * @param  None
 * @retval None
 */
void SPI_LED_Transmit(void);

#endif /* APP_SPI_LED_ENABLE */
#endif /* _SPI_LED_DRIVERS_H_ */
