# Vendored libraries

Each library is kept at a fixed path `lib/<name>/` and contains upstream files only.
To update a library, overwrite its directory in place so that the diff shows the upstream changes, and update this file.

| Name | Upstream | Version | License | Imported |
|------|----------|---------|---------|----------|
| `cmsis_core` | [ARM-software/CMSIS_5](https://github.com/ARM-software/CMSIS_5) | 5.9.0 (CMSIS-Core(M) 5.6.0) | Apache-2.0 | 2026-10-16 |
| `cmsis_device_g4` | [STMicroelectronics/cmsis-device-g4](https://github.com/STMicroelectronics/cmsis-device-g4) | v1.2.6 | BSD-3-Clause | 2026-10-16 |
| `stm32g4xx_hal_driver` | [STMicroelectronics/stm32g4xx-hal-driver](https://github.com/STMicroelectronics/stm32g4xx-hal-driver) | v1.2.7 | BSD-3-Clause | 2026-10-16 |
| `tinyusb` | [hathach/tinyusb_src](https://github.com/hathach/tinyusb_src) | 0.21.0 | MIT | 2026-10-12 |
| `printf` | [eyalroz/printf](https://github.com/eyalroz/printf) | v6.4.0 | MIT | 2026-10-15 |

Each library keeps the license file of its upstream repository.


## Subsets and modifications

### cmsis_core

Only `CMSIS/Core/Include` (as `Include/`) and `LICENSE.txt` are kept.
Other CMSIS components (DSP, Core_A, Lib, etc.) are not used and not included.
Tag `5.9.0` (commit 2b7495b8535bdcb306dac29b9ded4cfb679d7e5c).
No modifications.

### cmsis_device_g4

Only `Include/`, `Source/` and `LICENSE.md` are kept.
Tag `v1.2.6` (commit 25664ddc3a7624ae9627ae8c4c672073dc5b2539).
No modifications.
`src/system_stm32g4xx.c` and `src/startup_stm32g431xx.s` are copies of the templates in `Source/Templates/`.

### stm32g4xx_hal_driver

Only `Inc/`, `Src/` and `LICENSE.md` are kept.
Tag `v1.2.7` (commit f5929f431f9effe45fbe18f5337e4753ced9ac92).
No modifications.
The `*_template.c` files in `Src/` are excluded from the build (`cmake/stm32g4.cmake`).
`inc/stm32g4xx_hal_conf.h` is based on `Inc/stm32g4xx_hal_conf_template.h`.

### tinyusb

Imported from the sources-only mirror of [hathach/tinyusb](https://github.com/hathach/tinyusb) (`src/` and `LICENSE`).
No modifications.

### printf

Only `src/printf/` and `LICENSE` are kept.
The build configuration (`CMakeLists.txt`, `printf_config.h.in`) and the tests are not included; the options are set as preprocessor definitions in the top-level `CMakeLists.txt`.
No modifications.
