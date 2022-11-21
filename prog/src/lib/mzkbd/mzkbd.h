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

#include "kbdconfig.h"
#include "keycode.h"
#include "mzkbd_keycode.h"
#include "hid.h"
#include "matrix.h"
#include "keyboard.h"
#include "mouse.h"
#include "mediakey.h"
#include "layer.h"
#include "simcmd.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file
 * Include headers for mzkbd.
 */

static inline void mzkbd_init(void) {
    hid_init();
    matrix_init();
    keyboard_init();
#if USE_MOUSE
    mouse_init();
#endif
#if USE_MEDIAKEY
    mediakey_init();
#endif
#if USE_LAYER
    layer_init();
#endif
#if USE_SIMCMD
    simcmd_init();
#endif
}

static inline void mzkbd_task(void) {
    matrix_task();
    hid_task();
    keyboard_task();
#if USE_MOUSE
    mouse_task();
#endif
#if USE_MEDIAKEY
    mediakey_task();
#endif
#if USE_LAYER
    layer_task();
#endif
#if USE_SIMCMD
    simcmd_task();
#endif
}


#ifdef __cplusplus
}
#endif
