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

// USB descriptors for tinyUSB (single CDC interface)

#include <string.h>
#include "stm32g4xx.h"
#include "tusb.h"

#define USB_VID                     0x16D0
#define USB_PID                     0x117E

#define USB_MANUFACTURER_STRING     "Openlight Labs"
#define USB_PRODUCT_STRING          "CANable2" " " GIT_VERSION " " GIT_REMOTE
#define USB_CDC_STRING              "CDC Interface"

#define USB_STRING_MAX_CHARS        126     // Limited by bLength (255 bytes)
#define USB_UID_LEN                 12      // Bytes of the unique device ID

// String descriptor index
enum
{
    STRID_LANGID = 0,
    STRID_MANUFACTURER,
    STRID_PRODUCT,
    STRID_SERIAL,
    STRID_CDC,
};

// Interface number
enum
{
    ITF_NUM_CDC = 0,
    ITF_NUM_CDC_DATA,
    ITF_NUM_TOTAL
};

// Endpoint address
#define EPNUM_CDC_NOTIF             0x81
#define EPNUM_CDC_OUT               0x02
#define EPNUM_CDC_IN                0x82

#define CONFIG_TOTAL_LEN            (TUD_CONFIG_DESC_LEN + TUD_CDC_DESC_LEN)

// Device descriptor
static tusb_desc_device_t const desc_device =
{
    .bLength            = sizeof(tusb_desc_device_t),
    .bDescriptorType    = TUSB_DESC_DEVICE,
    .bcdUSB             = 0x0200,

    // Use Interface Association Descriptor (IAD) for CDC
    .bDeviceClass       = TUSB_CLASS_MISC,
    .bDeviceSubClass    = MISC_SUBCLASS_COMMON,
    .bDeviceProtocol    = MISC_PROTOCOL_IAD,
    .bMaxPacketSize0    = CFG_TUD_ENDPOINT0_SIZE,

    .idVendor           = USB_VID,
    .idProduct          = USB_PID,
    .bcdDevice          = 0x0100,

    .iManufacturer      = STRID_MANUFACTURER,
    .iProduct           = STRID_PRODUCT,
    .iSerialNumber      = STRID_SERIAL,

    .bNumConfigurations = 1
};

// Configuration descriptor (bus powered, 500 mA)
static uint8_t const desc_configuration[] =
{
    // Config number, interface count, string index, total length, attribute, power in mA
    TUD_CONFIG_DESCRIPTOR(1, ITF_NUM_TOTAL, 0, CONFIG_TOTAL_LEN, 0x00, 500),

    // Interface number, string index, EP notification address and size, EP data address (out, in) and size
    TUD_CDC_DESCRIPTOR(ITF_NUM_CDC, STRID_CDC, EPNUM_CDC_NOTIF, 8, EPNUM_CDC_OUT, EPNUM_CDC_IN, 64),
};

// String descriptors (LANGID and serial number are generated in the callback)
static char const *string_desc_arr[] =
{
    [STRID_MANUFACTURER] = USB_MANUFACTURER_STRING,
    [STRID_PRODUCT]      = USB_PRODUCT_STRING,
    [STRID_CDC]          = USB_CDC_STRING,
};

static uint16_t desc_str[USB_STRING_MAX_CHARS + 1];

// Serial number: the unique device ID in hex, as done by the tinyUSB board support
static size_t usb_get_serial(uint16_t *str, size_t max_chars)
{
    static char const nibble_to_hex[] = "0123456789ABCDEF";
    uint8_t const *uid = (uint8_t const *)UID_BASE;
    size_t len = USB_UID_LEN;

    if (len > max_chars / 2) len = max_chars / 2;

    for (size_t i = 0; i < len; i++)
    {
        str[2 * i]     = nibble_to_hex[uid[i] >> 4];
        str[2 * i + 1] = nibble_to_hex[uid[i] & 0x0F];
    }

    return 2 * len;
}

// Invoked when received GET DEVICE DESCRIPTOR
uint8_t const *tud_descriptor_device_cb(void)
{
    return (uint8_t const *)&desc_device;
}

// Invoked when received GET CONFIGURATION DESCRIPTOR
uint8_t const *tud_descriptor_configuration_cb(uint8_t index)
{
    (void)index;
    return desc_configuration;
}

// Invoked when received GET STRING DESCRIPTOR request
uint16_t const *tud_descriptor_string_cb(uint8_t index, uint16_t langid)
{
    (void)langid;
    size_t chr_count;

    if (index == STRID_LANGID)
    {
        desc_str[1] = 0x0409;   // English (United States)
        chr_count = 1;
    }
    else if (index == STRID_SERIAL)
    {
        chr_count = usb_get_serial(&desc_str[1], USB_STRING_MAX_CHARS);
    }
    else
    {
        if (index >= TU_ARRAY_SIZE(string_desc_arr) || string_desc_arr[index] == NULL) return NULL;

        char const *str = string_desc_arr[index];
        chr_count = strlen(str);
        if (chr_count > USB_STRING_MAX_CHARS) chr_count = USB_STRING_MAX_CHARS;

        // Convert ASCII string into UTF-16
        for (size_t i = 0; i < chr_count; i++)
        {
            desc_str[1 + i] = (uint16_t)str[i];
        }
    }

    // First element is the length (in bytes, including the header) and the descriptor type
    desc_str[0] = (uint16_t)((TUSB_DESC_STRING << 8) | (2 * chr_count + 2));

    return desc_str;
}
