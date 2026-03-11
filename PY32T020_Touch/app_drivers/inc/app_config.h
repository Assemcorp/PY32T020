#ifndef _APP_CONFIG_H_
#define _APP_CONFIG_H_

#include <stdio.h>
#include "py32t020_ll_rcc.h"
#include "py32t020_ll_bus.h"
#include "py32t020_ll_system.h"
#include "py32t020_ll_cortex.h"
#include "py32t020_ll_utils.h"
#include "py32t020_ll_pwr.h"
#include "py32t020_ll_gpio.h"
#include "py32t020_ll_uart.h"
#include "py32t020_ll_adc.h"
#include "py32t020_ll_tim.h"
#include "py32t020_ll_spi.h"
#include "py32t020_ll_exti.h"
#include "py32t020_ll_iwdg.h"
#include "py32t020_ll_rtc.h"
#if defined(USE_FULL_ASSERT)
#include "py32_assert.h"
#endif /* USE_FULL_ASSERT */


// <<< Use Configuration Wizard in Context Menu >>>

// <o> HSI Clock Frequency
// <24000000UL=> 24MHz
// <48000000UL=> 48MHz
#define HSI_FREQUENCE        24000000UL      // HSI oscillator frequency (Hz)

#define fac_us              (HSI_FREQUENCE / 1000000)   // Microsecond delay factor

//  <o> Touch Key Module
//  <0=> DISABLE
//  <1=> ENABLE
#define APP_TK_ENABLE            1           // Enable (1) / Disable (0) touch key module

//  <e> SYSTICK
#define APP_SYSTICK_ENABLE            1      // Enable (1) / Disable (0) SysTick timer

#if APP_SYSTICK_ENABLE
#define SYSTICK_TIMING_TIME            1000  // SysTick interrupt period (us)
#define SYSTICK_IRQ_PRIORITY           0     // SysTick interrupt priority (0=highest)
#define SYSTICK_DEBUG                  0     // Enable (1) / Disable (0) SysTick debug GPIO toggle
#define SYSTICK_DEBUG_GPIO             20    // GPIO pin number used for SysTick debug toggle
#endif
// </e>

// <e> Debug / Printf
#define DEBUG_ENABLE            0            // Enable (1) / Disable (0) debug print output
#if DEBUG_ENABLE
#define DEBUG_MODE              0            // 0: TK log output, 1: UART printf output
#define PRINTF_UART             1            // UART port used for printf (1=UART1, 2=UART2, 3=UART3)
#endif
// </e>

// <e> UART
#define APP_UART_ENABLE         0            // Enable (1) / Disable (0) UART module
#if APP_UART_ENABLE
#define UART1_ENABLE            1            // Enable (1) / Disable (0) UART1
#if UART1_ENABLE
#define UART1_TX_PIN                6        // UART1 TX GPIO pin number
#define UART1_RX_PIN                7        // UART1 RX GPIO pin number
#define UART1_BAUDRATE              115200   // UART1 baud rate (bps)
#define UART1_IRQ_ENABLE            1        // Enable (1) / Disable (0) UART1 receive interrupt
#define UART1_IRQ_PRIORITY          3        // UART1 interrupt priority
#endif
#define UART2_ENABLE                1        // Enable (1) / Disable (0) UART2
#if UART2_ENABLE
#define UART2_TX_PIN                0        // UART2 TX GPIO pin number
#define UART2_RX_PIN                1        // UART2 RX GPIO pin number
#define UART2_BAUDRATE              115200   // UART2 baud rate (bps)
#define UART2_IRQ_ENABLE            1        // Enable (1) / Disable (0) UART2 receive interrupt
#define UART2_IRQ_PRIORITY          3        // UART2 interrupt priority
#endif
#define UART3_ENABLE                1        // Enable (1) / Disable (0) UART3
#if UART3_ENABLE
#define UART3_TX_PIN                2        // UART3 TX GPIO pin number
#define UART3_RX_PIN                3        // UART3 RX GPIO pin number
#define UART3_BAUDRATE              115200   // UART3 baud rate (bps)
#define UART3_IRQ_ENABLE            1        // Enable (1) / Disable (0) UART3 receive interrupt
#define UART3_IRQ_PRIORITY          3        // UART3 interrupt priority
#endif
#endif
// </e>

