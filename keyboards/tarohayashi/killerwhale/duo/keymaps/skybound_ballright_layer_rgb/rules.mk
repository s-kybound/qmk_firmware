VIA_ENABLE = no
ENCODER_MAP_ENABLE = yes
OS_DETECTION_ENABLE = yes

COMBO_ENABLE = yes 			# For 34-key layout
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
NKRO_ENABLE = no            # Enable N-Key Rollover

DYNAMIC_TAPPING_TERM_ENABLE = yes
SRC += add_keycodes.c
SRC += add_oled.c
SRC += add_trackball.c
SRC += add_joystick.c
SRC += add_rgblayers.c
SRC += features/achordion.c
