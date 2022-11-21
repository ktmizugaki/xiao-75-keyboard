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
#include "kbdconfig.h"
#include "mzkbd_keycode.h"

#ifdef __cplusplus
extern "C" {
#endif

#if USE_SIMCMD

/**
 * @file
 * Handle simple command keys.
 */

#define CMD_BLR     (EXKT_SIMCMD+0x00)

/** initializes internal simcmd state. */
extern void simcmd_init(void);
/** handles simple command key.
 * call this function after matrix_task().
 */
extern void simcmd_task(void);

#endif /* USE_SIMCMD */

#ifdef __cplusplus
}
#endif