// <e> Flash Option Bytes
#define OB_USER_OPTION              0        // Enable (1) / Disable (0) option byte configuration
#if OB_USER_OPTION
#define OPTION_NRST_MODE            0        // 1: NRST pin active, 0: NRST pin as GPIO
#if OPTION_NRST_MODE
#define OB_GPIO_PIN_MODE        FLASH_OPTR_NRST_MODE
#else
#define OB_GPIO_PIN_MODE        0x00000000U
#endif
#define OPTION_BOR_EN               0        // Enable (1) / Disable (0) Brown-Out Reset
#if OPTION_BOR_EN
#define OB_BOR_EN                   FLASH_OPTR_BOR_EN
#else
#define OB_BOR_EN                   0x00000000U
#endif
#define OPTION_BOR_LEV                  4    // BOR level (1-7, higher = higher voltage threshold)
#if (OPTION_BOR_LEV == 1)
#define OB_BOR_LEVEL                    ((uint32_t)(FLASH_OPTR_BOR_LEV_0))
#elif (OPTION_BOR_LEV == 2)
#define OB_BOR_LEVEL                    ((uint32_t)(FLASH_OPTR_BOR_LEV_1))
#elif (OPTION_BOR_LEV == 3)
#define OB_BOR_LEVEL                    ((uint32_t)(FLASH_OPTR_BOR_LEV_0 | FLASH_OPTR_BOR_LEV_1))
#elif (OPTION_BOR_LEV == 4)
#define OB_BOR_LEVEL                    ((uint32_t)(FLASH_OPTR_BOR_LEV_2))
#elif (OPTION_BOR_LEV == 5)
#define OB_BOR_LEVEL                    ((uint32_t)(FLASH_OPTR_BOR_LEV_0 | FLASH_OPTR_BOR_LEV_2))
#elif (OPTION_BOR_LEV == 6)
#define OB_BOR_LEVEL                    ((uint32_t)(FLASH_OPTR_BOR_LEV_1 | FLASH_OPTR_BOR_LEV_2))
#elif (OPTION_BOR_LEV == 7)
#define OB_BOR_LEVEL                    ((uint32_t)(FLASH_OPTR_BOR_LEV_0 | FLASH_OPTR_BOR_LEV_1 | FLASH_OPTR_BOR_LEV_2))
#endif
#define OPTION_IWDG_SW_EN              1     // 1: IWDG in software mode, 0: hardware mode
#if OPTION_IWDG_SW_EN
#define OB_IWDG_MODE                   FLASH_OPTR_IWDG_SW
#else
#define OB_IWDG_MODE                   0x00000000U
#endif
#define OPTION_IWDG_STOP               0     // 1: IWDG continues in STOP mode, 0: IWDG freezes
#if OPTION_IWDG_STOP
#define OB_IWDG_STOP                   ((uint32_t)FLASH_OPTR_IWDG_STOP)
#else
#define OB_IWDG_STOP                   0x00000000U
#endif
#endif

// <e> Flash User OTP
#define APP_USER_OTP_ENABLE            0     // Enable (1) / Disable (0) user OTP flash area
#if APP_USER_OTP_ENABLE
#define LVD_WRITE_USER_DATA            1     // Enable (1) writing user data on low voltage detection
#define low_voltage                    3100  // Low voltage threshold (mV) for OTP write trigger
#endif
// </e>

// <e> IWDG (Independent Watchdog)
#define APP_IWDG_ENABLE            0         // Enable (1) / Disable (0) independent watchdog
#define IDWG_RELOAD_VALUE        1500        // IWDG reload value (determines timeout period)
// </e>

