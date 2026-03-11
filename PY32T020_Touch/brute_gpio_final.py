import re, io, sys

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8')
filepath = r'c:\Project\PUYA\Firmware\PY32T020\PY32T020_Touch\app_drivers\src\gpio.c'

with open(filepath, 'rb') as f:
    text = f.read().decode('utf-8', errors='ignore')

# We can replace blocks based on known ASCII context around the Chinese characters.

replacements = [
    (r'/\*+\s*\n\*\*\s*[^\n]*void GPIO_Init\(uint8_t gpio,uint32_t Init\)\s*\n[\s\S]*?\*\*\s*[^\n]*\n\*+/', 
     """/**
 * @brief  Initialize GPIO
 * @param  gpio : GPIO pin ID (e.g., PA0~PA15, PB0~PB3, PF0~PF5)
 * @param  Init : Modes and configurations combined with bitwise OR (|)
 *                Convert GPIO to analog mode: GPIO_Init(PA0, ANALOG)
 *                Convert GPIO to input with pull-up: GPIO_Init(PA0, INPUT|PULL_UP)
 *                Convert GPIO to input with pull-up & falling EXTI: GPIO_Init(PA0, INPUT|PULL_UP|EXTI_TRIGGER_FALLING)
 *                Convert GPIO to push-pull output: GPIO_Init(PA0, OUTPUT|PUSHPULL)
 *                Convert GPIO to open-drain output: GPIO_Init(PA0, OUTPUT|OPENDRAIN)
 *                Convert GPIO to TIM1_CH3 output: GPIO_Init(PA0, ALTERNATE|GPIO_TIM1_AF2)
 *                                                 (Check datasheet mappings to select AF2 or AF5 properly)
 *                Convert GPIO to UART function: GPIO_Init(PA0, ALTERNATE|GPIO_UART2)
 * @retval None
 */"""),
 
    (r'uint32_t Mode\s*=\s*\(Init \& 0X000000F\);\s*//.*', 'uint32_t Mode      = (Init & 0X000000F);		// Direction'),
    (r'uint32_t Pull\s*=\s*\(Init \& 0X00000F0\);\s*//.*', 'uint32_t Pull      = (Init & 0X00000F0);		// Pull up/down'),
    (r'uint32_t OutputType\s*=\s*\(Init \& 0X0000F00\);\s*//.*', 'uint32_t OutputType= (Init & 0X0000F00);		// Output mode'),
    (r'uint32_t Alternate\s*=\s*\(Init \& 0X000F000\);\s*//.*', 'uint32_t Alternate = (Init & 0X000F000);		// Alternate function mode'),
    (r'uint32_t Exti\s*=\s*\(Init \& 0X00F0000\);\s*//.*', 'uint32_t Exti      = (Init & 0X00F0000);		// External interrupt mode')
]

for pat, repl in replacements:
    text = re.sub(pat, repl, text)

with open(filepath, 'w', encoding='utf-8', newline='\n') as f:
    f.write(text)

print("Fixed GPIO problem lines.")
