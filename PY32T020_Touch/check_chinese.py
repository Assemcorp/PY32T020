import os

dirs = [
    r'c:\Project\PUYA\Firmware\PY32T020\PY32T020_Touch\app_drivers\src',
    r'c:\Project\PUYA\Firmware\PY32T020\PY32T020_Touch\app_drivers\inc',
    r'c:\Project\PUYA\Firmware\PY32T020\PY32T020_Touch\Project\Src',
    r'c:\Project\PUYA\Firmware\PY32T020\PY32T020_Touch\Project\Inc'
]

found = False
for d in dirs:
    if not os.path.exists(d): continue
    for f in os.listdir(d):
        if f.endswith('.c') or f.endswith('.h'):
            filepath = os.path.join(d, f)
            try:
                with open(filepath, 'rb') as file:
                    content = file.read()
                    try:
                        decoded = content.decode('utf-8')
                        # Check for chinese characters
                        for char in decoded:
                            if '\u4e00' <= char <= '\u9fff':
                                print(f"Chinese found in UTF-8 decoded {filepath}")
                                found = True
                                break
                    except UnicodeDecodeError:
                        print(f"Non-UTF-8 (likely GBK with Chinese) found in {filepath}")
                        found = True
            except Exception as e:
                pass

if not found:
    print("No Chinese or non-UTF8 files found!")