// <e> BEEP (Buzzer)
#define APP_BEEP_ENABLE                 1    // Enable (1) / Disable (0) buzzer output
#if APP_BEEP_ENABLE
#define BEEP_GPIO                       15   // GPIO pin number connected to buzzer
#define BEEP_GPIO_TYPE                  1    // Output type: 1=push-pull, 0=open-drain
#endif
// </e>

// <e> TIM14 (Timer 14 - Periodic Interrupt)
#define APP_TIM14_ENABLE            0        // Enable (1) / Disable (0) TIM14 timer
#if APP_TIM14_ENABLE
#define TIM14_TIMING_TIME           125      // TIM14 interrupt period (us)
#define TIM14_IRQ_ENABLE            1        // Enable (1) / Disable (0) TIM14 interrupt
#define TIM14_IRQ_PRIORITY          0        // TIM14 interrupt priority (0=highest)
#define TIM14_DEBUG                 0        // Enable (1) / Disable (0) TIM14 debug GPIO toggle
#define TIM14_DEBUG_GPIO            19       // GPIO pin number used for TIM14 debug toggle
#endif
// </e>

// <e> TIM14-PWM (Timer 14 - PWM Output)
#define APP_TIM14_PWM_ENABLE        0        // Enable (1) / Disable (0) TIM14 PWM output
#if APP_TIM14_PWM_ENABLE
#define TIM14_PWM_FREQUENCE         25000    // TIM14 PWM frequency (Hz)
#define TIM14_RESOLUTION            100      // PWM duty cycle resolution (steps)
#define TIM14_DUTY_CYCLE            10       // TIM14 CH1 duty cycle (%)
#define TIM14_CH1_PIN               9        // TIM14 CH1 GPIO pin number
#endif
// </e>

// <e> TIM1 (Timer 1 - Periodic Interrupt)
#define APP_TIM1_ENABLE             0        // Enable (1) / Disable (0) TIM1 timer
#if APP_TIM1_ENABLE
#define TIM1_TIMING_TIME            125      // TIM1 interrupt period (us)
#define TIM1_IRQ_ENABLE             1        // Enable (1) / Disable (0) TIM1 interrupt
#define TIM1_IRQ_PRIORITY           0        // TIM1 interrupt priority (0=highest)
#define TIM1_DEBUG                  0        // Enable (1) / Disable (0) TIM1 debug GPIO toggle
#define TIM1_DEBUG_GPIO             20       // GPIO pin number used for TIM1 debug toggle
#endif
// </e>

// <e> TIM1-PWM (Timer 1 - PWM Output)
#define APP_TIM1_PWM_ENABLE         0        // Enable (1) / Disable (0) TIM1 PWM output
#if APP_TIM1_PWM_ENABLE
#define TIM1_PWM_FREQUENCE          4000     // TIM1 PWM frequency (Hz)
#define TIM1_RESOLUTION             100      // PWM duty cycle resolution (steps)
#define TIM1_CH1_ENABLE             1        // Enable (1) / Disable (0) TIM1 CH1
#define TIM1_DUTY1_CYCLE            10       // TIM1 CH1 duty cycle (%)
#define TIM1_CH1_PIN                3        // TIM1 CH1 GPIO pin number
#define TIM1_CH2_ENABLE             1        // Enable (1) / Disable (0) TIM1 CH2
#define TIM1_DUTY2_CYCLE            20       // TIM1 CH2 duty cycle (%)
#define TIM1_CH2_PIN                5        // TIM1 CH2 GPIO pin number
#define TIM1_CH3_ENABLE             1        // Enable (1) / Disable (0) TIM1 CH3
#define TIM1_DUTY3_CYCLE            30       // TIM1 CH3 duty cycle (%)
#define TIM1_CH3_PIN                0        // TIM1 CH3 GPIO pin number
#define TIM1_CH4_ENABLE             1        // Enable (1) / Disable (0) TIM1 CH4
#define TIM1_DUTY4_CYCLE            50       // TIM1 CH4 duty cycle (%)
#define TIM1_CH4_PIN                11       // TIM1 CH4 GPIO pin number
#endif
// </e>

