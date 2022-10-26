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
#include <kbdconfig.h>
#include "mediakey.h"
#include "matrix.h"
#include "keycode.h"
#include "report.h"
#include "hid.h"

#if USE_MEDIAKEY

static uint16_t s_current_mediakey;

static int mediakey_press_key(uint16_t key)
{
    if (s_current_mediakey == key) {
        return 0;
    }
    s_current_mediakey = key;
    return 1;
}

static int mediakey_release_key(uint16_t key)
{
    if (s_current_mediakey != key) {
        return 0;
    }
    s_current_mediakey = 0;
    return 1;
}

void mediakey_init(void)
{
    s_current_mediakey = 0;
}

void mediakey_task(void)
{
    int update = 0;
    int i, num_change;
    const matrix_change_t *changes;
    changes = matrix_get_changes(&num_change);
    for (i = 0; i < num_change; i++) {
        kbdkey_t keycode = changes[i].keycode;
        if (IS_CONSUMER(keycode)) {
            uint16_t mediakey = KEYCODE2CONSUMER((uint8_t)keycode);
            if (changes[i].state) {
                update |= mediakey_press_key(mediakey);
            } else {
                update |= mediakey_release_key(mediakey);
            }
        }
    }
    if (update) {
        mediakey_report(s_current_mediakey);
    }
}
#endif /* USE_MEDIAKEY */
