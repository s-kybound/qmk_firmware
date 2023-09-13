// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
                    LSG(KC_S), KC_HOME, KC_END,  KC_BSPC,
        LCTL(KC_0), KC_BTN1,   KC_UP,   KC_BTN2,
                    KC_LEFT,   KC_DOWN, KC_RGHT, LT(3, KC_ENT),
        // LEVER
        RCS(KC_TAB), _______, LCTL(KC_TAB),
        LCTL(KC_KP_PLUS),LCTL(KC_KP_MINUS), KC_WH_U, KC_WH_D, KC_WH_L, KC_WH_R
  ),
  [1] = LAYOUT(
                 XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        // LEVER
        XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  ),
  [2] = LAYOUT(
                 XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        // LEVER
        XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  ),
  [3] = LAYOUT(
                 RGB_HUI, RGB_SAI, RGB_VAI, RGB_RMOD,
        RGB_TOG, _______, RGB_MOD, _______,
                 RGB_HUD, RGB_SAD, RGB_VAD, LT(5, KC_ENT),
        RGB_SPI, _______, RGB_SPD,
        RGB_MOD, RGB_RMOD, RGB_VAI, RGB_VAD, RGB_HUI, RGB_HUD
  )
};

keyevent_t encoder1_ccw = {
    .type = ENCODER_CCW_EVENT,
    .key = (keypos_t){.row = 4, .col = 5},
    .pressed = false
};

keyevent_t encoder1_cw = {
    .type = ENCODER_CW_EVENT,
    .key = (keypos_t){.row = 4, .col = 6},
    .pressed = false
};

keyevent_t encoder2_ccw = {
    .type = ENCODER_CCW_EVENT,
    .key = (keypos_t){.row = 5, .col = 5},
    .pressed = false
};

keyevent_t encoder2_cw = {
    .type = ENCODER_CW_EVENT,
    .key = (keypos_t){.row = 5, .col = 6},
    .pressed = false
};

keyevent_t encoder3_ccw = {
    .type = ENCODER_CCW_EVENT,
    .key = (keypos_t){.row = 6, .col = 6},
    .pressed = false
};

keyevent_t encoder3_cw = {
    .type = ENCODER_CW_EVENT,
    .key = (keypos_t){.row = 6, .col = 5},
    .pressed = false
};

void matrix_scan_user(void){
    if (encoder1_ccw.pressed){
        encoder1_ccw.pressed = false;
        encoder1_ccw.time = (timer_read() | 1);
        action_exec(encoder1_ccw);
    }
    if (encoder1_cw.pressed){
        encoder1_cw.pressed = false;
        encoder1_cw.time = (timer_read() | 1);
        action_exec(encoder1_cw);
    }
    if (encoder2_ccw.pressed){
        encoder2_ccw.pressed = false;
        encoder2_ccw.time = (timer_read() | 1);
        action_exec(encoder2_ccw);
    }
    if (encoder2_cw.pressed){
        encoder2_cw.pressed = false;
        encoder2_cw.time = (timer_read() | 1);
        action_exec(encoder2_cw);
    }
    if (encoder3_ccw.pressed){
        encoder3_ccw.pressed = false;
        encoder3_ccw.time = (timer_read() | 1);
        action_exec(encoder3_ccw);
    }
    if (encoder3_cw.pressed){
        encoder3_cw.pressed = false;
        encoder3_cw.time = (timer_read() | 1);
        action_exec(encoder3_cw);
    }
}


bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            encoder1_cw.pressed = true;
            encoder1_cw.time = (timer_read() | 1);
            action_exec(encoder1_cw);
        } else {
            encoder1_ccw.pressed = true;
            encoder1_ccw.time = (timer_read() | 1);
            action_exec(encoder1_ccw);
        }
    }else if (index == 1) {
        if (clockwise) {
            encoder2_cw.pressed = true;
            encoder2_cw.time = (timer_read() | 1);
            action_exec(encoder2_cw);
        } else {
            encoder2_ccw.pressed = true;
            encoder2_ccw.time = (timer_read() | 1);
            action_exec(encoder2_ccw);
        }
    }else if (index == 2) {
        if (clockwise) {
            encoder3_cw.pressed = true;
            encoder3_cw.time = (timer_read() | 1);
            action_exec(encoder3_cw);
        } else {
            encoder3_ccw.pressed = true;
            encoder3_ccw.time = (timer_read() | 1);
            action_exec(encoder3_ccw);
        }
    }
    return false;
}