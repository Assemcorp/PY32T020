import sys, io

filepath = r'c:\Project\PUYA\Firmware\PY32T020\PY32T020_Touch\Project\Inc\tk_cfg.h'

with open(filepath, 'r', encoding='utf-8') as f:
    lines = f.readlines()

new_content = [
    '//  <h> Touch Key Parameters\n',
    '//  <i> Configure touch key sensing parameters\n',
    '//  <o> Noise Threshold\n',
    '//  <i> Noise threshold setting\n',
    '//  <0-100>\n',
    '#define NOISE_THD_DEFAULT	15\n',
    '//  <o> Filter Count\n',
    '//  <i> Value range 1-30, higher means more stable but slower response\n',
    '//  <1-30>\n',
    '#define FILTERCOUNT			5\n',
    '//  <o> Max Long Press Timeout\n',
    '//  <i> Unit ms, max 2 minutes, set 0 to disable\n',
    '//  <0-120000>\n',
    '#define KEY_OUT_MAX_TIME					30000\n',
    '\n',
    '#define KEY_OUT_MAX_TICK_CNT				(KEY_OUT_MAX_TIME / 5)	\n',
    '//  <o> Finger Confirm Tick Count\n',
    '//  <i> Debounce time for key press (unit: 5ms)\n',
    '//  <0-100>\n',
    '#define FINGER_CONFIRM_TICK_CNT					(5) 		\n',
    '//  <o> Finger Release Confirm Tick Count\n',
    '//  <i> Debounce time for key release (unit: 5ms)\n',
    '//  <0-100>\n',
    '#define FINGER_RELEASE_CONFIRM_TICK_CNT			(5)  		\n',
    '//  <o> Water Area Confirm Tick Count\n',
    '//  <i> Unit: 5ms\n',
    '//  <0-1000>\n',
    '#define WATER_AREA_CONFIRM_TICK_CNT				(150)\n',
    '//  <o> Noise Area Confirm Tick Count\n',
    '//  <i> Unit: 5ms\n',
    '//  <0-1000>\n',
    '#define NOISE_AREA_CONFIRM_TICK_CNT				(100)\n',
    '//  <o> Button Area Confirm Tick Count\n',
    '//  <i> Unit: 5ms\n',
    '//  <0-1000>\n',
    '#define BOTTON_AREA_CONFIRM_TICK_CNT			(60)\n',
    '//  <o> Single Key Trigger\n',
    '//  <i> Set to enable single key mode\n',
    '//  <0=> DISABLE\n',
    '//  <1=> ENABLE\n',
    '#define SIGLE_KEY_TRIGGER			0		\n',
    '//  <o> Multi-Key Trigger Count\n',
    '//  <i> Multi-key trigger baseline threshold, 0 to disable\n',
    '//  <0-255>\n',
    '#define MAX_TRIGGER_KEY_CNT 		0				\n',
    '// </h>\n',
    '\n',
    '//  <e> Internal Reference Channel\n',
    '//  <i> Enable internal reference channel\n',
    '#define REF_CH_EN				1			\n',
    '//  <o> Threshold\n',
    '//  <i> Internal reference channel threshold value\n',
    '//  <0-2000>\n',
    '#define REF_CH_THD				50		\n',
    '// </e>\n'
]

# Lines 114 to 168 (1-indexed) are indices 113 to 168
slice_start = 113
slice_end = 168

final_lines = lines[:slice_start] + new_content + lines[slice_end:]

with open(filepath, 'w', encoding='utf-8', newline='\n') as f:
    f.writelines(final_lines)

print("tk_cfg.h fixed")