// <e> ADC (Analog-to-Digital Converter)
#define APP_ADC_ENABLE              0        // Enable (1) / Disable (0) ADC module
#if APP_ADC_ENABLE
#define ADC_SPEED                   10       // ADC sampling speed setting
#define ADC_IN0_ENABLE              0        // Enable (1) / Disable (0) ADC channel 0 (PA0)
#define ADC_IN1_ENABLE              0        // Enable (1) / Disable (0) ADC channel 1 (PA1)
#define ADC_IN2_ENABLE              0        // Enable (1) / Disable (0) ADC channel 2 (PA2)
#define ADC_IN3_ENABLE              0        // Enable (1) / Disable (0) ADC channel 3 (PA3)
#define ADC_IN4_ENABLE              0        // Enable (1) / Disable (0) ADC channel 4 (PA4)
#define ADC_IN5_ENABLE              0        // Enable (1) / Disable (0) ADC channel 5 (PA5)
#define ADC_IN6_ENABLE              0        // Enable (1) / Disable (0) ADC channel 6 (PA6)
#define ADC_IN7_ENABLE              0        // Enable (1) / Disable (0) ADC channel 7 (PA7)
#define ADC_IN8_ENABLE              0        // Enable (1) / Disable (0) ADC channel 8 (PB0)
#define ADC_IN9_ENABLE              0        // Enable (1) / Disable (0) ADC channel 9 (PB1)
#define ADC_IN10_ENABLE             1        // Enable (1) / Disable (0) ADC channel 10 (internal temperature sensor)
#define ADC_IN11_ENABLE             1        // Enable (1) / Disable (0) ADC channel 11 (internal VREFINT)
#define ADC_IN12_ENABLE             0        // Enable (1) / Disable (0) ADC channel 12 (1/3 VCCA)
#endif
// </e>

// <e> SPI-LED (WS2812 / RGB LED)
#define APP_SPI_LED_ENABLE          0        // Enable (1) / Disable (0) SPI-driven RGB LED (WS2812)
#if APP_SPI_LED_ENABLE
#define SPI_LED_PIN                 2        // SPI data out GPIO pin number
#define SPI_LED_CNT                 32       // Number of RGB LEDs in the chain
#endif
// </e>

// <e> SMG (7-Segment Display)
#define APP_SMG_ENABLE              1        // Enable (1) / Disable (0) 7-segment display driver
#if APP_SMG_ENABLE
#define COM0_GPIO_PIN               12       // COM0 GPIO pin number
#define COM1_GPIO_PIN               13       // COM1 GPIO pin number
#define COM2_GPIO_PIN               14       // COM2 GPIO pin number
#define COM3_GPIO_PIN               26       // COM3 GPIO pin number (NO_PIN to disable)
#define COM4_GPIO_PIN               26       // COM4 GPIO pin number (NO_PIN to disable)
#define SEG0_GPIO_PIN               5        // SEG0 (segment A) GPIO pin number
#define SEG1_GPIO_PIN               8        // SEG1 (segment B) GPIO pin number
#define SEG2_GPIO_PIN               18       // SEG2 (segment C) GPIO pin number
#define SEG3_GPIO_PIN               1        // SEG3 (segment D) GPIO pin number
#define SEG4_GPIO_PIN               19       // SEG4 (segment E) GPIO pin number
#define SEG5_GPIO_PIN               0        // SEG5 (segment F) GPIO pin number
#define SEG6_GPIO_PIN               7        // SEG6 (segment G) GPIO pin number
#define SEG7_GPIO_PIN               6        // SEG7 (segment DP) GPIO pin number
#endif
// </e>

