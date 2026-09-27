# CANable2-Kai

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
- `tiiildd...[CR] `- Transmits base frame
- `Tiiiiiiiildd...[CR] `- Transmits extended frame
- `diiildd...[CR] `- Transmits CANFD base frame (BRS disabled)
- `Diiiiiiiildd...[CR] `- Transmits CANFD extended frames (BRS disabled)
- `biiildd...[CR] `- Transmits CANFD base frames (BRS enabled)
- `Biiiiiiiildd...[CR] `- Transmits CANFD extended frames (BRS enable)
- `V[CR]` and `v[CR]` - Returns firmware version and remote path as a string
- `Z` and `z` - Configures reporting mechanism including time stamp and Tx event
- `M` and `m` - Configures CAN acceptance filter
- `F[CR]` - Returns status flags

`[CR]` : `0x0D` (hex), `\r` (ascii)

Please find more information in the `doc` directory or the [wiki](https://github.com/Nakakiyo092/canable2kai/wiki).


## Toolchain

The toolchain in this repository is designed to run on a Linux PC especially Ubuntu.

### Dependencies

On Ubuntu, the required tools can be installed with:

```bash
sudo apt install git gcc-arm-none-eabi dfu-util
```

### How to build firmware

Simply compile by running `make`.

### How to flash firmware

Plug in your device in boot mode. Next, type `make flash` and your device will be updated to the latest firmware. Unplug the device and replug in normal mode, and your device will be up and running.

## Credits

### Related work

| Name | Author | License |
|------|--------|---------|
| [canable2-fw](https://github.com/normaldotcom/canable2-fw) | Openlight Labs | GPL-3.0 |

### Bundled third-party components

See LICENSE.md for the full list of bundled components and their licenses.

