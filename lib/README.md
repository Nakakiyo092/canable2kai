# Vendored libraries

Each library is kept at a fixed path `lib/<name>/` and contains upstream files only.
To update a library, overwrite its directory in place so that the diff shows the upstream changes, and update this file.

| Name | Upstream | Version | License | Imported |
|------|----------|---------|---------|----------|
| `cmsis_core` | [ARM-software/CMSIS_5](https://github.com/ARM-software/CMSIS_5) | CMSIS-Core(M) 5.1 (`core_cm4.h` V5.0.8) | Apache-2.0 | 2021-03-08 |
| `cmsis_device_g4` | [STMicroelectronics/cmsis_device_g4](https://github.com/STMicroelectronics/cmsis_device_g4) | V1.1.0 | BSD-3-Clause | 2021-03-08 |
| `stm32g4xx_hal_driver` | [STMicroelectronics/stm32g4xx_hal_driver](https://github.com/STMicroelectronics/stm32g4xx_hal_driver) | V1.1.0 | BSD-3-Clause | 2021-03-08 |
| `stm32_mw_usb_device` | [STMicroelectronics/stm32_mw_usb_device](https://github.com/STMicroelectronics/stm32_mw_usb_device) | Not recorded in the source files | SLA0044 | 2021-03-08 |

All libraries were imported as bundled with STM32CubeG4 V1.1.0.
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

### stm32_mw_usb_device

Only `Core` and `Class/CDC` are kept.
This library is planned to be replaced by tinyUSB.

- `Class/CDC/Inc/usbd_cdc.h`: `CDC_DATA_HS_MAX_PACKET_SIZE` is set to `CDC_DATA_FS_MAX_PACKET_SIZE` (the HS setting is unused).
- `Class/CDC/Src/usbd_cdc.c`: configuration descriptors report bus powered, MaxPower 500 mA (`bmAttributes = 0x80`, `MaxPower = 0xFA`).
- Line endings of some files were converted.
