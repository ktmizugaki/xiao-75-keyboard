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

#include <kbdconfig.h>

#ifdef __cplusplus
extern "C" {
#endif

#if USE_MEDIAKEY

/**
 * @file
 * Handle media key changes and send report.
 * USE_MEDIAKEY must be defined to 1 to use mediakey functions.
 */

/** initializes internal media key state. */
extern void mediakey_init(void);
/** handles media key changes.
 * also sends media key report if there is any change.
 * call this function after matrix_task().
 */
extern void mediakey_task(void);

#endif /* USE_MEDIAKEY */

#ifdef __cplusplus
}
#endif
