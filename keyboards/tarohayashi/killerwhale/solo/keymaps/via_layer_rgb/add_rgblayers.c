// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "add_rgblayers.h"
#include "quantum.h"

// レイヤーごとの発光場所、発光色の設定
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    { 3, 1, HSV_RED}, { 5, 1, HSV_RED}, {14, 1, HSV_RED}                                );
const rgblight_segment_t PROGMEM my_numlock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    { 3, 1, HSV_CYAN}, { 5, 1, HSV_CYAN}, {14, 1, HSV_CYAN}                             );
const rgblight_segment_t PROGMEM my_scrolllock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    { 3, 1, HSV_BLUE}, { 5, 1, HSV_ORANGE}, {14, 1, HSV_ORANGE}                         );
const rgblight_segment_t PROGMEM l_lower_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {10, 3, HSV_YELLOW},{18, 1, HSV_YELLOW}                                             );
const rgblight_segment_t PROGMEM l_upper_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {9, 4, HSV_BLUE}                                                                    );
const rgblight_segment_t PROGMEM r_lower_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {10, 3, HSV_YELLOW},{18, 1, HSV_YELLOW}                                             );
const rgblight_segment_t PROGMEM r_upper_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {9, 4, HSV_BLUE}                                                                    );
const rgblight_segment_t PROGMEM util_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {21, 3, HSV_PINK}                                                                   );
const rgblight_segment_t PROGMEM mouse_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {21, 3, HSV_CORAL}                                                                  );
const rgblight_segment_t PROGMEM ball_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    { 3, 2, HSV_BLACK}, { 5, 1, HSV_YELLOW}, { 6, 1, HSV_BLACK}, { 7, 1, HSV_AZURE},
    { 8, 1, HSV_BLACK}, { 9 ,1, HSV_AZURE},  {10, 1, HSV_BLUE},  {11, 1, HSV_AZURE},
    {12, 2, HSV_BLACK}, {14, 1, HSV_GREEN},  {15, 4, HSV_BLACK},{19, 1, HSV_AZURE},
    {20, 1, HSV_BLACK},{21, 1, HSV_YELLOW}, {22, 1, HSV_YELLOW}, {23, 10, HSV_BLACK}    );
const rgblight_segment_t PROGMEM light_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    { 3, 2, HSV_BLACK}, { 6, 2, HSV_BLACK}, {16, 8, HSV_BLACK}                          );

// レイヤーごとの発光方法の指定
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_capslock_layer,
    my_numlock_layer,
    my_scrolllock_layer,
    l_lower_layer,
    r_upper_layer,
    l_lower_layer,
    r_upper_layer,
    util_layer,
    mouse_layer,
    ball_layer,
    light_layer
);

void keyboard_post_init_rgblayers(void) {
    rgblight_layers = my_rgb_layers;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    rgblight_set_layer_state(1, led_state.num_lock);
    rgblight_set_layer_state(2, led_state.scroll_lock);
    return true;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, 0));
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(3, layer_state_cmp(state, 1));
    rgblight_set_layer_state(4, layer_state_cmp(state, 2));
    rgblight_set_layer_state(5, layer_state_cmp(state, 4));
    rgblight_set_layer_state(6, layer_state_cmp(state, 5));
    rgblight_set_layer_state(7, layer_state_cmp(state, 6));
    rgblight_set_layer_state(8, layer_state_cmp(state, 7));
    rgblight_set_layer_state(9, layer_state_cmp(state, 8));
    rgblight_set_layer_state(10, layer_state_cmp(state, 9));
    return state;
}