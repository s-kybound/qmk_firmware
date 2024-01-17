// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define POINTING_DEVICE_RIGHT
#define RGBLIGHT_LAYERS
#define RGBLIGHT_MAX_LAYERS 12

/* Configuration for home row mods */
// Configure the global tapping term (default: 200ms)
#define TAPPING_TERM 200

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define QUICK_TAP_TERM 0

// Per key quick tap
#define TAPPING_TERM_PER_KEY

// Per key quick tap
#define QUICK_TAP_TERM_PER_KEY

#ifdef USE_ACHORDION
#define PERMISSIVE_HOLD
#else
#undef PERMISSIVE_HOLD
#endif
#undef HOLD_ON_OTHER_KEY_PRESS