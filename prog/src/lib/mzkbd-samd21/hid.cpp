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
#include <Arduino.h>
#include <Adafruit_TinyUSB.h>
#include <kbdconfig.h>
#include "../mzkbd/hid.h"

static const uint8_t desc_hid_report[] = {
    TUD_HID_REPORT_DESC_KEYBOARD( HID_REPORT_ID(RID_KEYBOARD) ),
#if USE_MEDIAKEY
    TUD_HID_REPORT_DESC_CONSUMER( HID_REPORT_ID(RID_MEDIAKEY) ),
#endif
#if USE_MOUSE
    TUD_HID_REPORT_DESC_MOUSE( HID_REPORT_ID(RID_MOUSE) ),
#endif
};

static Adafruit_USBD_HID usb_hid(desc_hid_report, sizeof(desc_hid_report), HID_ITF_PROTOCOL_MOUSE, 2, false);
static bool s_woken;

void hid_init(void)
{
    usb_hid.begin();
    s_woken = 0;
}

void hid_task(void)
{
    s_woken = 0;
}

static void remote_wakeup(void)
{
    if (!s_woken) {
        if (TinyUSBDevice.suspended()) {
            TinyUSBDevice.remoteWakeup();
        }
        while (!usb_hid.ready()) {
            delay(1);
        }
        s_woken = 1;
    }
}

void keyboard_report(uint8_t modifier, uint8_t keycode[KEYCODES_SIZE])
{
    remote_wakeup();
    usb_hid.keyboardReport(RID_KEYBOARD, modifier, keycode);
}

void mouse_report(uint8_t buttons,
    int8_t x, int8_t y, int8_t vertical, int8_t horizontal)
{
#if USE_MOUSE
    remote_wakeup();
    usb_hid.mouseReport(RID_MOUSE, buttons, x, y, vertical, horizontal);
#else
    (void)buttons;
    (void)x;
    (void)y;
    (void)vertical;
    (void)horizontal;
#endif
}

#if USE_MEDIAKEY
void mediakey_report(uint16_t mediakey)
{
    remote_wakeup();
    usb_hid.sendReport16(RID_MEDIAKEY, mediakey);
}
#endif
