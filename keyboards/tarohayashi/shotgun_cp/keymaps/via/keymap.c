// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "add_keycodes.h"
#include "add_encoders.h"

enum layer_names {
    BASE = 0,
    LOWER,
    UPPER,
    LIGHT = 5
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
        KC_TAB, KC_PSLS, KC_PAST, KC_PMNS,
        KC_P7, KC_P8, KC_P9, KC_PPLS,
        KC_P4, KC_P5, KC_P6, KC_PPLS,
        KC_P1, KC_P2, KC_P3, KC_PENT,
        LT(LIGHT, KC_P0), KC_PDOT, KC_PDOT, KC_PENT, 
        XXXXXXX, XXXXXXX, 
        XXXXXXX, XXXXXXX, 
        XXXXXXX, XXXXXXX, 
        XXXXXXX, XXXXXXX, 
        XXXXXXX, XXXXXXX
    ),
    [LIGHT] = LAYOUT(
        XXXXXXX, RGB_SPI, RGB_SPD, RGB_TOG,
        XXXXXXX, RGB_VAI, RGB_VAD, XXXXXXX,
        XXXXXXX, RGB_SAI, RGB_SAD, XXXXXXX,
        XXXXXXX, RGB_HUI, RGB_HUD, XXXXXXX,
        LT(LIGHT, KC_P0), RGB_MOD, RGB_RMOD, XXXXXXX, 
        XXXXXXX, XXXXXXX, 
        XXXXXXX, XXXXXXX, 
        XXXXXXX, XXXXXXX, 
        XXXXXXX, XXXXXXX, 
        XXXXXXX, XXXXXXX
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    process_record_addedkeycodes(keycode, record);
    return true;
}

void matrix_scan_user(void){
    matrix_scan_addedencoders();
}

