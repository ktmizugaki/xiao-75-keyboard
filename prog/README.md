# xiao 75% keyboard firmware
This directory contains source code of firmware for xiao-75-keyboard.
This firmware is based on Arduino and supports only SAMD21 version of XIAO.

# Building firmware with Arduino-Makefile

I use [Arduino-Makefile](https://github.com/sudar/Arduino-Makefile) to compile.

Also my Makefile depends on specific directory structure.
See [here](https://gist.github.com/ktmizugaki/b0e66981756d498a5b219d92f9de6cc5#file-arduino_install-md) for the way I setup build environment.

To compile, requires followings.

* build tools for samd21:
  * CMSIS-4.5.0
  * CMSIS-Atmel-1.2.0
  * bossac-1.7.0-arduino3
  * Arduino-Makefile
    * https://github.com/sudar/Arduino-Makefile
    * commit: a1fbda0c53a75862bd7ac6285b70103ed04f70a6
  * gcc-arm-none-eabi
* arduino core:
  * https://github.com/Seeed-Studio/ArduinoCore-samd
  * commit: 28c4ac5980a0393f7417c773c5d8fa4f5283b379
  * with patch arduinocore-patch/0001-Adapt-to-latest-Adafruit_TinyUSB.patch applied
* additional library:
  * Adafruit TinyUSB
     * https://github.com/adafruit/Adafruit_TinyUSB_Arduino
     * commit: d5d96c4790a16d972149c2da9499ba63b86db1f4

After setting up build environment, run `make` to build firmware and `make upload` to flash firmware to XIAO.

This firmware disables USB-CDC and automatic reset doesn't work.
Use double-tap-reset or press `Fn+R` if XIAO is attached to xiao 75% keyboard to enter bootloader.

# Building firmware with Arduino IDE

1. Setup Seeed SAMD development environment as per [Official guide](https://wiki.seeedstudio.com/Seeeduino-XIAO/#getting-started).
2. Open prog.ino from Arduino IDE.
3. Select Seeed XIAO in board menu.
4. Since Seeed's official core doesn't support TinyUSB, select Arduino's USB Stack which is default.
5. Connect Seeed XIAO and upload sketch.

It seems like USB-CDC can't be disabled with arduino's USB stack.
