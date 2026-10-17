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
// See also: LICENSE in the root of this repository
///////////////////////////////////////////////////////////////////////////////

// tinyUSB configuration

#ifndef TUSB_CONFIG_H
#define TUSB_CONFIG_H

// MCU and OS
#define CFG_TUSB_MCU                OPT_MCU_STM32G4
#define CFG_TUSB_OS                 OPT_OS_NONE

// Device stack
#define CFG_TUD_ENABLED             1
#define CFG_TUD_MAX_SPEED           OPT_MODE_FULL_SPEED
#define CFG_TUD_ENDPOINT0_SIZE      64

// Device classes
#define CFG_TUD_CDC                 1

// CDC FIFO sizes. The Tx FIFO takes a whole CDC Tx slot of buffer.c at once
// (BUF_CDC_TX_BUF_SIZE), and its content is sent in a single transfer.
#define CFG_TUD_CDC_RX_BUFSIZE      1024
#define CFG_TUD_CDC_TX_BUFSIZE      4096

// Keep Tx data while the host has not set DTR. When the FIFO is full, the data
// stays in the application buffer and its overflow is reported by the F flag.
#define CFG_TUD_CDC_TX_OVERWRITABLE_IF_NOT_CONNECTED 0

#endif // TUSB_CONFIG_H
