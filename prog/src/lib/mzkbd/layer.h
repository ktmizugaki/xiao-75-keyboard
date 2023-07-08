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

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file
 * Handle layer keys.
 * USE_LAYER must be set to use layers.
 */

#if USE_LAYER

/** maximum number of layers */
#define LAYER_MAX   32

typedef uint8_t layer_t;
typedef uint32_t layer_state_t;

/** initializes internal layer state. */
extern void layer_init(void);
/** handles layer key.
 * call this function after matrix_task().
 */
extern void layer_task(void);

/** set layer state. */
extern void layer_state_set(layer_state_t layer_state);
/** get layer state. */
extern layer_state_t layer_state(void);
/** obtain active layers and check updates.
 * return 1 if layer was updated, return 0 otherwise. */
extern int layer_state_obtain_check(layer_state_t *layer_state);

/** activate specified layer and deactivate others. */
extern void layer_set(layer_t layer);
/** activate specified layer. */
extern void layer_on(layer_t layer);
/** deactivate specified layer. */
extern void layer_off(layer_t layer);
/** toggle specified layer. */
extern void layer_toggle(layer_t layer);
/** return 1 if specified layer is active. */
extern int layer_is_on(layer_t layer);

#endif /* USE_LAYER */

#ifdef __cplusplus
}
#endif
