# stm32_mw_usb_device

Vendored from: STM32 USB Device Library, as bundled with STM32CubeG4 (the exact library version is not recorded in the source files)
Upstream: https://github.com/STMicroelectronics/stm32_mw_usb_device
License: Ultimate Liberty license SLA0044 (www.st.com/SLA0044)
Imported: 2021-03-08

Only `Core` and `Class/CDC` are kept.

Modifications:

- `Class/CDC/Inc/usbd_cdc.h`: `CDC_DATA_HS_MAX_PACKET_SIZE` is set to `CDC_DATA_FS_MAX_PACKET_SIZE` (the HS setting is unused).
- `Class/CDC/Src/usbd_cdc.c`: configuration descriptors report bus powered, MaxPower 500 mA (`bmAttributes = 0x80`, `MaxPower = 0xFA`).
- Line endings of some files were converted.

This library is planned to be replaced by tinyUSB.
