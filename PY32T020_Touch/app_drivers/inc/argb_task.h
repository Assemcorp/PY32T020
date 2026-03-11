#ifndef _ARGB_TASK_H_
#define _ARGB_TASK_H_

#include "app_config.h"
#if APP_SPI_LED_ENABLE

/**
 * @brief RGB color data structure (one LED)
 */
typedef struct LedSetData
{
    unsigned char  red;     // Red channel value (0-255)
    unsigned char  green;   // Green channel value (0-255)
    unsigned char  blue;    // Blue channel value (0-255)
} LedSetData;

#pragma anon_unions

/**
 * @brief Full display data structure for a single ARGB LED
 */
typedef struct LedDisplayData
{
    LedSetData  color;              // Base RGB color of the LED
    union
    {
        unsigned char flag;
        struct
        {
            unsigned char  dir          : 2;    // Animation direction (0=none, 1=up, 2=down, 3=both)
            unsigned char  colorCount   : 5;    // Current color step counter for animation
            unsigned char  reserved     : 1;    // Reserved bit
        } flag_b;
    };                                          // Display direction / animation flags
    uint8_t alpha;  // Transparency / brightness blending factor (0=off, 255=full)
    uint8_t hold;   // Hold time for current animation frame (timer ticks)
    uint8_t dim;    // Global dimming level (0=off, 255=full brightness)
} ARGBDisplay;

/**
 * @brief  Initialize the ARGB LED module
 * @param  None
 * @retval None
 */
void argb_init(void);

/**
 * @brief  Increment the global color index (cycle forward through color palette)
 * @param  None
 * @retval None
 */
void argb_color_inc(void);

/**
 * @brief  Decrement the global color index (cycle backward through color palette)
 * @param  None
 * @retval None
 */
void argb_color_dec(void);

/**
 * @brief  ARGB animation service routine, call periodically from timer or main loop
 * @param  whlelhold  : Hold ticks for wheel position LEDs
 * @param  sliderhold : Hold ticks for slider position LEDs
 * @retval None
 */
void argb_serive(uint8_t whlelhold, uint8_t sliderhold);

/**
 * @brief  Configure display parameters for a specific LED
 * @param  offset : LED index in the chain (0 to SPI_LED_CNT-1)
 * @param  alpha  : Alpha / brightness blend value (0-255)
 * @param  dim    : Dimming level (0=off, 255=max)
 * @param  dir    : Animation direction
 * @param  hold   : Frame hold duration (ticks)
 * @retval None
 */
void argb_config(uint8_t offset, uint8_t alpha, uint8_t dim, uint8_t dir, uint8_t hold);

extern uint16_t argb_time;          // Global animation timer counter
extern ARGBDisplay argb[SPI_LED_CNT]; // Display data array, one entry per LED

#endif  /* APP_SPI_LED_ENABLE */
#endif  /* _ARGB_TASK_H_ */
