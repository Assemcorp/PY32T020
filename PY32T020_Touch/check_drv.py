import sys, io
sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8')

filepath = r'c:\Project\PUYA\Firmware\PY32T020\PY32T020_Touch\app_drivers\src\drivers.c'
with open(filepath, 'rb') as f:
    text = f.read().decode('gbk', errors='replace')

for i, line in enumerate(text.split('\n')):
    if 'app_drivers_init' in line or 'app_drivers_loop' in line:
        print(f'{i+1:4d}: {line.rstrip()}')
