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
#include "mzkbd_keycode.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file
 * This header contains declarations of key map functions.
 * User must implement these functions.
 */

/** user provided function taht returns keycode from column and row */
extern kbdkey_t keymap_get_keycode(int column, int row);

#ifdef __cplusplus
}
#endif
