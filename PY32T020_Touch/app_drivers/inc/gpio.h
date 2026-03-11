#ifndef _GPIO_H
#define _GPIO_H

#include "py32t020_ll_gpio.h"
#include "py32t020_ll_exti.h"

/**
 * @brief Logical GPIO pin numbers for PY32T020
 *        PA0-PA15 = 0-15, PB0-PB3 = 16-19, PF0-PF5 = 20-25, PIN_NONE = 26
 */
enum
{
    PA0 = 0,
    PA1,
    PA2,
    PA3,
    PA4,
    PA5,
    PA6,
    PA7,
    PA8,
    PA9,
    PA10,
    PA11,
    PA12,
    PA13,
    PA14,
    PA15,
    PB0,    // 16
    PB1,
    PB2,
    PB3,
    PF0,    // 20
    PF1,
    PF2,
    PF3,
    PF4,
    PF5,
    PIN_NONE
};

/**
 * @brief GPIO mode / pull / output type / alternate function / EXTI trigger flags.
 *        Combine with bitwise OR when calling GPIO_Init().
 *
 * Mode flags (choose one):
 *   INPUT     - Digital input
 *   OUTPUT    - Digital output
 *   ALTERNATE - Alternate (peripheral) function
 *   ANALOG    - Analog / ADC input
 *
 * Pull flags (choose one):
 *   PULL_NO       - No pull resistor
 *   PULL_UP       - Pull-up resistor
 *   PULL_DOWN     - Pull-down resistor
 *   PULL_UP_DOWN  - Both pull-up and pull-down
 *
 * Output type flags (choose one):
 *   OPENDRAIN - Open-drain output
 *   PUSHPULL  - Push-pull output
 *
 * Alternate function flags (valid when ALTERNATE is selected):
 *   GPIO_SPI1, GPIO_I2C_AF3/AF4, GPIO_UART1/2/3,
 *   GPIO_TIM1_AF2/AF5, GPIO_TIM14_AF5/AF6,
 *   GPIO_COMP1/2, GPIO_MCO
 *   (Check the datasheet alternate function mapping for each pin)
 *
 * EXTI trigger flags (valid with INPUT mode only):
 *   EXTI_TRIGGER_RISING         - Rising edge interrupt
 *   EXTI_TRIGGER_FALLING        - Falling edge interrupt
 *   EXTI_TRIGGER_RISING_FALLING - Both edges interrupt
 */
enum
{
    INPUT                       = 0X01,     // Digital input mode
    OUTPUT                      = 0X02,     // Digital output mode
    ALTERNATE                   = 0X03,     // Alternate (peripheral) function mode
    ANALOG                      = 0X04,     // Analog / ADC mode

    PULL_NO                     = 0X10,     // No pull resistor
    PULL_UP                     = 0X20,     // Internal pull-up resistor
    PULL_DOWN                   = 0X30,     // Internal pull-down resistor
    PULL_UP_DOWN                = 0X40,     // Both pull-up and pull-down

    OPENDRAIN                   = 0X100,    // Open-drain output type
    PUSHPULL                    = 0X200,    // Push-pull output type

    GPIO_SPI1                   = 0X0000,   // Alternate function: SPI1
    GPIO_I2C_AF3                = 0X1000,   // Alternate function: I2C (AF3)
    GPIO_I2C_AF4                = 0X2000,   // Alternate function: I2C (AF4)
    GPIO_UART1                  = 0X3000,   // Alternate function: UART1
    GPIO_UART2                  = 0X4000,   // Alternate function: UART2
    GPIO_UART3                  = 0X5000,   // Alternate function: UART3
    GPIO_TIM1_AF2               = 0X6000,   // Alternate function: TIM1 (AF2)
    GPIO_TIM1_AF5               = 0X7000,   // Alternate function: TIM1 (AF5)
    GPIO_TIM14_AF5              = 0X8000,   // Alternate function: TIM14 (AF5)
    GPIO_TIM14_AF6              = 0X9000,   // Alternate function: TIM14 (AF6)
    GPIO_COMP1                  = 0XA000,   // Alternate function: Comparator 1
    GPIO_COMP2                  = 0XB000,   // Alternate function: Comparator 2
    GPIO_MCO                    = 0XC000,   // Alternate function: MCO clock output

