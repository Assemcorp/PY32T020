import os, re
import sys, io

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8')

files_to_check = [
    r'c:\Project\PUYA\Firmware\PY32T020\PY32T020_Touch\app_drivers\src\adc_drivers.c',
    r'c:\Project\PUYA\Firmware\PY32T020\PY32T020_Touch\app_drivers\src\argb_task.c',
    r'c:\Project\PUYA\Firmware\PY32T020\PY32T020_Touch\app_drivers\src\smg_drivers.c',
    r'c:\Project\PUYA\Firmware\PY32T020\PY32T020_Touch\app_drivers\src\spi-led_drivers.c',
    r'c:\Project\PUYA\Firmware\PY32T020\PY32T020_Touch\app_drivers\src\tim14_drivers.c',
    r'c:\Project\PUYA\Firmware\PY32T020\PY32T020_Touch\app_drivers\src\tim1_drivers.c',
    r'c:\Project\PUYA\Firmware\PY32T020\PY32T020_Touch\app_drivers\src\tm1624.c',
    r'c:\Project\PUYA\Firmware\PY32T020\PY32T020_Touch\app_drivers\src\tm1640.c',
    r'c:\Project\PUYA\Firmware\PY32T020\PY32T020_Touch\app_drivers\src\uart_drivers.c',
    r'c:\Project\PUYA\Firmware\PY32T020\PY32T020_Touch\app_drivers\src\uart_task.c',
    r'c:\Project\PUYA\Firmware\PY32T020\PY32T020_Touch\app_drivers\src\user-otp_drivers.c'
]

for fpath in files_to_check:
    print(f"--- {os.path.basename(fpath)} ---")
    try:
        with open(fpath, 'rb') as f:
            content = f.read().decode('gbk', errors='replace')
        
        matches = re.findall(r'/\*+.*?\*+/', content, re.DOTALL)
        for m in matches:
            if any('\u4e00' <= char <= '\u9fff' for char in m):
                print(repr(m[:100]))
                
        lines = content.split('\n')
        for i, line in enumerate(lines):
            target = line.split('//')
            if len(target) > 1:
                comment = target[1]
                if any('\u4e00' <= char <= '\u9fff' for char in comment):
                    print(f"Line {i+1}: {line.strip()}")
    except Exception as e:
        print(f"Error: {e}")

