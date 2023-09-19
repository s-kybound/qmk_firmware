// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "add_encoders.h"
#include "quantum.h"

keyevent_t encoder1_ccw = {
    .type = ENCODER_CCW_EVENT,
    .key = (keypos_t){.row = 7, .col = 0},
    .pressed = false
};

keyevent_t encoder1_cw = {
    .type = ENCODER_CW_EVENT,
    .key = (keypos_t){.row = 7, .col = 1},
    .pressed = false
};

keyevent_t encoder2_ccw = {
    .type = ENCODER_CCW_EVENT,
    .key = (keypos_t){.row = 8, .col = 0},
    .pressed = false
};

keyevent_t encoder2_cw = {
    .type = ENCODER_CW_EVENT,
    .key = (keypos_t){.row = 8, .col = 1},
    .pressed = false
};

keyevent_t encoder3_ccw = {
    .type = ENCODER_CCW_EVENT,
    .key = (keypos_t){.row = 9, .col = 0},
    .pressed = false
};

keyevent_t encoder3_cw = {
    .type = ENCODER_CW_EVENT,
    .key = (keypos_t){.row = 9, .col = 1},
    .pressed = false
};

keyevent_t encoder4_ccw = {
    .type = ENCODER_CCW_EVENT,
    .key = (keypos_t){.row = 10, .col = 0},
    .pressed = false
};

keyevent_t encoder4_cw = {
    .type = ENCODER_CW_EVENT,
    .key = (keypos_t){.row = 10, .col = 1},
    .pressed = false
};


keyevent_t encoder5_ccw = {
    .type = ENCODER_CCW_EVENT,
    .key = (keypos_t){.row = 18, .col = 0},
    .pressed = false
};

keyevent_t encoder5_cw = {
    .type = ENCODER_CW_EVENT,
    .key = (keypos_t){.row = 18, .col = 1},
    .pressed = false
};

keyevent_t encoder6_ccw = {
    .type = ENCODER_CCW_EVENT,
    .key = (keypos_t){.row = 19, .col = 0},
    .pressed = false
};

keyevent_t encoder6_cw = {
    .type = ENCODER_CW_EVENT,
    .key = (keypos_t){.row = 19, .col = 1},
    .pressed = false
};

keyevent_t encoder7_ccw = {
    .type = ENCODER_CCW_EVENT,
    .key = (keypos_t){.row = 20, .col = 0},
    .pressed = false
};

keyevent_t encoder7_cw = {
    .type = ENCODER_CW_EVENT,
    .key = (keypos_t){.row = 20, .col = 1},
    .pressed = false
};

keyevent_t encoder8_ccw = {
    .type = ENCODER_CCW_EVENT,
    .key = (keypos_t){.row = 21, .col = 0},
    .pressed = false
};

keyevent_t encoder8_cw = {
    .type = ENCODER_CW_EVENT,
    .key = (keypos_t){.row = 21, .col = 1},
    .pressed = false
};

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
    }else if (index == 3) {
        if (clockwise) {
            encoder4_cw.pressed = true;
            encoder4_cw.time = (timer_read() | 1);
            action_exec(encoder4_cw);
        } else {
            encoder4_ccw.pressed = true;
            encoder4_ccw.time = (timer_read() | 1);
            action_exec(encoder4_ccw);
        }
    }else if (index == 4) {
        if (clockwise) {
            encoder5_cw.pressed = true;
            encoder5_cw.time = (timer_read() | 1);
            action_exec(encoder5_cw);
        } else {
            encoder5_ccw.pressed = true;
            encoder5_ccw.time = (timer_read() | 1);
            action_exec(encoder5_ccw);
        }
    }else if (index == 5) {
        if (clockwise) {
            encoder6_cw.pressed = true;
            encoder6_cw.time = (timer_read() | 1);
            action_exec(encoder6_cw);
        } else {
            encoder6_ccw.pressed = true;
            encoder6_ccw.time = (timer_read() | 1);
            action_exec(encoder6_ccw);
        }
    }else if (index == 6) {
        if (clockwise) {
            encoder7_cw.pressed = true;
            encoder7_cw.time = (timer_read() | 1);
            action_exec(encoder7_cw);
        } else {
            encoder7_ccw.pressed = true;
            encoder7_ccw.time = (timer_read() | 1);
            action_exec(encoder7_ccw);
        }
    }else if (index == 7) {
        if (clockwise) {
            encoder8_cw.pressed = true;
            encoder8_cw.time = (timer_read() | 1);
            action_exec(encoder8_cw);
        } else {
            encoder8_ccw.pressed = true;
            encoder8_ccw.time = (timer_read() | 1);
            action_exec(encoder8_ccw);
        }
    }
    return false;
}


void matrix_scan_addedencoders(void){
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
    if (encoder4_ccw.pressed){
        encoder4_ccw.pressed = false;
        encoder4_ccw.time = (timer_read() | 1);
        action_exec(encoder4_ccw);
    }
    if (encoder4_cw.pressed){
        encoder4_cw.pressed = false;
        encoder4_cw.time = (timer_read() | 1);
        action_exec(encoder4_cw);
    }
    if (encoder5_ccw.pressed){
        encoder5_ccw.pressed = false;
        encoder5_ccw.time = (timer_read() | 1);
        action_exec(encoder5_ccw);
    }
    if (encoder5_cw.pressed){
        encoder5_cw.pressed = false;
        encoder5_cw.time = (timer_read() | 1);
        action_exec(encoder5_cw);
    }
    if (encoder6_ccw.pressed){
        encoder6_ccw.pressed = false;
        encoder6_ccw.time = (timer_read() | 1);
        action_exec(encoder6_ccw);
    }
    if (encoder6_cw.pressed){
        encoder6_cw.pressed = false;
        encoder6_cw.time = (timer_read() | 1);
        action_exec(encoder6_cw);
    }
    if (encoder7_ccw.pressed){
        encoder7_ccw.pressed = false;
        encoder7_ccw.time = (timer_read() | 1);
        action_exec(encoder7_ccw);
    }
    if (encoder7_cw.pressed){
        encoder7_cw.pressed = false;
        encoder7_cw.time = (timer_read() | 1);
        action_exec(encoder7_cw);
    }
    if (encoder8_ccw.pressed){
        encoder8_ccw.pressed = false;
        encoder8_ccw.time = (timer_read() | 1);
        action_exec(encoder8_ccw);
    }
    if (encoder8_cw.pressed){
        encoder8_cw.pressed = false;
        encoder8_cw.time = (timer_read() | 1);
        action_exec(encoder8_cw);
    }
}