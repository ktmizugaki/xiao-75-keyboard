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
#include "layer.h"
#include "mzkbd_keycode.h"
#include "matrix.h"

#if USE_LAYER

#define DEFAULT_LAYER_STATE     0x00000001
#define TO_LAYER_STATE(layer)   ((layer_state_t)1<<(layer))

static layer_state_t s_layer_state;

static void layer_press_key(kbdkey_t key)
{
    layer_t layer = key&LAYER_MASK;
    switch (key&(3<<6)) {
    case LAYER_TOGGLE:
        layer_set(layer);
        return;
    case LAYER_MOMENTARY:
        layer_on(layer);
        return;
    }
}

static void layer_release_key(kbdkey_t key)
{
    layer_t layer = key&LAYER_MASK;
    switch (key&(3<<6)) {
    case LAYER_TOGGLE:
        return;
    case LAYER_MOMENTARY:
        layer_off(layer);
        return;
    }
}

void layer_init(void)
{
    s_layer_state = DEFAULT_LAYER_STATE;
}

void layer_task(void)
{
    int i, num_change;
    const matrix_change_t *changes;
    changes = matrix_get_changes(&num_change);
    for (i = 0; i < num_change; i++) {
        kbdkey_t keycode = changes[i].keycode;
        if (IS_LAYER(keycode)) {
            if (changes[i].state) {
                layer_press_key(keycode);
            } else {
                layer_release_key(keycode);
            }
        }
    }
}

void layer_state_set(layer_state_t layer_state)
{
    s_layer_state = layer_state? layer_state: DEFAULT_LAYER_STATE;
}

layer_state_t layer_state(void)
{
    return s_layer_state;
}

int layer_state_obtain_check(layer_state_t *layer_state)
{
    if (*layer_state == s_layer_state) {
        return 0;
    }
    *layer_state = s_layer_state;
    return 1;
}

void layer_set(layer_t layer)
{
    layer_state_set(TO_LAYER_STATE(layer));
}

void layer_on(layer_t layer)
{
    layer_state_set(s_layer_state|TO_LAYER_STATE(layer));
}

void layer_off(layer_t layer)
{
    layer_state_set(s_layer_state&~TO_LAYER_STATE(layer));
}

int layer_is_on(layer_t layer)
{
    return (s_layer_state&TO_LAYER_STATE(layer)) != 0;
}

#endif /* USE_LAYER */
