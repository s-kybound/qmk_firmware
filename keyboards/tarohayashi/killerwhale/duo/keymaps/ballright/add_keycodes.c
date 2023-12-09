// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "add_keycodes.h"
#include "quantum.h"
#include "os_detection.h"
#include "add_oled.h"
#include "add_trackball.h"

// スクロールボタンをマウスキー扱いに
bool is_mouse_record_user(uint16_t keycode, keyrecord_t* record) {
    switch(keycode) {
        case MOD_SCRL:
            return true;
        default:
            return false;
    }
}

bool process_record_addedkeycodes(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CMD_CTL:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                }
            } else {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    unregister_code(KC_LGUI);
                } else {
                    unregister_code(KC_LCTL);
                }
            }
            return false;
            break;
        case UNDO:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_Z);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_Z);
                    unregister_code(KC_LCTL);
                }
            }
            return false;
            break;
        case REDO:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LSFT);
                    register_code(KC_LGUI);
                    tap_code(KC_Z);
                    unregister_code(KC_LGUI);
                    unregister_code(KC_LSFT);
                } else {
                    register_code(KC_LSFT);
                    register_code(KC_LCTL);
                    tap_code(KC_Z);
                    unregister_code(KC_LCTL);
                    unregister_code(KC_LSFT);
                }
            }
            return false;
            break;
        case COPY:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_C);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_C);
                    unregister_code(KC_LCTL);
                }
            }
            return false;
            break;
        case CUT:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_X);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_X);
                    unregister_code(KC_LCTL);
                }
            }
            return false;
            break;
        case PASTE:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_V);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_V);
                    unregister_code(KC_LCTL);
                }
            }
            return false;
            break;
        case SC_UP:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_PPLS);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_PPLS);
                    unregister_code(KC_LCTL);
                }
            }
            return false;
            break;
        case SC_DOWN:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_PMNS);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_PMNS);
                    unregister_code(KC_LCTL);
                }
            }
            return false;
            break;
        case SC_RESET:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_0);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_0);
                    unregister_code(KC_LCTL);
                }
            }
            return false;
            break;
        case CAPTCHA:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LSFT);
                    register_code(KC_LGUI);
                    tap_code(KC_4);
                    unregister_code(KC_LGUI);
                    unregister_code(KC_LSFT);
                } else {
                    register_code(KC_LSFT);
                    register_code(KC_LGUI);
                    tap_code(KC_S);
                    unregister_code(KC_LGUI);
                    unregister_code(KC_LSFT);
                }
            }
            return false;
            break;
        case SAVE:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_S);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_S);
                    unregister_code(KC_LCTL);
                }
            }
            return false;
            break;
        case SAVEAS:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LSFT);
                    register_code(KC_LGUI);
                    tap_code(KC_S);
                    unregister_code(KC_LGUI);
                    unregister_code(KC_LSFT);
                } else {
                    register_code(KC_LSFT);
                    register_code(KC_LCTL);
                    tap_code(KC_S);
                    unregister_code(KC_LCTL);
                    unregister_code(KC_LSFT);
                }
            }
            return false;
            break;
        case NEXTTAB:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                tap_code(KC_TAB);
                unregister_code(KC_LCTL);
            }
            return false;
            break;
        case PREVTAB:
            if (record->event.pressed) {
                register_code(KC_LSFT);
                register_code(KC_LCTL);
                tap_code(KC_TAB);
                unregister_code(KC_LCTL);
                unregister_code(KC_LSFT);
            }
            return false;
            break;
        case CLOSETAB:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_W);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_W);
                    unregister_code(KC_LCTL);
                }
            }
            return false;
            break;
        case RSTRTAB:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LSFT);
                    register_code(KC_LGUI);
                    tap_code(KC_T);
                    unregister_code(KC_LGUI);
                    unregister_code(KC_LSFT);
                } else {
                    register_code(KC_LSFT);
                    register_code(KC_LCTL);
                    tap_code(KC_T);
                    unregister_code(KC_LCTL);
                    unregister_code(KC_LSFT);
                }
            }
            return false;
            break;
        case NEXTAPP:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_TAB);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LALT);
                    tap_code(KC_TAB);
                    unregister_code(KC_LALT);
                }
            }
            return false;
            break;
        case PREVAPP:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LSFT);
                    register_code(KC_LGUI);
                    tap_code(KC_TAB);
                    unregister_code(KC_LGUI);
                    unregister_code(KC_LSFT);
                } else {
                    register_code(KC_LSFT);
                    register_code(KC_LALT);
                    tap_code(KC_TAB);
                    unregister_code(KC_LALT);
                    unregister_code(KC_LSFT);
                }
            }
            return false;
            break;
        case CPI_I:
            if (record->event.pressed) {
                ballconfig.cpi_idx = ballconfig.cpi_idx + 1;
                if(ballconfig.cpi_idx >= CPI_OPTION_SIZE){
                    ballconfig.cpi_idx = CPI_OPTION_SIZE-1;
                }
                eeconfig_update_user(ballconfig.raw);
                pointing_device_set_cpi(cpi_array[ballconfig.cpi_idx]);
            }
            return false;
            break;
        case CPI_D:
            if (record->event.pressed) {
                if(ballconfig.cpi_idx > 0){
                    ballconfig.cpi_idx = ballconfig.cpi_idx - 1;
                }
                eeconfig_update_user(ballconfig.raw);
                pointing_device_set_cpi(cpi_array[ballconfig.cpi_idx]);
            }
            return false;
            break;
        case L_ANG_I:
            if (record->event.pressed) {
                ballconfig.angle_idx = (ballconfig.angle_idx + 1) % ANGLE_OPTION_SIZE;
                eeconfig_update_user(ballconfig.raw);
            }
            return false;
            break;
        case L_ANG_D:
            if (record->event.pressed) {
                ballconfig.angle_idx = (ANGLE_OPTION_SIZE + ballconfig.angle_idx - 1) % ANGLE_OPTION_SIZE;
                eeconfig_update_user(ballconfig.raw);
            }
            return false;
            break;
        case R_ANG_I:
            if (record->event.pressed) {
                ballconfig.angle_idx = (ballconfig.angle_idx + 1) % ANGLE_OPTION_SIZE;
                eeconfig_update_user(ballconfig.raw);
            }
            return false;
            break;
        case R_ANG_D:
            if (record->event.pressed) {
                ballconfig.angle_idx = (ANGLE_OPTION_SIZE + ballconfig.angle_idx - 1) % ANGLE_OPTION_SIZE;
                eeconfig_update_user(ballconfig.raw);
            }
            return false;
            break;
        case L_INV:
            if (record->event.pressed) {
                ballconfig.inv = !ballconfig.inv;
                eeconfig_update_user(ballconfig.raw);
            }
            return false;
            break;
        case R_INV:
            if (record->event.pressed) {
                ballconfig.inv = !ballconfig.inv;
                eeconfig_update_user(ballconfig.raw);
            }
            return false;
            break;
        case L_CHMOD:
            if (record->event.pressed) {
                ballconfig.scmode = !ballconfig.scmode;
                eeconfig_update_user(ballconfig.raw);
            }
            return false;
            break;
        case R_CHMOD:
            if (record->event.pressed) {
                ballconfig.scmode = !ballconfig.scmode;
                eeconfig_update_user(ballconfig.raw);
            }
            return false;
            break;
        case INV_SCRL:
            if (record->event.pressed) {
                ballconfig.inv_sc = !ballconfig.inv_sc;
                eeconfig_update_user(ballconfig.raw);
            }
            return false;
            break;
        case MOD_SCRL:
            scrolling = record->event.pressed;
            return false;
            break;
        case AUTO_MOUSE:
            if (record->event.pressed) {
                ballconfig.auto_mouse = !ballconfig.auto_mouse;
                set_auto_mouse_enable(ballconfig.auto_mouse);
                eeconfig_update_user(ballconfig.raw);
            }
            return false;
            break;
        case OLED_MOD:
            if (record->event.pressed) {
                oled_mode = !oled_mode;
                oled_clear();
            }
            return false;
            break;
    }
    return true;
}