/*
 * MCP2210 hacky edit-this-file header for settings
 * Copyright (c) 2013 Daniel Santos <daniel.santos@pobox.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file due to the fact that I have no better means to do configuration, edit
 * this file to your needs and recompile the userspace utility
 */

#ifndef _SETTINGS_H
#define _SETTINGS_H

#include <linux/spi/spidev.h>

/*
 * The power up settings are just that, the settings the chip will have at
 * power up.  These settings are configured into the mcp2210 flash by the
 * appropriate command.  These setting (not the flash entry) may be changed by
 * the driver during initialization using the my_board_config settings.
 * The power up and the my_board_config settings may be different.
 */

/*
 * Used to configure MMCP2210 CHIP SETTINGS POWER-UP DEFAULT using
 * mcp2210-util set config 2
 *
 * MCP2210 reference:
 *    3.1.1 CHIP SETTINGS POWER-UP DEFAULT
 */

static const struct mcp2210_chip_settings my_power_up_chip_settings = {
	.pin_mode = {
		MCP2210_PIN_SPI,
		MCP2210_PIN_GPIO,
		MCP2210_PIN_DEDICATED,  /* Dedicated = USB Suspend */
		MCP2210_PIN_DEDICATED,  /* Dedicated = SPI Transfer LED */
		MCP2210_PIN_DEDICATED,  /* Dedicated = USB Low Power */
		MCP2210_PIN_DEDICATED,  /* Dedicated = USB Configured */
		MCP2210_PIN_DEDICATED,  /* Dedicated = External Interrupt */
		MCP2210_PIN_SPI,        /* Dedicated = SPI Bus Release ACK */
		MCP2210_PIN_GPIO,       /* Dedicated = SPI Bus Release REQ */
	},
	.gpio_value		= 0x0002,
	.gpio_direction		= 0x0140,
	.other_settings		= 0x01,
	.nvram_access_control	= 0,
	.password = {0, 0, 0, 0, 0, 0, 0, 0},
};


/*
 * Used to configure SET SPI POWER-UP TRANSFER SETTINGS using
 * mcp2210-util set config 8
 *
 * MCP2210 reference
 *   3.1.2 SET SPI POWER-UP TRANSFER SETTINGS
 */
static const struct mcp2210_spi_xfer_settings my_power_up_spi_settings = {
	.bitrate		= MCP2210_MAX_SPEED,
	.idle_cs		= 0x01ff,
	.active_cs		= 0x0000,
	.cs_to_data_delay	= 1,
	.last_byte_to_cs_delay	= 1,
	.delay_between_bytes	= 1,
	.bytes_per_trans	= 4,
	.mode			= SPI_MODE_3
};


/*
 * Used to set SET (VM) CURRENT CHIP SETTINGS using
 *   mcp2210-util set config 1
 * Also used for creek encode command using
 *   mcp2210-util encode
 *
 * Usually the same as my_power_up_chip_settings
 *
 * MCP2210 reference
 *    3.2.4 SET (VM) CURRENT CHIP SETTINGS
 */
#define my_chip_settings my_power_up_chip_settings

/*
 * Used to set SET (VM) SPI TRANSFER SETTINGS using
 *   mcp2210-util set config 4
 * Also used for creek encode command using
 *   mcp2210-util encode
 *
 * Usually the same as my_power_up_spi_settings
 *
 * MCP2210 reference
 *    3.2.2 SET (VM) SPI TRANSFER SETTINGS
 */
#define my_spi_settings  my_power_up_spi_settings


/*
 * Used to set SET USB POWER-UP KEY PARAMETERS using
 * mcp2210-util set config 16
 *
 * MCP2210 reference:
 *    3.1.3 SET USB POWER-UP KEY PARAMETERS
 */
static const struct mcp2210_usb_key_params my_usb_key_params = {
	.vid		   = USB_VENDOR_ID_MICROCHIP,
	.pid		   = USB_DEVICE_ID_MCP2210,
	.chip_power_option = 0x80,
	.requested_power   = 0x32, /* 100mA */
};


/*
 * Used to configure the board using using
 *   mcp2210-util set config 32
 * Aslo used for creek encode using
 *   mcp2210-util encode
 *
 * see mcp2210-creek for further details.
 */
static const struct mcp2210_board_config my_board_config = {
	.pins = {
		{
			.mode = MCP2210_PIN_SPI,
			.spi.max_speed_hz = 20000,
			.spi.min_speed_hz = 2000,
			.spi.mode = SPI_MODE_3,
			.spi.bits_per_word = 8,
			.spi.cs_to_data_delay = 1,
			.spi.last_byte_to_cs_delay = 1,
			.spi.delay_between_bytes = 1,
			.spi.delay_between_xfers = 1,
			.modalias = "spidev",
			.name = "L6470",
		}, {
			.mode = MCP2210_PIN_GPIO,
			.has_irq = 0,
			.irq = 0,
			.name = "unused%d",
		}, {
			.mode = MCP2210_PIN_DEDICATED,
			.name = "SSPND"
		}, {
			.mode = MCP2210_PIN_DEDICATED,
			.name = "USBLED",
		}, {
			.mode = MCP2210_PIN_DEDICATED,
			.name = "LOWPWR",
		}, {
			.mode = MCP2210_PIN_DEDICATED,
			.name = "USBCFG",
		}, {
			.mode = MCP2210_PIN_DEDICATED,
			.has_irq = 0,
			.irq = 0,
			.name = "MOTION",
		}, {
			.mode = MCP2210_PIN_SPI,
			.has_irq = 0,
			.irq = 0,
			.spi.max_speed_hz = 20000,
			.spi.min_speed_hz = 5000,
			.spi.mode = SPI_MODE_3,
			.spi.bits_per_word = 8,
			.spi.use_cs_gpio = 0,
			.spi.cs_gpio = 0,
			.spi.cs_to_data_delay = 2,
			.spi.last_byte_to_cs_delay = 2,
			.spi.delay_between_bytes = 4,
			.spi.delay_between_xfers = 10,
			.modalias = "spidev",
			.name = "ADNS-9800",
		}, {
			.mode = MCP2210_PIN_GPIO,
			.name = "unused%d",
		}
	},
	.poll_gpio_usecs	      = 0,
	.stale_gpio_usecs	      = 0,
	.poll_intr_usecs	      = 0,
	.stale_intr_usecs	      = 0,
	._3wire_capable		      = 0,
	._3wire_tx_enable_active_high = 0,
	._3wire_tx_enable_pin	      = 0,
	.strings_size		      = 0,
};

#endif /* _SETTINGS_H */
