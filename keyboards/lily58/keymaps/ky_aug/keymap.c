#include QMK_KEYBOARD_H

#define _LAYER0 0
#define _LAYER1 1
#define _LAYER2 2
#define _LAYER3 3
#define _LAYER4 4
#define _LAYER5 5
#define _LAYER6 6

#ifdef OLED_ENABLE

static void print_state(int check, const char * state) {
    oled_write(state, false);
    oled_write_P(PSTR(": "), false);
    oled_write_P(check ? PSTR("[ ACTIVE ]\n") : PSTR("[        ]\n"), false);
}

static void render_status(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("CURRENT: "), false);

    switch (get_highest_layer(layer_state)) {
        case _LAYER0:
            oled_write_P(PSTR("[ BASE   ]\n"), false);
            break;
        case _LAYER1:
            oled_write_P(PSTR("[ MEDIA  ]\n"), false);
            break;
        case _LAYER2:
            oled_write_P(PSTR("[ NAVI   ]\n"), false);
            break;
        case _LAYER3:
            oled_write_P(PSTR("[ MOUSE  ]\n"), false);
            break;
        case _LAYER4:
            oled_write_P(PSTR("[ SYMBOL ]\n"), false);
            break;
        case _LAYER5:
            oled_write_P(PSTR("[ NUMBER ]\n"), false);
            break;
        case _LAYER6:
            oled_write_P(PSTR("[ FUNCT  ]\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("!!DEBUG!!"), false);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    print_state(led_state.num_lock, "NUM-LCK");
    print_state(led_state.caps_lock, "CAP-LCK");
    print_state(led_state.scroll_lock, "SCR-LCK");
}

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_left()) {
        return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
    }
    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_logo();  // Renders a static logo
        if (is_keyboard_left()) {
            oled_scroll_left();  // Turns on scrolling
        } else {
            oled_scroll_right();
        }
    }
    return false;
}

#endif

enum custom_keycodes {
    LAYER0 = SAFE_RANGE,
    LAYER1,
    LAYER2,
    LAYER3,
    LAYER4,
    LAYER5,
    LAYER6,
};

const uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case LT(1, KC_ESC):
        case LT(2, KC_SPC):
        case LT(3, KC_TAB):
        case LT(4, KC_ENT):
        case LT(5, KC_BSPC):
        case LT(6, KC_DEL):
            // Thumb row gets normal tapping term
            return TAPPING_TERM;
        default:
            // Home row mods get quick tap
            return QUICK_TAP_TERM;
    }
};

const uint16_t get_tapping_term(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case LGUI_T(KC_A):
        case LALT_T(KC_R):
        case LCTL_T(KC_S):
        case LSFT_T(KC_T):
        case RSFT_T(KC_N):
        case RCTL_T(KC_E):
        case LALT_T(KC_I):
        case RGUI_T(KC_O):
            // In case I ever want to reconfigure home row tapping term
            return TAPPING_TERM;
        default:
            return TAPPING_TERM;
    }
};

#ifdef USE_ACHORDION

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (!process_achordion(keycode, record)) {
        return false;
    }
    return true;
}

bool achordion_chord(uint16_t tap_hold_keycode, keyrecord_t* tap_hold_record, uint16_t other_keycode, keyrecord_t* other_record) {
    switch (other_keycode) {
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            other_keycode &= 0xff; // Get base keycode.
    }
    // Allow same-hand holds with non-alpha keys.
    if (other_keycode > KC_Z) {
        return true;
    }

    return achordion_opposite_hands(tap_hold_record, other_record);
}

uint16_t achordion_timeout(uint16_t tap_hold_keycode) {
  return 500;  // Otherwise use a timeout of 800 ms.
}

bool achordion_eager_mod(uint8_t mod) {
  switch (mod) {
    case MOD_LSFT:
    case MOD_RSFT:
    case MOD_LCTL:
    case MOD_RCTL:
    case MOD_LALT:
      return true;  // Eagerly apply Shift and Ctrl mods.
    default:
      return false;
  }
}

