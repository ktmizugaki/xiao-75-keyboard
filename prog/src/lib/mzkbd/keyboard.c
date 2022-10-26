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
#include "keyboard.h"
#include "matrix.h"
#include "keycode.h"
#include "hid.h"

static uint8_t s_current_modifiers;
static uint8_t s_active_keycodes[KEYCODES_SIZE];

static int keyboard_press_key(uint8_t key)
{
    int i, empty_index = -1;
    for (i = 0; i < KEYCODES_SIZE; i++) {
        if (s_active_keycodes[i] == key) {
            return 0;
        }
        if (empty_index == -1 && s_active_keycodes[i] == 0) {
            empty_index = i;
        }
    }
    if (empty_index == -1) {
        return 0x0100;
    }
    s_active_keycodes[empty_index] = key;
    return 1;
}

static int keyboard_release_key(uint8_t key)
{
    int i;
    for (i = 0; i < KEYCODES_SIZE; i++) {
        if (s_active_keycodes[i] == key) {
            s_active_keycodes[i] = 0;
            return 1;
        }
    }
    return 0;
}

void keyboard_init(void)
{
    int i;
    s_current_modifiers = 0;
    for (i = 0; i < KEYCODES_SIZE; i++) {
        s_active_keycodes[i] = 0;
    }
}

void keyboard_task(void)
{
    int update = 0;
    int i, num_change;
    const matrix_change_t *changes;
    changes = matrix_get_changes(&num_change);
    for (i = 0; i < num_change; i++) {
        kbdkey_t keycode = changes[i].keycode;
        if (IS_KEY(keycode)) {
            if (changes[i].state) {
                update |= keyboard_press_key((uint8_t)keycode);
            } else {
                update |= keyboard_release_key((uint8_t)keycode);
            }
        } else if (IS_MOD(keycode)) {
            uint8_t old_modifiers = s_current_modifiers;
            if (changes[i].state) {
                s_current_modifiers |= MOD_BIT(keycode);
            } else {
                s_current_modifiers &= ~MOD_BIT(keycode);
            }
            update |= old_modifiers^s_current_modifiers;
        }
    }
    if (update & 0xff) {
        keyboard_report(s_current_modifiers, s_active_keycodes);
    }
}
