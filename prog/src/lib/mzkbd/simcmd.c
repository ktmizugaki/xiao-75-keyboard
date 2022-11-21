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

#include <stdint.h>
#include "kbdconfig.h"
#include "simcmd.h"
#include "mzkbd_keycode.h"
#include "matrix.h"

#if USE_SIMCMD

extern void enter_bootloader(void);

static void simcmd_handle_key(kbdkey_t key)
{
    switch (key) {
    case CMD_BLR:
        enter_bootloader();
        return;
    }
}

void simcmd_init(void)
{
}

void simcmd_task(void)
{
    int i, num_change;
    const matrix_change_t *changes;
    changes = matrix_get_changes(&num_change);
    for (i = 0; i < num_change; i++) {
        kbdkey_t keycode = changes[i].keycode;
        if (IS_SIMCMD(keycode)) {
            if (changes[i].state) {
                simcmd_handle_key(keycode);
            }
        }
    }
}

#endif /* USE_SIMCMD */