    EXTI_TRIGGER_RISING         = 0X10000,  // EXTI: rising edge trigger (input mode only)
    EXTI_TRIGGER_FALLING        = 0X20000,  // EXTI: falling edge trigger (input mode only)
    EXTI_TRIGGER_RISING_FALLING = 0X30000,  // EXTI: both edges trigger (input mode only)
};

#define NO_PIN                   26          // Sentinel value meaning "pin not used"
#define GPIO_PORT(__PIN__)       T020_IO[__PIN__].PORT
#define GPIO_PIN(__PIN__)        T020_IO[__PIN__].PIN

typedef struct {
    uint16_t bit0  : 1;
    uint16_t bit1  : 1;
    uint16_t bit2  : 1;
    uint16_t bit3  : 1;
    uint16_t bit4  : 1;
    uint16_t bit5  : 1;
    uint16_t bit6  : 1;
    uint16_t bit7  : 1;
    uint16_t bit8  : 1;
    uint16_t bit9  : 1;
    uint16_t bit10 : 1;
    uint16_t bit11 : 1;
    uint16_t bit12 : 1;
    uint16_t bit13 : 1;
    uint16_t bit14 : 1;
    uint16_t bit15 : 1;
} Bit16_TypeDef;

/* Bit-band output macros for direct pin write */
#define PAOUT(n) ((Bit16_TypeDef *)(&(GPIOA->ODR)))->bit##n
#define PBOUT(n) ((Bit16_TypeDef *)(&(GPIOB->ODR)))->bit##n
#define PFOUT(n) ((Bit16_TypeDef *)(&(GPIOF->ODR)))->bit##n

/* Input read macros */
#define PAIN(n)  (GPIOA->IDR & (1 << n))
#define PBIN(n)  (GPIOB->IDR & (1 << n))
#define PFIN(n)  (GPIOF->IDR & (1 << n))

/**
 * @brief  Initialize a GPIO pin with the specified mode, pull, output type and alternate function.
 *
 * Usage examples:
 *   Analog input        : GPIO_Init(PA0, ANALOG)
 *   Input with pull-up  : GPIO_Init(PA0, INPUT | PULL_UP)
 *   Input + falling EXTI: GPIO_Init(PA0, INPUT | PULL_UP | EXTI_TRIGGER_FALLING)
 *   Push-pull output    : GPIO_Init(PA0, OUTPUT | PUSHPULL)
 *   Open-drain output   : GPIO_Init(PA0, OUTPUT | OPENDRAIN)
 *   TIM1 CH3 alternate  : GPIO_Init(PA0, ALTERNATE | GPIO_TIM1_AF2)
 *                         (Select AF2 or AF5 based on datasheet pin mapping)
 *   UART2 alternate     : GPIO_Init(PA0, ALTERNATE | GPIO_UART2)
 *
 * @param  gpio : Pin number (PA0~PA15, PB0~PB3, PF0~PF5)
 * @param  Init : Combined mode/pull/type/AF/EXTI flags
 * @retval None
 */
void GPIO_Init(uint8_t gpio, uint32_t Init);

/**
 * @brief  Set a GPIO output pin high
 * @param  gpio : Pin number (PA0~PA15, PB0~PB3, PF0~PF5)
 * @retval None
 */
void GPIO_SetBit(uint8_t gpio);

/**
 * @brief  Set a GPIO output pin low
 * @param  gpio : Pin number (PA0~PA15, PB0~PB3, PF0~PF5)
 * @retval None
 */
void GPIO_ClearBit(uint8_t gpio);

/**
 * @brief  Toggle a GPIO output pin
 * @param  gpio : Pin number (PA0~PA15, PB0~PB3, PF0~PF5)
 * @retval None
 */
void GPIO_ToggleBit(uint8_t gpio);

/**
 * @brief  Read the current state of a GPIO pin
 * @param  gpio : Pin number (PA0~PA15, PB0~PB3, PF0~PF5)
 * @retval 0 = low, non-zero = high
 */
uint8_t GPIO_ReadBit(uint8_t gpio);

/**
 * @brief  EXTI line 0-15 interrupt callback - called from IRQ handler with pending flags
 * @param  PR : EXTI pending register value (bitmask of triggered lines)
 * @retval None
 */
void EXTI0_15_IRQHandlerCallback(uint32_t PR);

#endif  /* _GPIO_H */
