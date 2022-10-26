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

#include <stdbool.h>
#include <kbdconfig.h>
#include "src/lib/mzkbd/mzkbd.h"
#include <Arduino.h>

/* IMPORTANT: This firmware disables USB-CDC.
 * You need to double tap reset to upload new firmware once you upload this. */

#define INTERVAL_US    10000
static uint16_t next = 0;

void setup(void)
{
    mzkbd_init();
#if USE_ANALOG
    matrix_check_analog_presence();
#endif
    next = micros();
}

void loop(void)
{
    int16_t d = next - (uint16_t)micros();
    if (d <= 32) {
        next += INTERVAL_US;
        if (d > 0) {
            delayMicroseconds(d);
        }
        mzkbd_task();
    }
}
