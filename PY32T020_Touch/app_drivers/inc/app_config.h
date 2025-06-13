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
//  <o> HSI
//  <24000000UL=> 24MHz
//  <48000000UL=> 48MHz
#define HSI_FREQUENCE        24000000UL

#define fac_us              (HSI_FREQUENCE / 1000000)
//  <o> TK_MODULE
//  <0=> DISABLE
//  <1=> ENABLE
#define APP_TK_ENABLE            1    

//  <e> SYSTICK
#define APP_SYSTICK_ENABLE            1    

#if APP_SYSTICK_ENABLE
#define SYSTICK_TIMING_TIME            1000
#define SYSTICK_IRQ_PRIORITY           0
#define SYSTICK_DEBUG                  0
#define SYSTICK_DEBUG_GPIO             20
#endif
// </e>            

// <e> PRINTF
#define DEBUG_ENABLE            0
#if DEBUG_ENABLE
#define DEBUG_MODE              0    
#define PRINTF_UART             1    
#endif
// </e>

// <e> UART
#define APP_UART_ENABLE         0               
#if APP_UART_ENABLE
#define UART1_ENABLE            1
#if UART1_ENABLE
#define UART1_TX_PIN                6
#define UART1_RX_PIN                7
#define UART1_BAUDRATE              115200
#define UART1_IRQ_ENABLE            1
#define UART1_IRQ_PRIORITY          3
#endif
#define UART2_ENABLE                1
#if UART2_ENABLE
#define UART2_TX_PIN                0
#define UART2_RX_PIN                1
#define UART2_BAUDRATE              115200
#define UART2_IRQ_ENABLE            1
#define UART2_IRQ_PRIORITY          3
#endif
#define UART3_ENABLE                1
#if UART3_ENABLE
#define UART3_TX_PIN                2
#define UART3_RX_PIN                3
#define UART3_BAUDRATE              115200
#define UART3_IRQ_ENABLE            1
#define UART3_IRQ_PRIORITY          3
#endif
#endif
// </e>

// <e> Flash Option byte
#define OB_USER_OPTION              0        
#if OB_USER_OPTION
#define OPTION_NRST_MODE            0
#if OPTION_NRST_MODE
#define OB_GPIO_PIN_MODE        FLASH_OPTR_NRST_MODE
#else
#define OB_GPIO_PIN_MODE        0x00000000U
#endif
#define OPTION_BOR_EN               0
#if OPTION_BOR_EN
#define OB_BOR_EN                   FLASH_OPTR_BOR_EN    
#else
#define OB_BOR_EN                   0x00000000U    
#endif
#define OPTION_BOR_LEV                  4
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
#define OPTION_IWDG_SW_EN              1
#if OPTION_IWDG_SW_EN
#define OB_IWDG_MODE                   FLASH_OPTR_IWDG_SW    
#else
#define OB_IWDG_MODE                   0x00000000U    
#endif
#define OPTION_IWDG_STOP               0
#if OPTION_IWDG_STOP
#define OB_IWDG_STOP                   ((uint32_t)FLASH_OPTR_IWDG_STOP)
#else
#define OB_IWDG_STOP                   0x00000000U    
#endif
#endif

// <e> Flash User OTP    
#define APP_USER_OTP_ENABLE            0
#if APP_USER_OTP_ENABLE
#define LVD_WRITE_USER_DATA            1            
#define low_voltage                    3100
#endif
// </e>

// <e> IWDG
#define APP_IWDG_ENABLE            0               
#define IDWG_RELOAD_VALUE        1500
// </e>

// <e> BEEP
#define APP_BEEP_ENABLE                 1    
#if APP_BEEP_ENABLE
#define BEEP_GPIO                       15
#define BEEP_GPIO_TYPE                  1
#endif
// </e>

// <e> TIM14
#define APP_TIM14_ENABLE            0    
#if APP_TIM14_ENABLE
#define TIM14_TIMING_TIME           125
#define TIM14_IRQ_ENABLE            1
#define TIM14_IRQ_PRIORITY          0
#define TIM14_DEBUG                 0
#define TIM14_DEBUG_GPIO            19
#endif
// </e>

