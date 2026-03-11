import sys, io

filepath = r'c:\Project\PUYA\Firmware\PY32T020\PY32T020_Touch\Project\Inc\tk_cfg.h'

with open(filepath, 'rb') as f:
    lines = f.readlines()

new_content = [
    '//  <h> Touch Key Parameters\n',
    '//  <i> Configure touch key sensing parameters\n',
    '//  <o> NOISE Threshold\n',
    '//  <i> Noise threshold setting\n',
    '//  <0-100>\n',
    '#define NOISE_THD_DEFAULT	15\n',
    '//  <o> Sampling Filter Count\n',
    '//  <i> Higher values result in more stable but slower response (range: 1-30)\n',
    '//  <1-30>\n',
    '#define FILTERCOUNT			5\n',
    '//  <o> Max Press Time Out\n',
    '//  <i> Max press time in ms, set to 0 to disable (up to 2 minutes)\n',
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
    '//  <o> Single Key Mode\n',
    '//  <i> Set to enable single key trigger mode\n',
    '//  <0=> DISABLE\n',
    '//  <1=> ENABLE\n',
    '#define SIGLE_KEY_TRIGGER			0		\n',
    '//  <o> Multi-Key Max Trigger Count\n',
    '//  <i> Max number of keys allowed to be triggered simultaneously, 0 to disable limit\n',
    '//  <0-255>\n',
    '#define MAX_TRIGGER_KEY_CNT 		0				\n',
    '// </h>\n',
    '\n',
    '//  <e> Internal Reference Channel\n',
    '//  <i> Enable internal reference channel for environment tracking\n',
    '#define REF_CH_EN				1			\n',
    '//  <o> Reference Channel Threshold\n',
    '//  <i> Internal reference channel threshold setting\n',
    '//  <0-2000>\n',
    '#define REF_CH_THD				50		\n',
    '// </e>\n'
]

# Lines 114 to 168 (1-indexed) are indices 113 to 168 (0-indexed exclusive)
# Wait, let's check exact line count in view_file:
# 114 to 168 inclusive.
slice_start = 113
slice_end = 168

final_lines = lines[:slice_start] + [l.encode('utf-8') for l in new_content] + lines[slice_end:]

with open(filepath, 'wb') as f:
    f.writelines(final_lines)

print("tk_cfg.h fixed")
