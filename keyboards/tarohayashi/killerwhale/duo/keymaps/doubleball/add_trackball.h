// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include "quantum.h"

// トラックボールの定数
#define CPI_OPTIONS {800, 1200, 1600, 2200}
#define CPI_DEFAULT 2
#define CPI_OPTION_SIZE 4
#define ANGLE_OPTIONS { 70, 80, 90, 160, 170, 180, 250, 260, 270, 340, 350, 360}
#define ANGLE_DEFAULT_LEFT 2
#define ANGLE_DEFAULT_RIGHT 2
#define ANGLE_OPTION_SIZE 12
#define SCROLL_DIVISOR 150.0

// eeprom保存用
typedef union{
    uint32_t raw;
    struct{
        uint8_t cpi_idx         :3;
        uint8_t left_angle_idx  :5;
        uint8_t right_angle_idx :5;
        bool left_inv           :1;
        bool left_scmode        :1;
        bool right_inv          :1;
        bool right_scmode       :1;
        bool inv_sc             :1;
        bool auto_mouse         :1;
    };
} ballconfig_t;


// ファイル外参照変数
extern ballconfig_t ballconfig;
extern bool scrolling;
extern uint16_t cpi_array[];
extern uint16_t angle_array[];