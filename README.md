# CANable2-Kai

CAN is a network that lets the controllers inside machines communicate with each other, mostly in vehicles but also in industrial machines, robots and agricultural equipment.
In a car, for example, these are the controllers for the engine, brakes, airbags and dashboard.
This firmware runs on a small USB adapter that connects a PC to such a network.
It is used to watch, record and send messages when developing, testing or diagnosing these systems.

This repository contains sources for the slcan CANable 2.0 firmware. This firmware implements non-standard commands to support CANFD messaging (beta) alongside a LAWICEL-style command set.

URL to this repository: https://github.com/Nakakiyo092/canable2kai


## Frequently used commands

- `O[CR]` - Opens the CAN channel
- `C[CR]` - Closes the CAN channel
- `sxxyy[CR]` - Sets custom nominal bit rate
- `Y0[CR]` - Sets the CANFD data segment bit rate to 500k
- `Y1[CR]` - Sets the CANFD data segment bit rate to 1M
- `Y2[CR]` - Sets the CANFD data segment bit rate to 2M
- `Y4[CR]` - Sets the CANFD data segment bit rate to 4M
- `Y5[CR]` - Sets the CANFD data segment bit rate to 5M
- `tiiildd...[CR]` - Transmits base frame
- `Tiiiiiiiildd...[CR]` - Transmits extended frame
- `diiildd...[CR]` - Transmits CAN FD base frame (BRS disabled)
- `Diiiiiiiildd...[CR]` - Transmits CAN FD extended frame (BRS disabled)
- `biiildd...[CR]` - Transmits CAN FD base frame (BRS enabled)
- `Biiiiiiiildd...[CR]` - Transmits CAN FD extended frame (BRS enabled)
- `V[CR]` and `v[CR]` - Returns firmware version and remote path as a string
- `Z` and `z` - Configures reporting mechanism including time stamp and Tx event
- `M` and `m` - Configures CAN acceptance filter
- `F[CR]` - Returns status flags

`[CR]` : `0x0D` (hex), `\r` (ascii)

Please find more information in the `doc` directory or the [wiki](https://github.com/Nakakiyo092/canable2kai/wiki).


## Toolchain

The build environment is intended for Linux, especially Ubuntu 24.04 or later.

### Dependencies

- git
- CMake 3.25 or later
- Ninja
- GNU Arm Embedded Toolchain
- dfu-util

On Ubuntu, the required tools can be installed with:

```bash
sudo apt install git cmake ninja-build gcc-arm-none-eabi dfu-util
```

### How to build firmware

The build uses CMake presets. `cmake --list-presets` shows the available boards.

```bash
cmake --preset canable2
cmake --build --preset canable2
```

The firmware is written to `build/canable2/` (`canable2.elf`, `canable2.bin`, `canable2.hex`, `canable2.map`).

The test suite under `test/` uses debug-only commands (e.g. loopback modes) and requires a debug build.
Use the `canable2-debug` preset for it. The firmware is written to `build/canable2-debug/`, and the `V` command returns a version string with `-DEBUG`.

```bash
cmake --preset canable2-debug
cmake --build --preset canable2-debug
```

The former Makefile has been removed. The commands map as follows:

| Former command | Command |
|----------------|---------|
| `make`         | `cmake --preset canable2` (first time only), then `cmake --build --preset canable2` |
| `make flash`   | `cmake --build --preset canable2 --target upload` |
| `make clean`   | `cmake --build --preset canable2 --target clean` |

### How to flash firmware

Plug in your device in boot mode (see [Hardware](doc/5.-Hardware.md) for how to enter it). Next, run the command below and your device will be updated to the firmware. Unplug/replug the device after returning it to normal mode, and your device will be up and running.

```bash
cmake --build --preset canable2 --target upload
```

For the debug build, use the `canable2-debug` preset instead.

```bash
cmake --build --preset canable2-debug --target upload
```

On Linux, dfu-util needs permission to access the device (a udev rule, or running the command with `sudo`).

### Related work

| Name | Author | License |
|------|--------|---------|
| [canable2-fw](https://github.com/normaldotcom/canable2-fw) | Openlight Labs | GPL-3.0 |

### Bundled third-party components

See lib/README.md for the full list of bundled components and their licenses.
