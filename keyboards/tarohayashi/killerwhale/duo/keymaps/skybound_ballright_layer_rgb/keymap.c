// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "add_keycodes.h"
#include "add_joystick.h"
#include "add_rgblayers.h"
#include "features/achordion.h"

// レイヤー名
enum layer_number {
    BASE = 0,
    GAME,                                     // A layer designed to work with games expecting a QWERTY keyboard
    ONOFF, OFFON, ONON,                       // トグルスイッチで変更するレイヤー
    MEDIA, NAV, _MOUSE, SYM, NUM, FUN,        // Miryoku-style layers
    LOWER, UPPER,                             // 長押しで変更するレイヤー
    MOUSE, BALL_SETTINGS, LIGHT_SETTINGS      // 自動マウスレイヤー切り替えや設定用のレイヤー
};

enum combos {
    BASE_L,
    BASE_R,
    GAME_L,
    MEDIA_R,
    NAV_R,
    _MOUSE_R,
    SYM_L,
    NUM_L,
    FUN_L
};

const uint16_t PROGMEM base_esc_combo[] = {LT(NAV, KC_SPC), LT(_MOUSE, KC_TAB), COMBO_END};
const uint16_t PROGMEM base_del_combo[] = {LT(SYM, KC_ENT), LT(NUM, KC_BSPC), COMBO_END};
const uint16_t PROGMEM media_combo[] = {KC_MSTP, KC_MPLY, COMBO_END};
const uint16_t PROGMEM nav_combo[] = {KC_ENT, KC_BSPC, COMBO_END};
const uint16_t PROGMEM mse_combo[] = {KC_BTN1, KC_BTN2, COMBO_END};
const uint16_t PROGMEM sym_combo[] = {KC_RPRN, KC_UNDS, COMBO_END};
const uint16_t PROGMEM num_combo[] = {KC_0, KC_MINS, COMBO_END};
const uint16_t PROGMEM fun_combo[] = {KC_SPC, KC_TAB, COMBO_END};
const uint16_t PROGMEM game_combo[] = {KC_SPC, KC_TAB, COMBO_END};
combo_t key_combos[] = {
    [BASE_L] = COMBO(base_esc_combo, LT(MEDIA, KC_ESC)),
    [BASE_R] = COMBO(base_del_combo, LT(FUN, KC_DEL)),
    [GAME_L] = COMBO(fun_combo, KC_ESC),
    [MEDIA_R] = COMBO(media_combo, KC_MUTE),
    [NAV_R] = COMBO(nav_combo, KC_DEL), 
    [_MOUSE_R] = COMBO(mse_combo, KC_BTN3),
    [SYM_L] = COMBO(sym_combo, KC_LPRN),
    [NUM_L] = COMBO(num_combo, KC_DOT),
    [FUN_L] = COMBO(fun_combo, KC_APP),
};

bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    switch (combo_index) {
        case FUN_L:
            if (layer_state_is(GAME)) {
                return false;
            }
        case GAME_L:
            if (layer_state_is(SYM)) {
                return false;
            }
    }

    return true;
}

