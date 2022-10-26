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

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file
 * Handle keyboard key changes and send report.
 */

/** initializes internal keyboard state. */
extern void keyboard_init(void);
/** handles keyboard key changes.
 * also sends keyboard report if there is any change.
 * call this function after matrix_task().
 */
extern void keyboard_task(void);

#ifdef __cplusplus
}
#endif
