// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "add_joystick.h"
#include "quantum.h"
#include "analog.h"

// ファイル内のみ変数
int16_t gp27_newt;
int16_t gp28_newt;
bool joystick_attached;
uint16_t wait_timer;


keyevent_t joystick_left = {
    .type = KEY_EVENT,
    .key = (keypos_t){.row = 2, .col = 6},
    .pressed = false
};

keyevent_t joystick_right = {
    .type = KEY_EVENT,
    .key = (keypos_t){.row = 4, .col = 6},
    .pressed = false
};

keyevent_t joystick_up = {
    .type = KEY_EVENT,
    .key = (keypos_t){.row = 3, .col = 6},
    .pressed = false
};

keyevent_t joystick_down = {
    .type = KEY_EVENT,
    .key = (keypos_t){.row = 1, .col = 6},
    .pressed = false
};

void matrix_init_addedjoystick(void) {
    gp27_newt = analogReadPin(GP27);
    gp28_newt = analogReadPin(GP28);
    if(gp27_newt < NO_STICK_VAL ||  gp28_newt < NO_STICK_VAL ){
        joystick_attached = false;
    }else{
        joystick_attached = true;
    }
}

void matrix_scan_addedjoystick(void) {
    if(joystick_attached){
        int16_t gp27_val = analogReadPin(GP27);
        int16_t gp28_val = analogReadPin(GP28);
        float x_val = ( (float)gp27_val - (float)gp27_newt  ) * (float)511 / ((float)1023 - (float)gp27_newt);
        float y_val = ( (float)gp28_val - (float)gp28_newt ) * (float)511 / ((float)1023 - (float)gp28_newt);
        if(x_val < -511){
            x_val = -511;
        }
        if(y_val < -511){
            y_val = -511;
        }

        if(x_val > (float)STICK_OFFSET && timer_elapsed(wait_timer) > STICK_WAIT){
            joystick_left.pressed = true;
            joystick_left.time = (timer_read() | 1);
            action_exec(joystick_left);
            wait_timer = timer_read();
        }else if(x_val < (float)-1 * (float)STICK_OFFSET && timer_elapsed(wait_timer) > STICK_WAIT){
            joystick_right.pressed = true;
            joystick_right.time = (timer_read() | 1);
            action_exec(joystick_right);
            wait_timer = timer_read();
        }

        if(y_val > (float)STICK_OFFSET && timer_elapsed(wait_timer) > STICK_WAIT){
            joystick_up.pressed = true;
            joystick_up.time = (timer_read() | 1);
            action_exec(joystick_up);
            wait_timer = timer_read();
        }else if(y_val < (float)-1 * (float)STICK_OFFSET && timer_elapsed(wait_timer) > STICK_WAIT){
            joystick_down.pressed = true;
            joystick_down.time = (timer_read() | 1);
            action_exec(joystick_down);
            wait_timer = timer_read();
        }

        if (joystick_left.pressed){
            joystick_left.pressed = false;
            joystick_left.time = (timer_read() | 1);
            action_exec(joystick_left);
        }

        if (joystick_right.pressed){
            joystick_right.pressed = false;
            joystick_right.time = (timer_read() | 1);
            action_exec(joystick_right);
        }

        if (joystick_up.pressed){
            joystick_up.pressed = false;
            joystick_up.time = (timer_read() | 1);
            action_exec(joystick_up);
        }

        if (joystick_down.pressed){
            joystick_down.pressed = false;
            joystick_down.time = (timer_read() | 1);
            action_exec(joystick_down);
        }
    }
}