void matrix_scan_user(void) {
    achordion_task();
}

#endif


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 [_LAYER0] = LAYOUT(KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_PSCR, KC_MINS, KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, KC_QUOT, KC_BSLS, KC_CAPS, LGUI_T(KC_A), LALT_T(KC_R), LCTL_T(KC_S), LSFT_T(KC_T), KC_G, KC_M, RSFT_T(KC_N), RCTL_T(KC_E), LALT_T(KC_I), LGUI_T(KC_O), KC_SCLN, KC_LPRN, KC_Z, KC_X, KC_C, KC_D, KC_V, KC_LBRC, KC_RBRC, KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, KC_RPRN, KC_HOME, LT(1,KC_ESC), LT(2,KC_SPC), LT(3,KC_TAB), LT(4,KC_ENT), LT(5,KC_BSPC), LT(6,KC_DEL), KC_END),

[_LAYER1] = LAYOUT(KC_LT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_GT, KC_LCBR, QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_RCBR, KC_LBRC, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO, KC_NO, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_RBRC, KC_LPRN, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_RPRN, KC_NO, KC_NO, KC_NO, KC_NO, KC_MSTP, KC_MPLY, KC_MUTE, KC_NO),

[_LAYER2] = LAYOUT(KC_LT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_GT, KC_LCBR, QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO, KC_AGIN, KC_PSTE, KC_COPY, KC_CUT, KC_UNDO, KC_RCBR, KC_LBRC, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO, KC_CAPS, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_RBRC, KC_LPRN, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_INS, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_RPRN, KC_NO, KC_NO, KC_NO, KC_NO, KC_ENT, KC_BSPC, KC_DEL, KC_NO),

[_LAYER3] = LAYOUT(KC_LT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_GT, KC_LCBR, QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO, KC_AGIN, KC_PSTE, KC_COPY, KC_CUT, KC_UNDO, KC_RCBR, KC_LBRC, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO, KC_NO, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_RBRC, KC_LPRN, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, KC_RPRN, KC_NO, KC_NO, KC_NO, KC_NO, KC_BTN1, KC_BTN2, KC_BTN3, KC_NO),

[_LAYER4] = LAYOUT(KC_LT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_GT, KC_LCBR, KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR, KC_NO, KC_NO, KC_NO, KC_NO, QK_BOOT, KC_RCBR, KC_LBRC, KC_COLN, KC_DLR, KC_PERC, KC_CIRC, KC_PLUS, KC_NO, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, KC_RBRC, KC_LPRN, KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_PIPE, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_RPRN, KC_NO, KC_LPRN, KC_RPRN, KC_UNDS, KC_NO, KC_NO, KC_NO, KC_NO),

[_LAYER5] = LAYOUT(KC_LT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_GT, KC_LCBR, KC_LBRC, KC_7, KC_8, KC_9, KC_RBRC, KC_NO, KC_NO, KC_NO, KC_NO, QK_BOOT, KC_RCBR, KC_LBRC, KC_SCLN, KC_4, KC_5, KC_6, KC_EQL, KC_NO, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, KC_RBRC, KC_LPRN, KC_GRV, KC_1, KC_2, KC_3, KC_BSLS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_RPRN, KC_NO, KC_DOT, KC_0, KC_MINS, KC_NO, KC_NO, KC_NO, KC_NO),

[_LAYER6] = LAYOUT(KC_LT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_GT, KC_LCBR, KC_F12, KC_F7, KC_F8, KC_F9, KC_PSCR, KC_NO, KC_NO, KC_NO, KC_NO, QK_BOOT, KC_RCBR, KC_LBRC, KC_F11, KC_F4, KC_F5, KC_F6, KC_SCRL, KC_NO, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, KC_RBRC, KC_LT, KC_F10, KC_F1, KC_F2, KC_F3, KC_PAUS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_GT, KC_NO, KC_APP, KC_SPC, KC_TAB, KC_NO, KC_NO, KC_NO, KC_NO) 

};