// <e> TM1624 (LED Driver)
#define APP_TM1624_ENABLE   0                // Enable (1) / Disable (0) TM1624 LED driver
#define TM1624_CLK          2                // TM1624 CLK GPIO pin number
#define TM1624_DIN          3                // TM1624 DIN GPIO pin number
#define TM1624_STB          1                // TM1624 STB (chip select) GPIO pin number
#define TM1624_DISP_COM     3                // Number of COM lines used
#define TM1624_DISP_DIM     7                // Display brightness (0-7, 7=max)
#define TM1624_DISP_TEST    1                // 1: Display test mode on, 0: normal mode
// </e>

// <e> TM1640 (LED Driver)
#define APP_TM1640_ENABLE   0                // Enable (1) / Disable (0) TM1640 LED driver
#define TM1640_CLK          2                // TM1640 CLK GPIO pin number
#define TM1640_DIN          3                // TM1640 DIN GPIO pin number
#define TM1640_DISP_DIM     7                // Display brightness (0-7, 7=max)
#define TM1640_DISP_TEST    1                // 1: Display test mode on, 0: normal mode
// </e>

// <e> IR Receiver
#define APP_IR_RECEIVED_ENABLE      0        // Enable (1) / Disable (0) IR receiver
#define IR_GPIO                     20       // IR receiver input GPIO pin number
#define D_IR_TIM                    1        // Timer used for IR decoding (1=TIM1, 14=TIM14)
// </e>
// <<< end of configuration section >>>


#ifndef NULL
#define NULL 0
#endif

typedef struct 
{
    uint8_t bit0 : 1;
    uint8_t bit1 : 1;
    uint8_t bit2 : 1;
    uint8_t bit3 : 1;
    uint8_t bit4 : 1;
    uint8_t bit5 : 1;
    uint8_t bit6 : 1;
    uint8_t bit7 : 1;
} Bits8_TypeDef;

#if DEBUG_ENABLE
    #if (DEBUG_MODE == 0)
        #if (APP_TK_ENABLE == 0)
            #error "error! TK module must be enabled for debug print"
        #else
        extern char log_string[64];
        #define log_printf(...)         do{snprintf(log_string,64,__VA_ARGS__);log_putstr(log_string);}while(0)
        #endif
    #elif (DEBUG_MODE == 1)
        #if (APP_UART_ENABLE == 0)
            #error "error! UART module must be enabled for debug print"
        #else
            #if (PRINTF_UART == 1)    
                #if (UART1_ENABLE == 0)
                #error "error! UART1 must be enabled for debug print"
                #else
                #define printf_UARTx            UART1
                #endif
            #elif (PRINTF_UART == 2)
                #if (UART2_ENABLE == 0)
                #error "error! UART2 must be enabled for debug print"
                #else
                #define printf_UARTx            UART2
                #endif
            #else
                #if (UART3_ENABLE == 0)
                #error "error! UART3 must be enabled for debug print"
                #else
                #define printf_UARTx            UART3
                #endif
            #endif
        #endif
        #define log_printf(...)         printf(__VA_ARGS__)        
    #endif
#else
    #define log_printf(...) 
#endif

#include "gpio.h"
#include "py32t020_flash.h"

#if    APP_TK_ENABLE
#include "tk_cfg.h"
#endif

#if APP_BEEP_ENABLE
#include "beep_drivers.h"
#endif

#if (APP_TIM14_ENABLE || APP_TIM14_PWM_ENABLE)
#include "tim14_drivers.h"
#endif

#if (APP_TIM14_ENABLE && APP_TIM14_PWM_ENABLE)
    #error "error! Cannot enable both TIM14 and TIM14_PWM"
#endif

#if (APP_TIM1_ENABLE || APP_TIM1_PWM_ENABLE)
#include "tim1_drivers.h"
#endif

#if (APP_TIM1_ENABLE && APP_TIM1_PWM_ENABLE)
    #error "error! Cannot enable both TIM1 and TIM1_PWM"