// <e> TIM14-PWM
#define APP_TIM14_PWM_ENABLE        0                
#if APP_TIM14_PWM_ENABLE
#define TIM14_PWM_FREQUENCE         25000
#define TIM14_RESOLUTION            100
#define TIM14_DUTY_CYCLE            10
#define TIM14_CH1_PIN               9
#endif
// </e>

// <e> TIM1
#define APP_TIM1_ENABLE             0    
#if APP_TIM1_ENABLE
#define TIM1_TIMING_TIME            125
#define TIM1_IRQ_ENABLE             1
#define TIM1_IRQ_PRIORITY           0
#define TIM1_DEBUG                  0
#define TIM1_DEBUG_GPIO             20
#endif
// </e>

// <e> TIM1-PWM
#define APP_TIM1_PWM_ENABLE         0                
#if APP_TIM1_PWM_ENABLE
#define TIM1_PWM_FREQUENCE          4000
#define TIM1_RESOLUTION             100
#define TIM1_CH1_ENABLE             1
#define TIM1_DUTY1_CYCLE            10
#define TIM1_CH1_PIN                3
#define TIM1_CH2_ENABLE             1
#define TIM1_DUTY2_CYCLE            20
#define TIM1_CH2_PIN                5
#define TIM1_CH3_ENABLE             1
#define TIM1_DUTY3_CYCLE            30
#define TIM1_CH3_PIN                0
#define TIM1_CH4_ENABLE             1
#define TIM1_DUTY4_CYCLE            50
#define TIM1_CH4_PIN                11
#endif
// </e>

// <e> ADC
#define APP_ADC_ENABLE              0
#if APP_ADC_ENABLE
#define ADC_SPEED                   10
#define ADC_IN0_ENABLE              0    
#define ADC_IN1_ENABLE              0    
#define ADC_IN2_ENABLE              0    
#define ADC_IN3_ENABLE              0    
#define ADC_IN4_ENABLE              0    
#define ADC_IN5_ENABLE              0
#define ADC_IN6_ENABLE              0    
#define ADC_IN7_ENABLE              0    
#define ADC_IN8_ENABLE              0    
#define ADC_IN9_ENABLE              0
#define ADC_IN10_ENABLE             1
#define ADC_IN11_ENABLE             1    
#define ADC_IN12_ENABLE             0    
#endif
// </e>

// <e> SPI-LED
#define APP_SPI_LED_ENABLE          0
#if APP_SPI_LED_ENABLE
#define SPI_LED_PIN                 2    
#define SPI_LED_CNT                 32
#endif
// </e>

// <e> SMG    
#define APP_SMG_ENABLE              1        
#if APP_SMG_ENABLE
#define COM0_GPIO_PIN               12
#define COM1_GPIO_PIN               13
#define COM2_GPIO_PIN               14
#define COM3_GPIO_PIN               26
#define COM4_GPIO_PIN               26
#define SEG0_GPIO_PIN               5
#define SEG1_GPIO_PIN               8
#define SEG2_GPIO_PIN               18
#define SEG3_GPIO_PIN               1
#define SEG4_GPIO_PIN               19
#define SEG5_GPIO_PIN               0
#define SEG6_GPIO_PIN               7
#define SEG7_GPIO_PIN               6
#endif
// </e>

// <e> TM1624    
#define APP_TM1624_ENABLE   0
#define TM1624_CLK          2
#define TM1624_DIN          3
#define TM1624_STB          1
#define TM1624_DISP_COM     3
#define TM1624_DISP_DIM     7
#define TM1624_DISP_TEST    1
// </e>

// <e> TM1640    
#define APP_TM1640_ENABLE   0
#define TM1640_CLK          2
#define TM1640_DIN          3
#define TM1640_DISP_DIM     7
#define TM1640_DISP_TEST    1
// </e>

// <e> IR_RECEIVED    
#define APP_IR_RECEIVED_ENABLE      0
#define IR_GPIO                     20
#define D_IR_TIM                    1
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