# CANable 2.0 Firmware

This repository contains sources for the slcan CANable 2.0 firmware. This firmware implements non-standard commands to support CANFD messaging (beta) alongside a LAWICEL-style command set.

## Frequently Used Commands

- `O` - Opens channel
- `C` - Closes channel
- `sddxxyyzz` - Sets nominal bitrate and bittiming
- `yddxxyyzz` - Sets data bitrate and bittiming
- `tiiildd...` - Transmits a classical base data frame
- `Tiiiiiiiildd...` - Transmits a classical extended data frame
- `diiildd...` - Transmits a FD base data frame without bit rate switch
- `Diiiiiiiildd...` - Transmits a FD extended data frame without bit rate switch
- `biiildd...` - Transmits a FD base data frame with bit rate switch
- `Biiiiiiiildd...` - Transmits a FD extended data frame with bit rate switch
- `V` and `v` - Returns firmware version and remote path as a string
- `Z` and `z` - Configures reporting mechanism including time stamp and Tx event
- `M` and `m` - Configures CAN acceptance filter
- `F` - Returns status flags

Please find more information in the `doc` directory or the [wiki](https://github.com/Nakakiyo092/canable2kai/wiki).

## Dependencies

- GNU Arm Embedded Toolchain (`arm-none-eabi-gcc`)
- CMake 3.25 or later
- Ninja
- dfu-util (for flashing)
- git

The toolchain binaries must be in your PATH. On Ubuntu, the required tools can be installed with:

```bash
sudo apt install gcc-arm-none-eabi cmake ninja-build dfu-util git
```

## Building

The build uses CMake presets. `cmake --list-presets` shows the available boards.

```bash
cmake --preset canable2
cmake --build --preset canable2
```

The firmware is written to `build/canable2/` (`canable2.elf`, `canable2.bin`, `canable2.hex`, `canable2.map`).

The former Makefile has been removed. The commands map as follows:

| Former command | Command |
|----------------|---------|
| `make`         | `cmake --preset canable2` (first time only), then `cmake --build --preset canable2` |
| `make flash`   | `cmake --build --preset canable2 --target upload` |
| `make clean`   | `cmake --build --preset canable2 --target clean` |

## Flashing with the Bootloader

Plug in your CANable2 while boot pins are shorted with jumper. Neither the blue nor the green LED should be illuminated. Next, run `cmake --build --preset canable2 --target upload` and your CANable will be updated to the firmware. Unplug/replug the device after moving the boot jumper back, and your CANable2 will be up and running.

On Linux, dfu-util needs permission to access the device (a udev rule, or running the command with `sudo`).

## License

See LICENSE.md
