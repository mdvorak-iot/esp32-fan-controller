# esp-fan-controller

Single-purpose built controller for driving PWM fans according to temperature.

Based on ESP RainMaker platform.

## Usage

To provision WiFi, use provisioning app:

* [Android BLE Provisioning app](https://play.google.com/store/apps/details?id=com.espressif.provble)
* [iOS BLE Provisioning app](https://apps.apple.com/in/app/esp-ble-provisioning/id1473590141)

To initiate provisioning mode, reset the device twice (double tap reset in about 1s interval). Status LED will start
flashing rapidly.

See [Kconfig.projbuild](./main/Kconfig.projbuild) and [sdkconfig.defaults](./sdkconfig.defaults) for default config.

## Development

Prepare [ESP-IDF development environment](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html#get-started-get-prerequisites)
.

Configure application with

```
idf.py menuconfig
```

and select `Application configuration` in root menu and configure application parameters.

Flash it via

```
idf.py -b 921600 build flash monitor
```

As an alternative, you can use [PlatformIO](https://docs.platformio.org/en/latest/core/installation.html) to build and
flash the project.
