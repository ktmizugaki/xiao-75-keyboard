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

#ifdef __cplusplus
extern "C" {
#endif

enum gpio_mode {
    GPIO_DISABLE,
    GPIO_OUTPUT,
    GPIO_INPUT,
    GPIO_INPUT_PULLUP,
    GPIO_INPUT_PULLDOWN,
};

enum adc_res {
    ADC_RES_12BIT = 1,
    ADC_RES_10BIT,
    ADC_RES_8BIT,
};

extern void port_configure(uint8_t pin, uint8_t portfunc);
extern void gpio_configure(uint8_t pin, enum gpio_mode mode);
extern void gpio_set(uint8_t pin, int value);
extern int gpio_get(uint8_t pin);

extern void adc_configure(enum adc_res resolution);
extern uint16_t adc_get(uint8_t pin);

#ifdef __cplusplus
}
#endif
