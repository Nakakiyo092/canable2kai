# Vendored libraries

Each library is kept at a fixed path `lib/<name>/` and contains upstream files only.
To update a library, overwrite its directory in place so that the diff shows the upstream changes, and update this file.

| Name | Upstream | Version | License | Imported |
|------|----------|---------|---------|----------|
| `cmsis_core` | [ARM-software/CMSIS_5](https://github.com/ARM-software/CMSIS_5) | CMSIS-Core(M) 5.1 (`core_cm4.h` V5.0.8) | Apache-2.0 | 2021-03-08 |
| `cmsis_device_g4` | [STMicroelectronics/cmsis_device_g4](https://github.com/STMicroelectronics/cmsis_device_g4) | V1.1.0 | BSD-3-Clause | 2021-03-08 |
| `stm32g4xx_hal_driver` | [STMicroelectronics/stm32g4xx_hal_driver](https://github.com/STMicroelectronics/stm32g4xx_hal_driver) | V1.1.0 | BSD-3-Clause | 2021-03-08 |
| `tinyusb` | [hathach/tinyusb_src](https://github.com/hathach/tinyusb_src) | 0.21.0 | MIT | 2026-10-12 |

The Arm and ST libraries were imported as bundled with STM32CubeG4 V1.1.0.
Licenses are as stated in the file headers of the imported versions.


## Subsets and modifications

### cmsis_core

Only `CMSIS/Core/Include` is kept, as `Include/`.
Other CMSIS components (DSP, Core_A, Lib, etc.) are not used and not included.
No modifications.

### cmsis_device_g4

No modifications.

### stm32g4xx_hal_driver

No modifications.

### tinyusb

Imported from the sources-only mirror of [hathach/tinyusb](https://github.com/hathach/tinyusb) (`src/` and `LICENSE`).
No modifications.
