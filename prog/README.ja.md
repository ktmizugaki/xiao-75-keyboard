# xiao 75% keyboard firmware
このディレクトリには、 xiao-75-keyboard 用のファームウェアのソースコードが格納されています。

このファームウェアは Arduino ベースです。

SAMD21 版 XIAO にのみ対応しています。

# Arduino-Makefileを使ってファームウェアをビルドする。

私は [Arduino-Makefile](https://github.com/sudar/Arduino-Makefile) を使って、ファームウェアをビルドしています。

私なりの開発環境の構築方法: https://gist.github.com/ktmizugaki/b0e66981756d498a5b219d92f9de6cc5#file-arduino_install-md

ソースコードをコンパイルするのに、以下のツール類が必要です。
* SAMD21用ビルドツール:
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
  * TinyUSBに対応させるため、 arduinocore-patch/0001-Adapt-to-latest-Adafruit_TinyUSB.patch のパッチを適用してください。
* 追加のライブラリ:
  * Adafruit TinyUSB
     * https://github.com/adafruit/Adafruit_TinyUSB_Arduino
     * commit: d5d96c4790a16d972149c2da9499ba63b86db1f4

開発環境を構築後、 `make` でファームウェアがビルドされ、 `make upload` でファームウェアが XIAO に書き込まれます。

このファームウェアは、 USB-CDC を無効にするため、ツールによる自動リセットがされません。
次回ファームウェアを書き込む時は、ダブルタップリセットか、xiao 75% keyboard に接続して `Fn+R` を入力し、手動でブートローダモードにしてしてください。

# Arduino IDEを使ってファームウェアをビルドする。

1. [公式の手順](https://wiki.seeedstudio.com/jp/Seeeduino-XIAO/#seeeduino-xiao)に従い、Seeed XIAO の環境をセットアップします。
2. Arduino IDE で prog.ino を開きます。
3. board 一覧から Seeed XIAO を選択します。
4. Seeed XIAO の公式のcoreは最新の TinyUSB に未対応のため、USB Stackは標準のArduinoを使用します。
5. Seeed XIAO を接続し、 sketch を upload します。
