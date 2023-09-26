// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include "quantum.h"

// ジョイスティックの定数
#define STICK_OFFSET 220
#define STICK_WAIT 50
#define NO_STICK_VAL 100

void matrix_init_addedjoystick(void);
void matrix_scan_addedjoystick(void);