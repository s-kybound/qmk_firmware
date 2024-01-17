#include QMK_KEYBOARD_H
#include "features/achordion.h"

#define _LAYER0 0
#define _LAYER1 1
#define _LAYER2 2
#define _LAYER3 3
#define _LAYER4 4
#define _LAYER5 5
#define _LAYER6 6
#define _LAYER7 7

enum custom_keycodes {
    LAYER0 = SAFE_RANGE,
    LAYER1,
    LAYER2,
    LAYER3,
    LAYER4,
    LAYER5,
    LAYER6,
    LAYER7,
};

const uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case LT(2, KC_ESC):
        case LT(3, KC_SPC):
        case LT(4, KC_TAB):
        case LT(5, KC_ENT):
        case LT(6, KC_BSPC):
        case LT(7, KC_DEL):
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

 [_LAYER0] = LAYOUT(KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_PSCR, KC_MINS, KC_Q, KC_W, KC_F, KC_P, KC_B, KC_MINS, KC_EQL, KC_J, KC_L, KC_U, KC_Y, KC_QUOT, KC_BSLS, KC_CAPS, LGUI_T(KC_A), LALT_T(KC_R), LCTL_T(KC_S), LSFT_T(KC_T), KC_G, KC_LBRC, KC_RBRC, KC_M, RSFT_T(KC_N), RCTL_T(KC_E), LALT_T(KC_I), RGUI_T(KC_O), KC_SCLN, KC_LPRN, LT(1,KC_Z), KC_X, KC_C, KC_D, KC_V, KC_UNDS, KC_PGUP, KC_PGDN, KC_PIPE, KC_K, KC_H, KC_COMM, KC_DOT, LT(1,KC_SLSH), KC_RPRN, KC_VOLD, KC_VOLU, KC_APP, LT(2,KC_ESC), LT(3,KC_SPC), LT(4,KC_TAB), KC_HOME, KC_END, LT(5,KC_ENT), LT(6,KC_BSPC), LT(7,KC_DEL), KC_MUTE, KC_BRID, KC_BRIU),

[_LAYER1] = LAYOUT(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_UNDO, KC_CUT, KC_COPY, KC_PSTE, KC_AGIN, KC_NO, KC_NO, KC_AGIN, KC_PSTE, KC_COPY, KC_CUT, KC_UNDO, KC_NO, KC_NO, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, KC_NO, KC_NO, KC_UNDO, KC_CUT, KC_COPY, KC_PSTE, KC_AGIN, KC_NO, KC_NO, KC_NO, KC_NO, KC_AGIN, KC_PSTE, KC_COPY, KC_CUT, KC_UNDO, KC_NO, KC_NO, KC_NO, KC_NO, KC_BTN3, KC_BTN2, KC_BTN1, KC_NO, KC_NO, KC_BTN1, KC_BTN2, KC_BTN3, KC_NO, KC_NO, KC_NO),

[_LAYER2] = LAYOUT(KC_LT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_GT, KC_LCBR, QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_RCBR, KC_LBRC, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO, KC_MRWD, KC_VOLD, KC_VOLU, KC_MFFD, KC_RBRC, KC_LPRN, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_RPRN, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MSTP, KC_MPLY, KC_MUTE, KC_NO, KC_NO, KC_NO),

[_LAYER3] = LAYOUT(KC_LT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_GT, KC_LCBR, QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_AGIN, KC_PSTE, KC_COPY, KC_CUT, KC_UNDO, KC_RCBR, KC_LBRC, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO, KC_NO, KC_NO, KC_CAPS, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_RBRC, KC_LPRN, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_INS, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_RPRN, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_ENT, KC_BSPC, KC_DEL, KC_NO, KC_NO, KC_NO),

[_LAYER4] = LAYOUT(KC_LT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_GT, KC_LCBR, QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_AGIN, KC_PSTE, KC_COPY, KC_CUT, KC_UNDO, KC_RCBR, KC_LBRC, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_RBRC, KC_LPRN, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, KC_RPRN, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_BTN1, KC_BTN2, KC_BTN3, KC_NO, KC_NO, KC_NO),

[_LAYER5] = LAYOUT(KC_LT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_GT, KC_LCBR, KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, QK_BOOT, KC_RCBR, KC_LBRC, KC_COLN, KC_DLR, KC_PERC, KC_CIRC, KC_PLUS, KC_NO, KC_NO, KC_NO, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, KC_RBRC, KC_LPRN, KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_PIPE, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_RPRN, KC_NO, KC_NO, KC_NO, KC_LPRN, KC_RPRN, KC_UNDS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),

[_LAYER6] = LAYOUT(KC_LT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_GT, KC_LCBR, KC_LBRC, KC_7, KC_8, KC_9, KC_RBRC, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, QK_BOOT, KC_RCBR, KC_LBRC, KC_SCLN, KC_4, KC_5, KC_6, KC_EQL, KC_NO, KC_NO, KC_NO, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, KC_RBRC, KC_LPRN, KC_GRV, KC_1, KC_2, KC_3, KC_BSLS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_RPRN, KC_NO, KC_NO, KC_NO, KC_DOT, KC_0, KC_MINS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),

[_LAYER7] = LAYOUT(KC_LT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_GT, KC_LCBR, KC_F12, KC_F7, KC_F8, KC_F9, KC_PSCR, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, QK_BOOT, KC_RCBR, KC_LBRC, KC_F11, KC_F4, KC_F5, KC_F6, KC_SCRL, KC_NO, KC_NO, KC_NO, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, KC_RBRC, KC_LPRN, KC_F10, KC_F1, KC_F2, KC_F3, KC_PAUS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_RPRN, KC_NO, KC_NO, KC_NO, KC_APP, KC_SPC, KC_TAB, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO) 

};

