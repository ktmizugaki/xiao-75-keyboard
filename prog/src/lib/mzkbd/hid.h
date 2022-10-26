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

#define KEYCODES_SIZE   6

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file
 * This header contains declarations of usb hid functions.
 * User must implement these functions.
 */

/** user provided function to initialize hid module. */
extern void hid_init(void);
/** user provided function to prepare for report.
 * this function will be called after matrix_task. */
extern void hid_task(void);

/** user provided function to send keyboard report. */
extern void keyboard_report(uint8_t modifier, uint8_t keycode[KEYCODES_SIZE]);

/** user provided function to send mouse report. */
extern void mouse_report(uint8_t buttons,
    int8_t x, int8_t y, int8_t vertical, int8_t horizontal);

#if USE_MEDIAKEY
/** user provided function to send media key report.
 * required only if USE_MEDIAKEY is 1. */
extern void mediakey_report(uint16_t mediakey);
#endif /* USE_MEDIAKEY */

#ifdef __cplusplus
}
#endif
