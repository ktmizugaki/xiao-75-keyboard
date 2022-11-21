BOARD_TAG = seeed_XIAO_m0
ARDUINO_LIBS = Adafruit_TinyUSB_Arduino HID
CPPFLAGS += -DUSE_TINYUSB -DDISABLE_USBCDC=1
CFLAGS += -Wall -Wextra -Wno-expansion-to-defined
CXXFLAGS += -Wall -Wextra -Wno-expansion-to-defined

LOCAL_C_SRCS = $(wildcard *.c) $(shell find src -type f -name "*.c")
LOCAL_CPP_SRCS = $(wildcard *.cpp) $(shell find src -type f -name "*.cpp")

TARGET = xiao-75-keyboard
USB_PRODUCT = "xiao 75 keyboard"
USB_MANUFACTURER = "ktmizugaki"

include $(ARDUINO_DIR)/arduino-mk/Sam.mk
