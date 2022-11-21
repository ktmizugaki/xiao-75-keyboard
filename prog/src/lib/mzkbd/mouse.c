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

#include <stdlib.h>
#include <stdint.h>
#include "kbdconfig.h"
#include "mouse.h"
#include "matrix.h"
#include "keycode.h"
#include "hid.h"

#if defined(ANALOG_MOUSE_X) || defined(ANALOG_MOUSE_Y)
# if !USE_ANALOG
#  error USE_ANALOG must be set to use ANALOG_MOUSE_X/Y
#  undef ANALOG_MOUSE_X
#  undef ANALOG_MOUSE_Y
# endif
#endif

#if defined(ANALOG_MOUSE_X) || defined(ANALOG_MOUSE_Y)
#define ANALOG_MOUSE 1
#endif

#ifndef ANALOG_MOUSE
#define ANALOG_MOUSE 0
#endif

#ifndef MOUSE_THRES
#define MOUSE_THRES 256
#endif

#define MOUSE_INDEX(keycode)    ((keycode)-KC_MS_UP)
#define MOUSE_FLAG(keycode)     (1<<MOUSE_INDEX(keycode))
#define MOUSE_BTN_MASK  ((1<<MOUSE_INDEX(KC_MS_BTN8))-1)

static uint32_t s_last_mouse_states;
#if defined(ANALOG_MOUSE_X)
static int32_t s_acc_mouse_x;
#endif
#if defined(ANALOG_MOUSE_Y)
static int32_t s_acc_mouse_y;
#endif
#if defined(ANALOG_MOUSE_X) || defined(ANALOG_MOUSE_Y)
static int s_mouse_repeat;
#else
static const int s_mouse_repeat = 0;
#endif
static int s_wheel_repeat;

void mouse_init(void)
{
    s_last_mouse_states = 0;
#if defined(ANALOG_MOUSE_X)
    s_acc_mouse_x = 0;
#endif
#if defined(ANALOG_MOUSE_Y)
    s_acc_mouse_y = 0;
#endif
#if defined(ANALOG_MOUSE_X) || defined(ANALOG_MOUSE_Y)
    s_mouse_repeat = 0;
#endif
    s_wheel_repeat = 0;
}

static int mouse_process_key(uint8_t keycode, int state)
{
    uint32_t flag = 1<<MOUSE_INDEX(keycode);
    uint32_t prev_states = s_last_mouse_states;
    int update = 0;
    if (state) {
        s_last_mouse_states |= flag;
    } else {
        s_last_mouse_states &= ~flag;
    }
    if (IS_MOUSEKEY_BUTTON(keycode) && (prev_states^s_last_mouse_states) != 0) {
        update = 1;
    }
    return update;
}

static int mouse_process_changes(void)
{
    int update = 0;
    int i, num_change;
    const matrix_change_t *changes;
    changes = matrix_get_changes(&num_change);
    for (i = 0; i < num_change; i++) {
        kbdkey_t keycode = changes[i].keycode;
        if (IS_MOUSEKEY(keycode)) {
            update |= mouse_process_key((uint8_t)keycode, changes[i].state);
        }
    }
    return update;
}

#if ANALOG_MOUSE
static int mouse_process_raw(int val)
{
    static const int ACCEL = 1100 - MOUSE_THRES;
    if (val < -MOUSE_THRES) {
      val -= -MOUSE_THRES;
    } else if (val > MOUSE_THRES) {
      val -= MOUSE_THRES;
    } else {
      val = 0;
    }
    if (val < -ACCEL) {
      val = val*-val / (ACCEL/2) + ACCEL/2;
    } else if (val > ACCEL) {
      val = val*val / (ACCEL/2) - ACCEL/2;
    }
    return val;
}

