#ifndef _APP_IR_RECEIVED_H_
#define _APP_IR_RECEIVED_H_
#include "app_config.h"

#if APP_IR_RECEIVED_ENABLE

/**
 * @brief Decoded IR frame data
 */
typedef struct
{
    uint8_t ir_address;     // NEC address byte received
    uint8_t ir_command;     // NEC command byte received
    uint8_t ir_count;       // Repeat frame counter (increments while key is held)
} Ir_TypeDef;

/**
 * @brief NEC IR pulse-width timing thresholds (in timer ticks, based on D_IR_sample us/tick)
 */
typedef enum
{
    /* Leader (sync) pulse high duration: ~4.5ms */
    SYNC_MIN_TIME   = 4000 / D_IR_sample,
    SYNC_MAX_TIME   = 5000 / D_IR_sample,

    /* Data bit '1' high duration: ~1.69ms */
    DATA1_MIN_TIME  = 1495 / D_IR_sample,
    DATA1_MAX_TIME  = 1895 / D_IR_sample,

    /* Data bit '0' high duration: ~0.56ms */
    DATA0_MIN_TIME  = 365 / D_IR_sample,
    DATA0_MAX_TIME  = 765 / D_IR_sample,

    /* Repeat (long-press) frame high duration: ~2.25ms */
    LONG_MIN_TIME   = 2000 / D_IR_sample,
    LONG_MAX_TIME   = 3000 / D_IR_sample,

    /* Key-release timeout: 200ms with no signal */
    RELEASE_TIME    = 200000 / D_IR_sample,
} TIMEEnum;

/**
 * @brief  Initialize the IR receiver decoder
 * @param  None
 * @retval None
 */
void IR_Received_Init(void);

/**
 * @brief  IR signal level scanner - call from timer ISR at D_IR_sample us interval
 * @param  None
 * @retval None
 */
void IR_Received_Scan(void);

/**
 * @brief  Check for a decoded IR frame and fill the result structure
 * @param  remote : Pointer to Ir_TypeDef struct to receive address and command
 * @retval 0 : No valid IR signal received
 *         1 : Valid IR frame decoded successfully
 */
uint8_t IR_Press(Ir_TypeDef *remote);

#endif  /* APP_IR_RECEIVED_ENABLE */
#endif  /* _APP_IR_RECEIVED_H_ */