#endif

#if APP_ADC_ENABLE
#include "adc_drivers.h"
#define ADC_ENABLE_CHS           ((ADC_IN0_ENABLE << 0) | (ADC_IN1_ENABLE << 1) | (ADC_IN2_ENABLE << 2) |   \
                                (ADC_IN3_ENABLE << 3) | (ADC_IN4_ENABLE << 4) | (ADC_IN5_ENABLE << 5) |   \
                                (ADC_IN6_ENABLE << 6) | (ADC_IN7_ENABLE << 7) | (ADC_IN8_ENABLE << 8) |   \
                                (ADC_IN9_ENABLE << 9) | (ADC_IN10_ENABLE << 10) | (ADC_IN11_ENABLE << 11) | \
                                (ADC_IN12_ENABLE << 12))    
#endif

#if APP_UART_ENABLE
#include "uart_drivers.h"
#endif

#if APP_SPI_LED_ENABLE
#include "spi-led_drivers.h"
#include "argb_task.h"
#endif

#if APP_USER_OTP_ENABLE
#include "user-otp_drivers.h"
    #if LVD_WRITE_USER_DATA
        #if (APP_ADC_ENABLE == 0)
        #error "error! ADC module must be enabled for LVD_WRITE_USER_DATA"
        #else
        extern uint8_t power_count;
        #endif
    #endif
#endif

#if APP_SMG_ENABLE
#include "smg_drivers.h"
#if (SEG0_GPIO_PIN == NO_PIN)
    #error "error! At least 1 SEG must be enabled"
    #define SEG_COUNT      0
#elif (SEG1_GPIO_PIN == NO_PIN)    
    #define SEG_COUNT      1
#elif (SEG2_GPIO_PIN == NO_PIN)    
    #define SEG_COUNT      2
#elif (SEG3_GPIO_PIN == NO_PIN)    
    #define SEG_COUNT      3
#elif (SEG4_GPIO_PIN == NO_PIN)    
    #define SEG_COUNT      4
#elif (SEG5_GPIO_PIN == NO_PIN)    
    #define SEG_COUNT      5
#elif (SEG6_GPIO_PIN == NO_PIN)    
    #define SEG_COUNT      6
#elif (SEG7_GPIO_PIN == NO_PIN)    
    #define SEG_COUNT      7
#else
    #define SEG_COUNT      8
#endif
#if (COM0_GPIO_PIN == NO_PIN)
    #error "error! At least 1 COM must be enabled"
    #define COM_COUNT      0
#elif (COM1_GPIO_PIN == NO_PIN)    
    #define COM_COUNT      1
#elif (COM2_GPIO_PIN == NO_PIN)    
    #define COM_COUNT      2
#elif (COM3_GPIO_PIN == NO_PIN)    
    #define COM_COUNT      3
#elif (COM4_GPIO_PIN == NO_PIN)    
    #define COM_COUNT      4
#else
    #define COM_COUNT      5
#endif
#endif

#if APP_TM1624_ENABLE
#include "tm1624.h"
#endif

#if APP_TM1640_ENABLE
#include "tm1640.h"
#endif

#if APP_IR_RECEIVED_ENABLE
#if (D_IR_TIM == 1)
#if (APP_TIM1_ENABLE == 0)
    #error "error! TIM1 must be enabled for IR"
#endif
#define D_IR_sample         TIM1_TIMING_TIME
#elif (D_IR_TIM == 14)
#if (APP_TIM14_ENABLE == 0)
    #error "error! TIM14 must be enabled for IR"
#endif
#define D_IR_sample         TIM14_TIMING_TIME
#else
    #error "error! Invalid IR timer selection"
#endif
#if (D_IR_sample < 60 ||D_IR_sample > 250)
    #error "error! IR timer out of range"
#endif
#include "ir_received.h"
#endif

void nop_delay_xus(uint16_t nus);

#endif
