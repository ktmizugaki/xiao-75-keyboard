/*
 * Copyright (C) 2022 Kawashima Teruaki
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include <stdint.h>
#include <kbdconfig.h>
#include "mzkbd_keycode.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file
 * Scans key matrix.
 */

/** holds infrormation of changed key. */
typedef struct matrix_change {
    uint8_t column;     /**< column of key. */
    uint8_t row;        /**< row of key. */
    uint8_t state;      /**< 0 indicates key is released, 1 indicates key is pressed. */
    kbdkey_t keycode;   /**< value of key. */
} matrix_change_t;

/** initializes internal state of key matrix and io pins. */
extern void matrix_init(void);
/** scans key matrix and store changes from last scan. */
extern void matrix_task(void);
#if USE_ANALOG
/** test and store if analog device is preset. */
extern void matrix_check_analog_presence(void);
#endif

/** returns key changes found in last matrix_task(). */
extern const matrix_change_t* matrix_get_changes(int *num_change);

/** returns state of key at column and row.
 * 0 indicates key is released, 1 indicates key is pressed.
 */
extern int matrix_get(int column, int row);
#if USE_ANALOG
/** returns last analog value of analog_id at last matrix_task(). */
extern int matrix_get_analog(int analog_id);
#endif

#ifdef __cplusplus
}
#endif
