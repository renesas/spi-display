/***********************************************************************************************************************
 * File Name    : rs_spi_display.h
 * Description  : Contains macros, public data, and function declarations.
 **********************************************************************************************************************/
/***********************************************************************************************************************
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/

#ifndef RS_SPI_DISPLAY_RS_SPI_DISPLAY_FUNCTIONS_H_
#define RS_SPI_DISPLAY_RS_SPI_DISPLAY_FUNCTIONS_H_

#include <stdint.h>
#include <stdbool.h>
#include "bsp_api.h"
#include "r_spi_api.h"
#include "r_sci_spi.h"

/* Macros */
/* SPI Timeout */
#define RS_SPI_DISPLAY_TRANSFER_TIMEOUT   (1000000U)

/* Initialization */
#define RS_SPI_DISPLAY_USE_DELAY       (0x80)
#define RS_SPI_DISPLAY_DELAY_120_MS    (120)
#define RS_SPI_DISPLAY_DELAY_50_MS     (50)
#define RS_SPI_DISPLAY_DELAY_10_MS     (10)

/* Display Resolution */
#define RS_SPI_DISPLAY_MIN_X_RES    (8)
#define RS_SPI_DISPLAY_MIN_Y_RES    (8)
#define RS_SPI_DISPLAY_MAX_X_RES    (480)
#define RS_SPI_DISPLAY_MAX_Y_RES    (480)

/* Colors */
#define RS_SPI_DISPLAY_RGB565_RED      (0xf800)
#define RS_SPI_DISPLAY_RGB565_GREEN    (0x07e0)
#define RS_SPI_DISPLAY_RGB565_BLUE     (0x001f)
#define RS_SPI_DISPLAY_RGB565_YELLOW   (0xffe0)
#define RS_SPI_DISPLAY_RGB565_PURPLE   (0xf81f)
#define RS_SPI_DISPLAY_RGB565_CYAN     (0x07ff)
#define RS_SPI_DISPLAY_RGB565_WHITE    (0xffff)
#define RS_SPI_DISPLAY_RGB565_BLACK    (0x0000)
#define RS_SPI_DISPLAY_NUM_DEF_COLORS  (8)
#define RS_SPI_DISPLAY_RGB565_BYTES_PER_PIXEL   (2)

/* Public Data */
/* External LCD/OLED SPI Display Device Configuration */
typedef struct st_spi_display_device_cfg
{
    bsp_io_port_pin_t   reset_pinout;
    bsp_io_level_t      reset_active_lvl;
    bsp_io_level_t      reset_inactive_lvl;
    uint16_t            reset_delay_ms;

    bsp_io_port_pin_t   chip_select_pinout;
    bsp_io_level_t      cs_active_lvl;
    bsp_io_level_t      cs_inactive_lvl;

    bsp_io_port_pin_t   data_command_pinout;
    bsp_io_level_t      data_lvl;
    bsp_io_level_t      command_lvl;

    uint8_t             write_gddram_command;
    uint16_t            canvas_x_resolution;
    uint16_t            canvas_y_resolution;

    const uint8_t *     p_display_init_sequence;

} rs_spi_display_device_cfg_t;

/* SPI Display Layer Control Block */
typedef struct st_spi_display_ctrl
{
    bool    open;

    /* SCI SPI Instance */
    sci_spi_instance_ctrl_t    spi_bus_ctrl;
    spi_cfg_t                  spi_bus_cfg;
    sci_spi_extended_cfg_t     spi_bus_cfg_extend;
    spi_instance_t             spi_bus;

    /* External Display Device Configuration */
    const rs_spi_display_device_cfg_t * p_device;

    uint32_t    canvas_pixel_count;
}rs_spi_display_ctrl_t;

/* Public Functions */
fsp_err_t rs_spi_display_Open(rs_spi_display_ctrl_t *p_spi_display_ctrl, const rs_spi_display_device_cfg_t *p_external_display_cfg);
fsp_err_t rs_spi_display_Close(rs_spi_display_ctrl_t *p_spi_display_ctrl);
fsp_err_t rs_spi_display_SendInitSequence( rs_spi_display_ctrl_t *p_spi_display_ctrl, const uint8_t * addr);
fsp_err_t rs_spi_display_SendData(rs_spi_display_ctrl_t *p_spi_display_ctrl, uint8_t data);
fsp_err_t rs_spi_display_SendCommand(rs_spi_display_ctrl_t *p_spi_display_ctrl, uint8_t command);
fsp_err_t rs_spi_display_FillScreen(rs_spi_display_ctrl_t *p_spi_display_ctrl, uint16_t color);
fsp_err_t rs_spi_display_DrawColoredBars(rs_spi_display_ctrl_t *p_spi_display_ctrl);
fsp_err_t rs_spi_display_DrawFramebuffer( rs_spi_display_ctrl_t *p_spi_display_ctrl, const uint16_t * p_framebuffer);

/* Public Configuration Functions */
fsp_err_t rs_spi_display_ConfigGen(rs_spi_display_ctrl_t *p_spi_display_ctrl, const spi_instance_t * p_spi_display_bus);
fsp_err_t rs_spi_display_ConfigCheck(rs_spi_display_ctrl_t *p_spi_display_ctrl);

#endif /* RS_SPI_DISPLAY_RS_SPI_DISPLAY_FUNCTIONS_H_ */
