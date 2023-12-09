// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "add_joystick.h"
#include "quantum.h"
#include "analog.h"

// ファイル内のみ変数
int16_t gp27_newt;
int16_t gp28_newt;
bool joystick_attached;

keypos_t key_up;
keypos_t key_left;
keypos_t key_right;
keypos_t key_down;
bool pressed_up = false;
bool pressed_down = false;
bool pressed_left = false;
bool pressed_right = false;

void matrix_init_addedjoystick(void) {
    gp27_newt = analogReadPin(GP27);
    gp28_newt = analogReadPin(GP28);
    if(gp27_newt < NO_STICK_VAL ||  gp28_newt < NO_STICK_VAL ){
        joystick_attached = false;
    }else{
        joystick_attached = true;
    }
    key_up.row = 3;
    key_up.col = 6;
    key_left.row = 2;
    key_left.col = 6;
    key_right.row = 4;
    key_right.col = 6;
    key_down.row = 1;
    key_down.col = 6;
}

void matrix_scan_addedjoystick(void) {
    if(joystick_attached){

        int8_t layer = layer_switch_get_layer(key_up);
        int16_t keycode_up = keymap_key_to_keycode(layer, key_up);
        int16_t keycode_left = keymap_key_to_keycode(layer, key_left);
        int16_t keycode_right = keymap_key_to_keycode(layer, key_right);
        int16_t keycode_down = keymap_key_to_keycode(layer, key_down);

        if(!pressed_left && analogReadPin(GP27) - 512 > STICK_OFFSET){
            pressed_left = true;
            register_code(keycode_left);
        }else if(pressed_left && analogReadPin(GP27) - 512  < STICK_OFFSET){
            pressed_left = false;
            unregister_code(keycode_left);
        }else if(!pressed_right && analogReadPin(GP27) - 512  < -STICK_OFFSET){
            pressed_right = true;
            register_code(keycode_right);
        }else if (pressed_right && analogReadPin(GP27) - 512  > -STICK_OFFSET){
            pressed_right = false;
            unregister_code(keycode_right);
        }

        if(!pressed_up && analogReadPin(GP28) - 512  > STICK_OFFSET){
            pressed_up = true;
            register_code(keycode_up);
        }else if(pressed_up && analogReadPin(GP28) - 512  < STICK_OFFSET){
            pressed_up = false;
            unregister_code(keycode_up);
        }else if(!pressed_down && analogReadPin(GP28) - 512  < -STICK_OFFSET){
            pressed_down = true;
            register_code(keycode_down);
        }else if(pressed_down && analogReadPin(GP28) - 512  > -STICK_OFFSET){
            pressed_down = false;
            unregister_code(keycode_down);
        }
    }
}