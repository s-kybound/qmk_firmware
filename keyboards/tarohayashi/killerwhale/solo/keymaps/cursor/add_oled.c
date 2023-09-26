// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "add_oled.h"
#include "quantum.h"
#include "config.h"
#include "add_trackball.h"
#include "analog.h"

// ファイル外参照変数
bool oled_mode;
// ファイル内のみ変数
uint8_t pre_layer;
uint8_t cur_layer;

// 初期化 左右で向きを反転
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    oled_mode = true;
    pre_layer = 0;
    cur_layer = 0;
    return rotation;
}

// OLED表示
bool oled_task_user(void) {
    
    oled_set_cursor(0, 0);
    oled_write(get_u16_str(analogReadPin(GP27), ' '), false);

    oled_set_cursor(0, 1);
    oled_write(get_u16_str(analogReadPin(GP28), ' '), false);

    return false;
}



