/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

// #define USE_MATRIX_I2C

// #define USE_I2C

/* Select hand configuration */

// #define MASTER_LEFT
// #define MASTER_RIGHT
#define EE_HANDS

#define DYNAMIC_KEYMAP_LAYER_COUNT 7

#define QUICK_TAP_TERM 0

/* define tapping term */
#define TAPPING_TERM 200

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