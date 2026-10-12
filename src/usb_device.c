///////////////////////////////////////////////////////////////////////////////
// GNU General Public License v3.0
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// Full license text: https://www.gnu.org/licenses/gpl-3.0.txt
// See also: LICENSE.md in the root of this repository
///////////////////////////////////////////////////////////////////////////////

// USB device initialization (tinyUSB)

#include "main.h"
#include "usb_device.h"
#include "tusb.h"

// Initialize the USB peripheral and the tinyUSB device stack.
// The USB clock source (HSI48) is selected in SystemClock_Config().
void MX_USB_Device_Init(void)
{
    __HAL_RCC_USB_CLK_ENABLE();

    // tinyUSB enables these interrupts in tusb_init()
    HAL_NVIC_SetPriority(USB_HP_IRQn, 2, 0);
    HAL_NVIC_SetPriority(USB_LP_IRQn, 2, 0);

    const tusb_rhport_init_t rh_init =
    {
        .role = TUSB_ROLE_DEVICE,
        .speed = TUSB_SPEED_FULL,
    };
    if (!tusb_init(0, &rh_init))
    {
        Error_Handler();
    }
}
