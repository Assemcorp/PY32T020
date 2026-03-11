import os
import re

# Dictionary of common Chinese translations for this project
translations = {
    '数码管': '7-segment display',
    '初始化': 'Initialize',
    '功能': 'Function',
    '设置': 'Set',
    '描述': 'Description',
    '传入': 'Input',
    '返回': 'Return',
    '无': 'None',
    '按键': 'Key',
    '次数': 'Count',
    '计数': 'Count',
    '引导码': 'Sync Code',
    '接收': 'Received',
    '缓存': 'Buffer',
    '释放': 'Release',
    '时间': 'Time',
    '高电平': 'High Level',
    '低电平': 'Low Level',
    '扫描': 'Scan',
    '串口': 'UART',
    '定时器': 'Timer',
    '中断': 'Interrupt',
    '队列': 'Queue',
    '成功': 'Success',
    '完成': 'Complete',
    '标志': 'Flag',
    '读取': 'Read',
    '写入': 'Write',
    '清除': 'Clear',
    '测试': 'Test',
    '翻转': 'Toggle',
    '开启': 'Enable',
    '关闭': 'Disable',
    '默认': 'Default',
    '显示': 'Display',
    '内容': 'Content',
    '指示': 'Indicator',
    '入口': 'Entry',
    '出口': 'Exit',
    '引导': 'Sync',
    '校验': 'Verification',
    '数据': 'Data',
    '左移': 'Shift Left',
    '右移': 'Shift Right',
    '清除': 'Clear',
    '标记': 'Mark',
    '地址': 'Address'
}

def translate_match(match):
    text = match.group(0)
    # If the block contains Chinese/mojibake
    if any(ord(c) > 127 for c in text):
        # Extract function name from comment block if possible
        func = re.search(r'void\s+([a-zA-Z0-9_]+)\s*\(', text)
        if not func:
            func = re.search(r'([a-zA-Z0-9_]+)\(void\)', text)
            
        if func:
            name = func.group(1)
            return f'/**\n * @brief  {name} function\n * @param  None\n * @retval None\n */'
        
        # fallback to general documentation
        return '/**\n * @brief  Documentation\n */'
    return text

def clean_file(filepath):
    print(f"Checking {os.path.basename(filepath)}...")
    try:
        with open(filepath, 'rb') as f:
            content = f.read()
            
        # Try GBK first as it's the likely source
        try:
            text = content.decode('gbk')
        except UnicodeDecodeError:
            text = content.decode('utf-8', errors='replace')
            
        # Remove Chinese blocks /**** ... ****/
        text = re.sub(r'/[*]{3,}[\s\S]*?[*]{3,}/', translate_match, text)
        
        # Replace inline comments with translated or English versions
        # A simple way to handle // comments
        lines = text.split('\n')
        new_lines = []
        for line in lines:
            if '//' in line:
                code, comment = line.split('//', 1)
                if any(ord(c) > 127 for c in comment):
                    # For simple inline comments, just replace common terms or make it generic
                    comment = " " + comment.strip()
                    for ch, en in translations.items():
                        comment = comment.replace(ch, en)
                    # If it's still containing non-ascii, just make it English if possible or drop
                    if any(ord(c) > 127 for c in comment):
                         comment = " Documentation"
                    line = code + "//" + comment
            new_lines.append(line)
        text = '\n'.join(new_lines)
        
        # Write back as UTF-8
        with open(filepath, 'w', encoding='utf-8', newline='\n') as f:
            f.write(text)
    except Exception as e:
        print(f"Error on {filepath}: {e}")

# Target directories
dirs = [
    r'c:\Project\PUYA\Firmware\PY32T020\PY32T020_Touch\app_drivers\src',
    r'c:\Project\PUYA\Firmware\PY32T020\PY32T020_Touch\app_drivers\inc',
    r'c:\Project\PUYA\Firmware\PY32T020\PY32T020_Touch\Project\Src',
    r'c:\Project\PUYA\Firmware\PY32T020\PY32T020_Touch\Project\Inc'
]

for d in dirs:
    if not os.path.exists(d): continue
    for f in os.listdir(d):
        if f.endswith(('.c', '.h')):
            clean_file(os.path.join(d, f))

print("Cleanup complete.")
