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

#if defined(USE_TINYUSB)
#include <stdint.h>
#include <Arduino.h>
#include <Adafruit_TinyUSB.h>
#include "../mzkbd/kbdconfig.h"
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

#else /* defined(USE_TINYUSB) */

#include <stdint.h>
#include <Arduino.h>
#include <HID.h>
#include "../mzkbd/kbdconfig.h"
#include "../mzkbd/hid.h"

typedef struct
{
  uint8_t modifiers;
  uint8_t reserved;
  uint8_t keys[6];
} KeyReport;

typedef struct
{
  uint8_t buttons;
  uint8_t x;
  uint8_t y;
  uint8_t wheel;
  uint8_t pan;
} MouseReport;

static const uint8_t _hidReportDescriptor[] PROGMEM = {
    //  Keyboard
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)  // 47
    0x09, 0x06,                    // USAGE (Keyboard)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x85, RID_KEYBOARD,            //   REPORT_ID (RID_KEYBOARD)
    0x05, 0x07,                    //   USAGE_PAGE (Keyboard)

    0x19, 0xe0,                    //   USAGE_MINIMUM (Keyboard LeftControl)
    0x29, 0xe7,                    //   USAGE_MAXIMUM (Keyboard Right GUI)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
    0x75, 0x01,                    //   REPORT_SIZE (1)

    0x95, 0x08,                    //   REPORT_COUNT (8)
    0x81, 0x02,                    //   INPUT (Data,Var,Abs)
    0x95, 0x01,                    //   REPORT_COUNT (1)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x81, 0x03,                    //   INPUT (Cnst,Var,Abs)

    0x95, 0x06,                    //   REPORT_COUNT (6)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x73,                    //   LOGICAL_MAXIMUM (115)
    0x05, 0x07,                    //   USAGE_PAGE (Keyboard)

    0x19, 0x00,                    //   USAGE_MINIMUM (Reserved (no event indicated))
    0x29, 0x73,                    //   USAGE_MAXIMUM (Keyboard Application)
    0x81, 0x00,                    //   INPUT (Data,Ary,Abs)
    0xc0,                          // END_COLLECTION

#if USE_MOUSE
    //  Mouse
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)  // 54
    0x09, 0x02,                    // USAGE (Mouse)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x09, 0x01,                    //   USAGE (Pointer)
    0xa1, 0x00,                    //   COLLECTION (Physical)
    0x85, RID_MOUSE,               //     REPORT_ID (RID_MOUSE)
    0x05, 0x09,                    //     USAGE_PAGE (Button)
    0x19, 0x01,                    //     USAGE_MINIMUM (Button 1)
    0x29, 0x03,                    //     USAGE_MAXIMUM (Button 3)
    0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //     LOGICAL_MAXIMUM (1)
    0x95, 0x03,                    //     REPORT_COUNT (3)
    0x75, 0x01,                    //     REPORT_SIZE (1)
    0x81, 0x02,                    //     INPUT (Data,Var,Abs)
    0x95, 0x01,                    //     REPORT_COUNT (1)
    0x75, 0x05,                    //     REPORT_SIZE (5)
    0x81, 0x03,                    //     INPUT (Cnst,Var,Abs)
    0x05, 0x01,                    //     USAGE_PAGE (Generic Desktop)
    0x09, 0x30,                    //     USAGE (X)
    0x09, 0x31,                    //     USAGE (Y)
    0x09, 0x38,                    //     USAGE (Wheel)
    0x15, 0x81,                    //     LOGICAL_MINIMUM (-127)
    0x25, 0x7f,                    //     LOGICAL_MAXIMUM (127)
    0x75, 0x08,                    //     REPORT_SIZE (8)
    0x95, 0x03,                    //     REPORT_COUNT (3)
    0x81, 0x06,                    //     INPUT (Data,Var,Rel)
    0xc0,                          //   END_COLLECTION
    0xc0,                          // END_COLLECTION
#endif USE_MOUSE
};

static HIDSubDescriptor node(_hidReportDescriptor, sizeof(_hidReportDescriptor));

void hid_init(void)
{
    HID().AppendDescriptor(&node);
}

void hid_task(void)
{
}

void keyboard_report(uint8_t modifier, uint8_t keycode[KEYCODES_SIZE])
{
    KeyReport report = {modifier, 0};
    memcpy(report.keys, keycode, 6);
    HID().SendReport(RID_KEYBOARD, &report, sizeof(report));
}

void mouse_report(uint8_t buttons,
    int8_t x, int8_t y, int8_t vertical, int8_t horizontal)
{
#if USE_MOUSE
    MouseReport report = {buttons, x, y, vertical, horizontal};
    HID().SendReport(RID_MOUSE, &report, sizeof(report));
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
    uint8_t report[2] = {mediakey&0xff, (mediakey>>8)&0xff};
    HID().SendReport(RID_MOUSE, &report, sizeof(report));
}
#endif

#endif /* defined(USE_TINYUSB) */
