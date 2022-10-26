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
#include <sam.h>

#include "../mzkbd/port.h"

void port_configure(uint8_t pin, uint8_t portfunc)
{
    int group_index = pin>>5;
    pin &= 0x1f;
    if (pin & 1) {
        PORT->Group[group_index].PMUX[pin >> 1].bit.PMUXO = portfunc;
    } else {
        PORT->Group[group_index].PMUX[pin >> 1].bit.PMUXE = portfunc;
    }
    PORT->Group[group_index].PINCFG[pin].reg |= PORT_PINCFG_PMUXEN|PORT_PINCFG_DRVSTR;
}

void gpio_configure(uint8_t pin, enum gpio_mode mode)
{
    int group_index = pin>>5;
    pin &= 0x1f;
    switch(mode) {
    case GPIO_DISABLE:
        PORT->Group[group_index].PINCFG[pin].reg = 0;
        PORT->Group[group_index].DIRSET.reg = 1ul<<pin;
        break;
    case GPIO_OUTPUT:
        PORT->Group[group_index].PINCFG[pin].reg = PORT_PINCFG_INEN;
        PORT->Group[group_index].DIRSET.reg = 1ul<<pin;
        break;
    case GPIO_INPUT:
        PORT->Group[group_index].PINCFG[pin].reg = PORT_PINCFG_INEN;
        PORT->Group[group_index].DIRCLR.reg = 1ul<<pin;
        break;
    case GPIO_INPUT_PULLUP:
        PORT->Group[group_index].PINCFG[pin].reg = PORT_PINCFG_INEN|PORT_PINCFG_PULLEN;
        PORT->Group[group_index].DIRCLR.reg = 1ul<<pin;
        PORT->Group[group_index].OUTSET.reg = 1ul<<pin; /* pull up */
        break;
    case GPIO_INPUT_PULLDOWN:
        PORT->Group[group_index].PINCFG[pin].reg = PORT_PINCFG_INEN|PORT_PINCFG_PULLEN;
        PORT->Group[group_index].DIRCLR.reg = 1ul<<pin;
        PORT->Group[group_index].OUTCLR.reg = 1ul<<pin; /* pull down */
        break;
    }
}

void gpio_set(uint8_t pin, int value)
{
    int group_index = pin>>5;
    pin &= 0x1f;
    if (value) {
        PORT->Group[group_index].OUTSET.reg = (1ul<<pin);
    } else {
        PORT->Group[group_index].OUTCLR.reg = (1ul<<pin);
    }
}

int gpio_get(uint8_t pin)
{
    int group_index = pin>>5;
    pin &= 0x1f;
    if (PORT->Group[group_index].IN.reg & (1ul<<pin)) {
        return 1;
    } else {
        return 0;
    }
}

static void adc_calib(void)
{
    /* load calibration data from NVM. */
    uint32_t bias = (*((uint32_t *) ADC_FUSES_BIASCAL_ADDR) & ADC_FUSES_BIASCAL_Msk) >> ADC_FUSES_BIASCAL_Pos;
    uint32_t linearity = (*((uint32_t *) ADC_FUSES_LINEARITY_0_ADDR) & ADC_FUSES_LINEARITY_0_Msk) >> ADC_FUSES_LINEARITY_0_Pos;
    linearity |= ((*((uint32_t *) ADC_FUSES_LINEARITY_1_ADDR) & ADC_FUSES_LINEARITY_1_Msk) >> ADC_FUSES_LINEARITY_1_Pos) << 5;
    while (ADC->STATUS.bit.SYNCBUSY);
    ADC->CALIB.reg = ADC_CALIB_BIAS_CAL(bias) | ADC_CALIB_LINEARITY_CAL(linearity);
}