static int mouse_process_analog(int analog_id, int repeat, int32_t *acc, int8_t *move)
{
    static const int MOUSE_DIV = 640;
    int raw, processed, abs_processed;
    raw = matrix_get_analog(analog_id);
    if (raw < 0) {
        *move = 0;
        return 0;
    }
    raw -= 2048;
    processed = mouse_process_raw(raw);
    if (processed == 0) {
        *move = 0;
        return 0;
    }
    abs_processed = abs(processed);

    if (repeat >= 10) {
        int mult = 5+(repeat-10)/70;
        if (mult > 30) {
            mult = 30;
        }
        *acc += processed * mult / 15;
    } else {
        *acc += processed / 4;
    }
    *move = *acc / MOUSE_DIV;
    if (*move != 0) {
        *acc -= *move * MOUSE_DIV;
    }
    if (abs_processed > 1024) {
        return 2;
    } else if (abs_processed >= 180) {
        return 1;
    } else {
        return 0;
    }
}
#endif /* ANALOG_MOUSE */

static int mouse_process_digital(uint8_t dec_key, uint8_t inc_key, int repeat, int8_t *move)
{
    int update = 0;
    int dir = 0;
    if (s_last_mouse_states & MOUSE_FLAG(dec_key)) {
        dir--;
    }
    if (s_last_mouse_states & MOUSE_FLAG(inc_key)) {
        dir++;
    }
    *move = dir;
    if (*move != 0) {
        if (repeat == 0) {
            update = 2;
        } else if (repeat >= 20 && (repeat%4) == 0) {
            update = 2;
        } else {
            update = 1;
        }
    }
    return update;
}

static int mouse_process_move(int8_t *mouse_x, int8_t *mouse_y)
{
    int update = 0;
#if defined(ANALOG_MOUSE_X)
    update |= mouse_process_analog(ANALOG_MOUSE_X, s_mouse_repeat, &s_acc_mouse_x, mouse_x);
#else
    *mouse_x = 0;
#endif
    if (*mouse_x == 0) {
        update |= mouse_process_digital(KC_MS_LEFT, KC_MS_RIGHT, s_mouse_repeat, mouse_x);
    }
#if defined(ANALOG_MOUSE_Y)
    update |= mouse_process_analog(ANALOG_MOUSE_Y, s_mouse_repeat, &s_acc_mouse_y, mouse_y);
#else
    *mouse_y = 0;
#endif
    if (*mouse_y == 0) {
        update |= mouse_process_digital(KC_MS_UP, KC_MS_DOWN, s_mouse_repeat, mouse_y);
    }
#if defined(ANALOG_MOUSE_X) || defined(ANALOG_MOUSE_Y)
    if (update >= 2) {
        s_mouse_repeat++;
    } else if (update == 0) {
        s_mouse_repeat = 0;
    }
#endif /* ANALOG_MOUSE_X */
    return *mouse_x != 0 || *mouse_y != 0;
}

static int mouse_process_wheel(int8_t *wheel_x, int8_t *wheel_y)
{
    int update = 0;
    *wheel_x = 0;
    if (*wheel_x == 0) {
        update |= mouse_process_digital(KC_MS_WH_LEFT, KC_MS_WH_RIGHT,
                    s_wheel_repeat, wheel_x);
    }
    *wheel_y = 0;
    if (*wheel_y == 0) {
        update |= mouse_process_digital(KC_MS_WH_DOWN, KC_MS_WH_UP,
                    s_wheel_repeat, wheel_y);
    }
    if (update >= 2) {
        s_wheel_repeat++;
    } else if (update == 0) {
        s_wheel_repeat = 0;
    }
    return *wheel_x != 0 || *wheel_y != 0;
}

void mouse_task(void)
{
    int update = 0;
    int8_t mouse_x, mouse_y, wheel_x, wheel_y;
    update |= mouse_process_changes();
    update |= mouse_process_move(&mouse_x, &mouse_y);
    update |= mouse_process_wheel(&wheel_x, &wheel_y);
    if (update) {
        uint8_t buttons = (s_last_mouse_states&MOUSE_BTN_MASK)>>MOUSE_INDEX(KC_MS_BTN1);
        mouse_report(buttons, mouse_x, mouse_y, wheel_y, wheel_x);
    }
}
