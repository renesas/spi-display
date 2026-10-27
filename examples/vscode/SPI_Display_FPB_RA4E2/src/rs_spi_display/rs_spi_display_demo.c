/***********************************************************************************************************************
 * File Name    : rs_spi_display_demo.c
 * Description  : Contains demonstration function and related macro definitions.
 **********************************************************************************************************************/
/***********************************************************************************************************************
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
#include "rs_spi_display.h"
#include "rs_spi_display_ST7735SV.h"

#if RS_SPI_DISPLAY_USE_PRESET_CFG   //Use pre-set configuration for SPI Display
#ifdef BSP_MCU_R7FA4E2B93CFM
#include "rs_spi_display_data_fpb_ra4e2_TCXD015IWLON.h"
#endif
#else
#include "hal_data.h"
#endif

/** Initialization sequence for the TCXD015IWLON display. */
const uint8_t g_tcxd015iwlon_init[] =
{
    8 ,              //Number of commands in the init array

    ST7735SV_SWRESET,               // 1: Software reset
        RS_SPI_DISPLAY_USE_DELAY,   // No args, use a delay
        120,                        // 120ms delay

    ST7735SV_SLPOUT,                // 2: Out of sleep mode
        RS_SPI_DISPLAY_USE_DELAY,   // No args, use a delay
        120,                        // 120 ms delay

    ST7735SV_COLMOD,    // 3: Color Mode
        1,              // 1 arg, no delay
        0x05,           // Set 565RGB

    ST7735SV_MADCTL,    // 4: Memory Access Control
        1,              // 1 arg, no delay
        0x08,           // BGR

    ST7735SV_CASET,                         // 5: Column Address Set
        4,                                  // 4 args, no delay
        0x00, 0x00+X_OFFSET_TCXD015IWLON,   // X start: 0+offset
        0x00, 0x7F+X_OFFSET_TCXD015IWLON,   // X end: 128+offset

    ST7735SV_RASET,                         // 6: Row Address Set
        4,                                  // 4 args, no delay
        0x00, 0x00+Y_OFFSET_TCXD015IWLON,   // Y start: 0+offset
        0x00, 0x7F+Y_OFFSET_TCXD015IWLON,   // Y end: 128+offset

    ST7735SV_NORON,         // 7: Normal mode on
        0,                  // no args, no delay

    ST7735SV_DISPON,        // 8: Display On
        0,                  // no args, no delays

    /* Can add additional B1h-C7h, E0h, and E1h panel-function commands
     * For optimal contrast, frame rate, and gamma. Values are display-vendor specific */
};

/** Device-specific configuration for the TCXD015IWLON display. */
const rs_spi_display_device_cfg_t  g_tcxd015iwlon_cfg =
{
    .reset_pinout =       DISP_RESET,
    .reset_active_lvl =   ST7735SV_RESET_ACTIVE_LVL,
    .reset_inactive_lvl = ST7735SV_RESET_INACTIVE_LVL,
    .reset_delay_ms =     ST7735SV_RESET_DELAY_MS,

    .chip_select_pinout = DISP_CS,
    .cs_active_lvl =      ST7735SV_CS_SELECT_LVL,
    .cs_inactive_lvl =    ST7735SV_CS_DESELECT_LVL,

    .data_command_pinout = DISP_DC,
    .data_lvl =            ST7735SV_DATA_LVL,
    .command_lvl =         ST7735SV_CMD_LVL,

    .write_gddram_command = ST7735SV_RAMWR,
    .canvas_x_resolution =  X_RES_TCXD015IWLON,
    .canvas_y_resolution =  Y_RES_TCXD015IWLON,
    .p_display_init_sequence =  &g_tcxd015iwlon_init[0]

};

/** Control structure for the TCXD015IWLON SPI display instance. */
rs_spi_display_ctrl_t g_tcxd015iwlon_ctrl;

/***********************************************************************************************************************
 * @brief Demonstrates initialization and basic operation of the SPI display layer.
 *
 * @retval FSP_SUCCESS  SPI display demonstration completed successfully.
 * @return              Error code returned by the SPI display layer.
 **********************************************************************************************************************/
fsp_err_t spi_display_demo(void)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Generate configuration information for underlying SCI SPI driver. */
#if RS_SPI_DISPLAY_USE_PRESET_CFG   //Use pre-set configuration for SPI Display
    err = rs_spi_display_ConfigGen(&g_tcxd015iwlon_ctrl, &g_spi_display_preset);
    if(err) return err;

#else
    err = rs_spi_display_ConfigGen(&g_tcxd015iwlon_ctrl, &g_spi_display);
    if(err) return err;

#endif

    /* Check configuration information was properly initialized */
    err = rs_spi_display_ConfigCheck(&g_tcxd015iwlon_ctrl);
    if(err) return err;

    /* Open the SPI Display Layer */
    err = rs_spi_display_Open(&g_tcxd015iwlon_ctrl, &g_tcxd015iwlon_cfg);
    if(err) return err;

    /* Send the initialization sequence to configure and turn on external display. */
    err = rs_spi_display_SendInitSequence(&g_tcxd015iwlon_ctrl, g_tcxd015iwlon_ctrl.p_device->p_display_init_sequence);
    if(err) return err;

    /* Fill screen blue. */
    err = rs_spi_display_FillScreen( &g_tcxd015iwlon_ctrl, RS_SPI_DISPLAY_RGB565_BLUE);
    if(err) return err;

    /* Fill screen with colored bars */
    err = rs_spi_display_DrawColoredBars(&g_tcxd015iwlon_ctrl);
    if(err) return err;

    return err;

}
