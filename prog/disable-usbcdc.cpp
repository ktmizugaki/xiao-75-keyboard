#include "Adafruit_TinyUSB.h"

#if DISABLE_USBCDC
/* variant of initializer that disables USB-CDC */

extern "C" {

void TinyUSB_Device_Init(uint8_t rhport) {
  TinyUSBDevice.clearConfiguration();
  TinyUSB_Port_InitDevice(rhport);
}

}
#endif
