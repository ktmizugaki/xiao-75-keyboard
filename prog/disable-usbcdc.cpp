#if DISABLE_USBCDC
#if defined(USE_TINYUSB)
#include "Adafruit_TinyUSB.h"

/* variant of initializer that disables USB-CDC */

extern "C" {

void TinyUSB_Device_Init(uint8_t rhport) {
  TinyUSBDevice.clearConfiguration();
  TinyUSB_Port_InitDevice(rhport);
}

}
#endif /* defined(USE_TINYUSB) */
#endif
