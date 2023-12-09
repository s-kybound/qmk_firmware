// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "add_trackball.h"
#include "math.h"
#include "split_util.h"
#include "quantum.h"

// ファイル外参照変数
ballconfig_t ballconfig;
bool scrolling;
uint16_t cpi_array[] = CPI_OPTIONS;
uint16_t angle_array[] = ANGLE_OPTIONS;
// ファイル内のみ変数
float scroll_accumulated_l_h;
float scroll_accumulated_l_v;
float scroll_accumulated_r_h;
float scroll_accumulated_r_v;

// eeprom初期化
void eeconfig_init_user(void) {
    ballconfig.cpi_idx = CPI_DEFAULT;
    ballconfig.left_angle_idx = ANGLE_DEFAULT_LEFT;
    ballconfig.right_angle_idx = ANGLE_DEFAULT_RIGHT;
    ballconfig.left_inv = false;
    ballconfig.left_scmode = true;
    ballconfig.right_inv = false;
    ballconfig.right_scmode = false;
    ballconfig.inv_sc = false;
    ballconfig.auto_mouse = true;
    eeconfig_update_user(ballconfig.raw);
}

// トラックボール初期化
void pointing_device_init_user(void) {
    scrolling = false;
    scroll_accumulated_l_h = 0;
    scroll_accumulated_l_v = 0;
    scroll_accumulated_r_h = 0;
    scroll_accumulated_r_v = 0;
    ballconfig.raw = eeconfig_read_user();
    pointing_device_set_cpi_on_side(true, cpi_array[ballconfig.cpi_idx]);
    pointing_device_set_cpi_on_side(false, cpi_array[ballconfig.cpi_idx]);
    set_auto_mouse_enable(ballconfig.auto_mouse);
}

report_mouse_t pointing_device_task_combined_user(report_mouse_t left_report, report_mouse_t right_report) {

    double l_rad = angle_array[ballconfig.left_angle_idx] * (M_PI / 180) * -1;
    int8_t l_x_rev =  + left_report.x * cos(l_rad) - left_report.y * sin(l_rad);
    int8_t l_y_rev =  + left_report.x * sin(l_rad) + left_report.y * cos(l_rad);
    if(ballconfig.left_inv){
            l_x_rev = -1 * l_x_rev;
    }
    // 左手
    if(scrolling || ballconfig.left_scmode){
        if (abs(l_x_rev) > abs(l_y_rev)) {
            l_y_rev = 0;
        } else {
            l_x_rev = 0;
        }
        left_report.h = l_x_rev;
        left_report.v = l_y_rev;
        if(!ballconfig.inv_sc ){
            left_report.h = -1 * left_report.h;
            left_report.v = -1 * left_report.v;
        }
        scroll_accumulated_l_h += (float)left_report.h / SCROLL_DIVISOR;
        scroll_accumulated_l_v += (float)left_report.v / SCROLL_DIVISOR;
        left_report.h = (int8_t)scroll_accumulated_l_h;
        left_report.v = (int8_t)scroll_accumulated_l_v;
        scroll_accumulated_l_h -= (int8_t)scroll_accumulated_l_h;
        scroll_accumulated_l_v -= (int8_t)scroll_accumulated_l_v;
        left_report.x = 0;
        left_report.y = 0;
    }else{
        left_report.x = -1 * l_x_rev;
        left_report.y = l_y_rev;
    }

    // 右手
    double r_rad = angle_array[ballconfig.right_angle_idx] * (M_PI / 180) * -1;
    int8_t r_x_rev =  + right_report.x * cos(r_rad) - right_report.y * sin(r_rad);
    int8_t r_y_rev =  + right_report.x * sin(r_rad) + right_report.y * cos(r_rad);
    if(ballconfig.right_inv){
            r_x_rev = -1 * r_x_rev;
    }
    if(scrolling || ballconfig.right_scmode){
        if (abs(r_x_rev) > abs(r_y_rev)) {
            r_y_rev = 0;
        } else {
            r_x_rev = 0;
        }
        right_report.h = r_x_rev;
        right_report.v = r_y_rev;
        if(!ballconfig.inv_sc ){
            right_report.h = -1 * right_report.h;
            right_report.v = -1 * right_report.v;
        }
        scroll_accumulated_r_h += (float)right_report.h / SCROLL_DIVISOR;
        scroll_accumulated_r_v += (float)right_report.v / SCROLL_DIVISOR;
        right_report.h = (int8_t)scroll_accumulated_r_h;
        right_report.v = (int8_t)scroll_accumulated_r_v;
        scroll_accumulated_r_h -= (int8_t)scroll_accumulated_r_h;
        scroll_accumulated_r_v -= (int8_t)scroll_accumulated_r_v;
        right_report.x = 0;
        right_report.y = 0;
    }else{
        right_report.x = -1 * r_x_rev;
        right_report.y = r_y_rev;
    }

    return pointing_device_combine_reports(left_report, right_report);
}
