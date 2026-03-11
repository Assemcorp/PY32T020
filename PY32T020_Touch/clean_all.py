import os, re
import glob

dirs = [
    r'c:\Project\PUYA\Firmware\PY32T020\PY32T020_Touch\app_drivers\src',
    r'c:\Project\PUYA\Firmware\PY32T020\PY32T020_Touch\app_drivers\inc',
]

def clean_inline_comments(text):
    lines = text.split('\n')
    out = []
    for line in lines:
        if '//' in line:
            parts = line.split('//')
            if any(ord(c) > 127 for c in parts[1]):
                line = parts[0].rstrip()
        out.append(line)
    return '\n'.join(out)

def clean_block_comments(text):
    # Find all /**** ... ****/ blocks
    # and replace them with /** @brief FunctionName */ if it's a function header
    
    def replacer(match):
        block = match.group(0)
        # If block contains non-ASCII characters
        if any(ord(c) > 127 for c in block):
            # Try to extract the function name from the line after the block
            # Or from inside the block
            func_name = ""
            m = re.search(r'(?:void|uint8_t|uint16_t|uint32_t|int)\s+([a-zA-Z0-9_]+)\s*\(', block)
            if m:
                func_name = m.group(1)
            else:
                # check after the block
                pass
                
            if not func_name:
                return '/**\n * @brief  Documentation\n */'
            
            return f'/**\n * @brief  {func_name}\n * @param  None\n * @retval None\n */'
        return block

    # match regular Chinese block comments
    text = re.sub(r'/[*]{2,}[\s\S]*?[*]{2,}/', replacer, text)
    
    # match any other /** */ block comments with chinese
    def replacer2(match):
        block = match.group(0)
        if any(ord(c) > 127 for c in block):
            return '/**\n * @brief  Documentation\n */'
        return block
    text = re.sub(r'/[*][\s\S]*?[*]/', replacer2, text)
    return text

for d in dirs:
    if not os.path.exists(d): continue
    for f in os.listdir(d):
        if f.endswith('.c') or f.endswith('.h'):
            filepath = os.path.join(d, f)
            with open(filepath, 'rb') as file:
                content = file.read()
            
            try:
                # Try UTF-8 first
                text = content.decode('utf-8')
            except UnicodeDecodeError:
                # Fallback to GBK
                text = content.decode('gbk', errors='replace')
                
            # Only modify if it contains non-ASCII
            if any(ord(c) > 127 for c in text):
                text = clean_inline_comments(text)
                text = clean_block_comments(text)
                
                # Check for remaining non-ASCII
                remaining = [c for c in text if ord(c) > 127]
                if remaining:
                    # just strip all other non-ASCII characters like mojibake in strings/macros
                    new_text = ""
                    for c in text:
                        if ord(c) <= 127:
                            new_text += c
                        else:
                            new_text += " "
                    text = new_text

                with open(filepath, 'w', encoding='utf-8', newline='\n') as file:
                    file.write(text)
                print(f"Cleaned {f}")