// キーマップの設定
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
        // 左手 
        // 天面スイッチ
        KC_MINS,        KC_1,           KC_2,           KC_3,           KC_4,           KC_5,
        KC_CAPS,        KC_Q,           KC_W,           KC_F,           KC_P,           KC_B,
        KC_LPRN,        LGUI_T(KC_A),   LALT_T(KC_R),   LCTL_T(KC_S),   LSFT_T(KC_T),   KC_G,
                        KC_Z,           KC_X,           KC_C,           LT(MOUSE, KC_D),KC_V,
                                        KC_MPLY,
        // 側面スイッチ
        LT(NAV, KC_SPC),LT(_MOUSE, KC_TAB),                
        // 十字キーorジョイスティック                                                       // ジョイスティックスイッチ
        KC_UP,          KC_DOWN,        KC_LEFT,        KC_RIGHT,                       KC_ENT,      
        // 追加スイッチ                                                                   // トグルスイッチ
        KC_NO,          KC_NO,                                                          KC_NO,
        // 右手
        KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_BSLS,
        KC_J,           KC_L,           KC_U,           KC_Y,           KC_QUOT,        KC_SCLN,
        KC_M,           RSFT_T(KC_N),   RCTL_T(KC_E),   LALT_T(KC_I),   RGUI_T(KC_O),   KC_RPRN,
        KC_K,           LT(MOUSE, KC_H),KC_COMM,        KC_DOT,         KC_SLSH,
                                                        KC_PSCR,
        // 側面スイッチ
        LT(SYM, KC_ENT),LT(NUM, KC_BSPC),                   
        // 十字キーorジョイスティック                                                       // ジョイスティックスイッチ
        KC_UP,              KC_DOWN,        KC_LEFT,        KC_RIGHT,                   KC_ENT,     
        // 追加スイッチ                                                                   // トグルスイッチ
        KC_MS_BTN2,         KC_MS_BTN1,                                                 MO(GAME)
    ),
    [GAME] = LAYOUT(
        // 左手 
        // 天面スイッチ
        // in this case, the only change to qwerty is a slight shift to put QE-WASD in the middle - else, all is the same
        KC_TAB,         KC_1,           KC_2,           KC_3,           KC_4,           KC_5,
        KC_CAPS,        KC_R,           KC_Q,           KC_W,           KC_E,           KC_T,
        KC_LSFT,        KC_F,           KC_A,           KC_S,           KC_D,           KC_G,
                        KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,
                                        KC_MPLY,
        // 側面スイッチ
        KC_SPC,         KC_TAB,                
        // 十字キーorジョイスティック                                                       // ジョイスティックスイッチ
        KC_UP,          KC_DOWN,        KC_LEFT,        KC_RIGHT,                       KC_ENT,      
        // 追加スイッチ                                                                   // トグルスイッチ
        KC_NO,          KC_NO,                                                          KC_NO,
        // 右手
        // how useful are j and k? in this case, replace with the mouse buttons, and move j, k elsewhere
        KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_BSLS,
        KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_ENT,
        KC_H,           KC_MS_BTN1,     KC_MS_BTN2,     KC_L,           KC_SCLN,        KC_RSFT,
        KC_N,           KC_M,           KC_COMM,        KC_DOT,         KC_SLSH,
                                                            KC_PSCR,
        // 側面スイッチ
        KC_ENT,         KC_BSPC,
        // 十字キーorジョイスティック                                                       // ジョイスティックスイッチ
        KC_UP,          KC_DOWN,        KC_LEFT,        KC_RIGHT,                      KC_ENT,
        // 追加スイッチ                                                                  // トグルスイッチ
        // in case we ever need j and k again, they are now here
        KC_J,           KC_K,                                                          KC_TRNS
    ),
    [MEDIA] = LAYOUT(
        // 左手 
        // 天面スイッチ
        KC_NO,      KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
        KC_NO,      KC_LGUI,    KC_LALT,    KC_LCTL,    KC_LSFT,    KC_NO,
                    KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
                                KC_NO,
        // 側面スイッチ
        KC_NO,      KC_NO,                
        // 十字キーorジョイスティック                                   // ジョイスティックスイッチ
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,                KC_TRNS,      
        // 追加スイッチ                                               // トグルスイッチ
        KC_TRNS,    KC_TRNS,                                        KC_TRNS,
        // 右手
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_NO,
        RGB_TOG,    RGB_MOD,    RGB_HUI,    RGB_SAI,    RGB_VAI,    KC_NO,
        KC_NO,      KC_MRWD,    KC_VOLD,    KC_VOLU,    KC_MFFD,    KC_NO,
        KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
                                            KC_NO,
        // 側面スイッチ
        KC_MSTP,    KC_MPLY,                
        // 十字キーorジョイスティック                                   // ジョイスティックスイッチ
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,                KC_TRNS,      
        // 追加スイッチ                                               // トグルスイッチ
        KC_TRNS,    KC_TRNS,                                        KC_NO
    ),
    [NAV] = LAYOUT(
        // 左手 
        // 天面スイッチ
        KC_NO,      KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
        KC_NO,      KC_LGUI,    KC_LALT,    KC_LCTL,    KC_LSFT,    KC_NO,
                    KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
                                KC_NO,
        // 側面スイッチ
        KC_NO,      KC_NO,                
        // 十字キーorジョイスティック                                   // ジョイスティックスイッチ
        KC_PGUP,    KC_PGDN,    KC_HOME,    KC_END,                 KC_TRNS,      
        // 追加スイッチ                                               // トグルスイッチ
        KC_TRNS,    KC_TRNS,                                        KC_TRNS,
        // 右手
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_NO,
        UNDO,       CUT,        COPY,       PASTE,      REDO,       KC_NO,
        KC_CAPS,    KC_LEFT,    KC_DOWN,    KC_UP,      KC_RIGHT,   KC_NO,
        KC_INS,     KC_HOME,    KC_PGDN,    KC_PGUP,    KC_END,
                                            KC_NO,
        // 側面スイッチ
        KC_ENT,     KC_BSPC,                
        // 十字キーorジョイスティック                                   // ジョイスティックスイッチ
        KC_PGUP,    KC_PGDN,    KC_HOME,    KC_END,                 KC_TRNS,      
        // 追加スイッチ                                               // トグルスイッチ
        KC_TRNS,    KC_TRNS,                                        KC_TRNS
    ),
    [_MOUSE] = LAYOUT(
        // 左手 
        // 天面スイッチ
        KC_NO,      KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
        KC_NO,      KC_LGUI,    KC_LALT,    KC_LCTL,    KC_LSFT,    KC_NO,
                    KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
                                KC_NO,
        // 側面スイッチ
        KC_NO,      KC_NO,                
        // 十字キーorジョイスティック                                   // ジョイスティックスイッチ
        KC_UP,      KC_DOWN,    KC_LEFT,    KC_RIGHT,               KC_TRNS,      
        // 追加スイッチ                                               // トグルスイッチ
        KC_TRNS,    KC_TRNS,                                        KC_TRNS,
        // 右手
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_NO,
        UNDO,       CUT,        COPY,       PASTE,      REDO,       KC_NO,
        KC_NO,      KC_MS_L,    KC_MS_D,    KC_MS_U,    KC_MS_R,    KC_NO,
        KC_NO,      KC_WH_L,    KC_WH_D,    KC_WH_U,    KC_WH_R,
                                            KC_NO,
        // 側面スイッチ 
        KC_BTN1,    KC_BTN2,                
        // 十字キーorジョイスティック                                   // ジョイスティックスイッチ
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,                KC_TRNS,      
        // 追加スイッチ                                               // トグルスイッチ
        KC_TRNS,    KC_TRNS,                                        KC_TRNS   
    ),
    [SYM] = LAYOUT(
        // 左手 
        // 天面スイッチ
        KC_NO,      KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_NO,      KC_LCBR,    KC_AMPR,    KC_ASTR,    KC_LPRN,    KC_RCBR,
        KC_NO,      KC_COLN,    KC_DLR,     KC_PERC,    KC_CIRC,    KC_PLUS, 
                    KC_TILD,    KC_EXLM,    KC_AT,      KC_HASH,    KC_PIPE,
                                KC_NO,
        // 側面スイッチ
        KC_RPRN,    KC_UNDS,                
        // 十字キーorジョイスティック                                   // ジョイスティックスイッチ
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,                KC_TRNS,      
        // 追加スイッチ                                               // トグルスイッチ
        KC_TRNS,    KC_TRNS,                                        KC_TRNS,
        // 右手
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_NO,
        KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
        KC_NO,      KC_RSFT,    KC_RCTL,    KC_LALT,    KC_RGUI,    KC_NO,
        KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
                                            KC_NO,
        // 側面スイッチ
        KC_NO,      KC_NO,                
        // 十字キーorジョイスティック                                   // ジョイスティックスイッチ
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,                KC_TRNS,      
        // 追加スイッチ                                               // トグルスイッチ
        KC_TRNS,    KC_TRNS,                                        KC_TRNS
    ),
    [NUM] = LAYOUT(
        // 左手 
        // 天面スイッチ
        KC_NO,      KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_NO,      KC_LBRC,    KC_7,       KC_8,       KC_9,       KC_RBRC,
        KC_NO,      KC_SCLN,    KC_4,       KC_5,       KC_6,       KC_EQL,
                    KC_GRV,     KC_1,       KC_2,       KC_3,       KC_BSLS,
                                KC_NO,
        // 側面スイッチ
        KC_0,       KC_MINS,                
        // 十字キーorジョイスティック                                   // ジョイスティックスイッチ
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,                KC_TRNS,      
        // 追加スイッチ                                               // トグルスイッチ
        KC_TRNS,    KC_TRNS,                                        KC_TRNS,
        // 右手
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_NO,
        KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
        KC_NO,      KC_RSFT,    KC_RCTL,    KC_LALT,    KC_RGUI,    KC_NO,
        KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
                                            KC_NO,
        // 側面スイッチ
        KC_NO,      KC_NO,                
        // 十字キーorジョイスティック                                   // ジョイスティックスイッチ
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,                KC_TRNS,      
        // 追加スイッチ                                               // トグルスイッチ
        KC_TRNS,    KC_TRNS,                                        KC_TRNS
    ),
    [FUN] = LAYOUT(
        // 左手 
        // 天面スイッチ
        KC_NO,      KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_NO,      KC_F12,     KC_F7,      KC_F8,      KC_F9,      KC_PSCR,
        KC_NO,      KC_F11,     KC_F4,      KC_F5,      KC_F6,      KC_SCRL, 
                    KC_F10,     KC_F1,      KC_F2,      KC_F3,      KC_PAUS,
                                KC_NO,
        // 側面スイッチ
        KC_SPC,     KC_TAB,                
        // 十字キーorジョイスティック                                   // ジョイスティックスイッチ
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,                KC_TRNS,      
        // 追加スイッチ                                               // トグルスイッチ
        KC_TRNS,    KC_TRNS,                                        KC_TRNS,
        // 右手
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_NO,
        KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
        KC_NO,      KC_RSFT,    KC_RCTL,    KC_LALT,    KC_RGUI,    KC_NO,
        KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
                                            KC_NO,
        // 側面スイッチ
        KC_NO,      KC_NO,                
        // 十字キーorジョイスティック                                   // ジョイスティックスイッチ
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,                KC_TRNS,      
        // 追加スイッチ                                               // トグルスイッチ
        KC_TRNS,    KC_TRNS,                                        KC_TRNS
    ),
    // TODO find some way to keep my precious homerow mods here?
    [MOUSE] = LAYOUT(
        // 左手 
        // 天面スイッチ
        XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, R_CHMOD,
        XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, CPI_I,
        AUTO_MOUSE, XXXXXXX, XXXXXXX, R_ANG_D, R_INV,   R_ANG_I,
                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, CPI_D,
                             INV_SCRL,
        // 側面スイッチ
        KC_NO,      KC_NO,                
        // 十字キーorジョイスティック                                   // ジョイスティックスイッチ
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,                KC_TRNS,      
        // 追加スイッチ                                               // トグルスイッチ
        KC_TRNS,    KC_TRNS,                                        KC_TRNS,
        // 右手
        _______,    _______,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        MOD_SCRL,   KC_MS_BTN1, KC_MS_BTN2, KC_MS_BTN3, MOD_SCRL, XXXXXXX,
        XXXXXXX,    KC_RSFT,    KC_RCTL, KC_LALT, KC_RGUI,
                                   XXXXXXX,
        XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
        XXXXXXX, XXXXXXX,                            XXXXXXX
    ),
    [BALL_SETTINGS] = LAYOUT(
        XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                             XXXXXXX,
        XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
        XXXXXXX, XXXXXXX,                           XXXXXXX,
        R_CHMOD, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, CPI_I,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        R_ANG_D, R_INV,   R_ANG_I, XXXXXXX, XXXXXXX, AUTO_MOUSE,
        XXXXXXX, CPI_D,   XXXXXXX, XXXXXXX, XXXXXXX,
                                   INV_SCRL,
        XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
        XXXXXXX, XXXXXXX,                            XXXXXXX
    ),
    [LIGHT_SETTINGS] = LAYOUT (
        XXXXXXX, XXXXXXX, XXXXXXX, RGB_MOD, RGB_MOD, _______,
        XXXXXXX, RGB_SPI, RGB_VAI, RGB_SAI, RGB_HUI, RGB_TOG,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                 RGB_SPD, RGB_VAD, RGB_SAD, RGB_HUD, XXXXXXX,
                          XXXXXXX,
        RGB_MOD, RGB_MOD,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
        XXXXXXX, XXXXXXX,                            XXXXXXX,
        _______, RGB_MOD, RGB_MOD, XXXXXXX, XXXXXXX, XXXXXXX,
        RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD,
                                   XXXXXXX,
        RGB_MOD, RGB_MOD,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
        XXXXXXX, XXXXXXX,                            XXXXXXX
    )
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [BASE] =   { 
        ENCODER_CCW_CW(KC_ESC, KC_TAB),
        ENCODER_CCW_CW(REDO, UNDO),
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D),
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D),
        ENCODER_CCW_CW(KC_DEL, KC_BSPC),
        ENCODER_CCW_CW(KC_UP, KC_DOWN),
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D),
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D)
    },
    [GAME] =   {
        ENCODER_CCW_CW(KC_ESC, KC_TAB),
        ENCODER_CCW_CW(REDO, UNDO),
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D),
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D),
        ENCODER_CCW_CW(KC_DEL, KC_BSPC),
        ENCODER_CCW_CW(KC_UP, KC_DOWN),
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D),
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D)
    },
    [MEDIA] =   { 
        ENCODER_CCW_CW(KC_ESC, KC_TAB),
        ENCODER_CCW_CW(REDO, UNDO),
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D),
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D),
        ENCODER_CCW_CW(KC_DEL, KC_BSPC),
        ENCODER_CCW_CW(KC_UP, KC_DOWN),
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D),
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D)
    },
    [NAV] =   { 
        ENCODER_CCW_CW(KC_ESC, KC_TAB),
        ENCODER_CCW_CW(REDO, UNDO),
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D),
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D),
        ENCODER_CCW_CW(KC_DEL, KC_BSPC),
        ENCODER_CCW_CW(KC_UP, KC_DOWN),
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D),
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D)
    },
    [_MOUSE] =   { 
        ENCODER_CCW_CW(KC_ESC, KC_TAB),
        ENCODER_CCW_CW(REDO, UNDO),
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D),
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D),
        ENCODER_CCW_CW(KC_DEL, KC_BSPC),
        ENCODER_CCW_CW(KC_UP, KC_DOWN),
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D),
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D)
    },
    [SYM] =   { 
        ENCODER_CCW_CW(KC_ESC, KC_TAB),
        ENCODER_CCW_CW(REDO, UNDO),
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D),
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D),
        ENCODER_CCW_CW(KC_DEL, KC_BSPC),
        ENCODER_CCW_CW(KC_UP, KC_DOWN),
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D),
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D)
    },
    [NUM] =   { 
        ENCODER_CCW_CW(KC_ESC, KC_TAB),
        ENCODER_CCW_CW(REDO, UNDO),
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D),
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D),
        ENCODER_CCW_CW(KC_DEL, KC_BSPC),
        ENCODER_CCW_CW(KC_UP, KC_DOWN),
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D),
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D)
    },
    [FUN] =   { 
        ENCODER_CCW_CW(KC_ESC, KC_TAB),
        ENCODER_CCW_CW(REDO, UNDO),
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D),
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D),
        ENCODER_CCW_CW(KC_DEL, KC_BSPC),
        ENCODER_CCW_CW(KC_UP, KC_DOWN),
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D),
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D)
    },
    [MOUSE] =   { 
        ENCODER_CCW_CW(KC_ESC, KC_TAB),
        ENCODER_CCW_CW(REDO, UNDO),
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D),
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D),
        ENCODER_CCW_CW(KC_DEL, KC_BSPC),
        ENCODER_CCW_CW(KC_UP, KC_DOWN),
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D),
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D)
    },
    [LIGHT_SETTINGS] =   { 
        ENCODER_CCW_CW(RGB_SPI, RGB_SPD), 
        ENCODER_CCW_CW(RGB_VAI, RGB_VAD), 
        ENCODER_CCW_CW(RGB_SAI, RGB_SAD), 
        ENCODER_CCW_CW(RGB_HUI, RGB_HUD),
        ENCODER_CCW_CW(RGB_SPI, RGB_SPD), 
        ENCODER_CCW_CW(RGB_VAI, RGB_VAD), 
        ENCODER_CCW_CW(RGB_SAI, RGB_SAD), 
        ENCODER_CCW_CW(RGB_HUI, RGB_HUD)
    },
};

// 初期化関係
void matrix_init_user(void) {
    matrix_init_addedjoystick();
}

// for advanced rgb
// void keyboard_post_init_user(void) {
//     keyboard_post_init_rgblayers();
// }

// キースキャン関係
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    process_record_addedkeycodes(keycode, record);
    return true;
}

const uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case LT(MEDIA, KC_ESC):
        case LT(NAV, KC_SPC):
        case LT(MOUSE, KC_TAB):
        case LT(SYM, KC_ENT):
        case LT(NUM, KC_BSPC):
        case LT(FUN, KC_DEL):
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

void matrix_scan_user(void) {
    matrix_scan_addedjoystick();
}