static void adc_setup(void)
{
    static int setup = 0;
    if (setup) {
        return;
    }
    setup = 1;

    PM->APBCMASK.reg |= PM_APBCMASK_ADC;
    GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID(GCLK_CLKCTRL_ID_ADC_Val) |
                        GCLK_CLKCTRL_GEN_GCLK0 |
                        GCLK_CLKCTRL_CLKEN;
    while (GCLK->STATUS.bit.SYNCBUSY);

    adc_calib();

    while (ADC->STATUS.bit.SYNCBUSY);
    ADC->CTRLA.bit.ENABLE = 0;
    while (ADC->STATUS.bit.SYNCBUSY);
    ADC->REFCTRL.bit.REFSEL = ADC_REFCTRL_REFSEL_INTVCC1_Val;
    ADC->AVGCTRL.reg = ADC_AVGCTRL_SAMPLENUM_1|ADC_AVGCTRL_ADJRES(0);
    ADC->SAMPCTRL.reg = ADC_SAMPCTRL_SAMPLEN(5);
    ADC->CTRLB.reg = ADC_CTRLB_PRESCALER_DIV64|ADC_CTRLB_RESSEL_12BIT;
    while (ADC->STATUS.bit.SYNCBUSY);
    ADC->WINCTRL.reg = ADC_WINCTRL_WINMODE_DISABLE;
    while (ADC->STATUS.bit.SYNCBUSY);
    ADC->INPUTCTRL.reg = ADC_INPUTCTRL_MUXNEG_GND|ADC_INPUTCTRL_GAIN_DIV2;
    while (ADC->STATUS.bit.SYNCBUSY);
}

void adc_configure(enum adc_res resolution)
{
    adc_setup();
    switch (resolution) {
    case ADC_RES_12BIT:
        ADC->CTRLB.bit.RESSEL = ADC_CTRLB_RESSEL_12BIT_Val;
        break;
    case ADC_RES_10BIT:
        ADC->CTRLB.bit.RESSEL = ADC_CTRLB_RESSEL_10BIT_Val;
        break;
    case ADC_RES_8BIT:
        ADC->CTRLB.bit.RESSEL = ADC_CTRLB_RESSEL_8BIT_Val;
        break;
    }


}

uint16_t adc_get(uint8_t pin)
{
    uint8_t channel;
    uint16_t val;
    switch (pin) {
    case PIN_PA02:
        channel = ADC_INPUTCTRL_MUXPOS_PIN0_Val;
        break;
    case PIN_PA04:
        channel = ADC_INPUTCTRL_MUXPOS_PIN4_Val;
        break;
    case PIN_PA10:
        channel = ADC_INPUTCTRL_MUXPOS_PIN18_Val;
        break;
    case PIN_PA11:
        channel = ADC_INPUTCTRL_MUXPOS_PIN19_Val;
        break;
    case PIN_PA08:
        channel = ADC_INPUTCTRL_MUXPOS_PIN16_Val;
        break;
    case PIN_PA09:
        channel = ADC_INPUTCTRL_MUXPOS_PIN17_Val;
        break;
    case PIN_PB08:
        channel = ADC_INPUTCTRL_MUXPOS_PIN2_Val;
        break;
    case PIN_PB09:
        channel = ADC_INPUTCTRL_MUXPOS_PIN3_Val;
        break;
    case PIN_PA07:
        channel = ADC_INPUTCTRL_MUXPOS_PIN7_Val;
        break;
    case PIN_PA05:
        channel = ADC_INPUTCTRL_MUXPOS_PIN5_Val;
        break;
    case PIN_PA06:
        channel = ADC_INPUTCTRL_MUXPOS_PIN6_Val;
        break;
    default:
        return 0;
    }

    gpio_configure(pin, GPIO_INPUT);
    port_configure(pin, PORT_PMUX_PMUXE_B_Val);
    while (ADC->STATUS.bit.SYNCBUSY);
    ADC->INPUTCTRL.bit.MUXPOS = channel;
    while (ADC->STATUS.bit.SYNCBUSY);
    ADC->CTRLA.bit.ENABLE = 1;
    while (ADC->STATUS.bit.SYNCBUSY);
    ADC->SWTRIG.bit.START = 1;
    while (!ADC->INTFLAG.bit.RESRDY);
    ADC->INTFLAG.reg = ADC_INTFLAG_RESRDY;
    /* discard first result */

    while (ADC->STATUS.bit.SYNCBUSY);
    ADC->SWTRIG.bit.START = 1;
    while (!ADC->INTFLAG.bit.RESRDY);

    val = ADC->RESULT.reg;

    while (ADC->STATUS.bit.SYNCBUSY);
    ADC->CTRLA.bit.ENABLE = 0;

    return val;
}
