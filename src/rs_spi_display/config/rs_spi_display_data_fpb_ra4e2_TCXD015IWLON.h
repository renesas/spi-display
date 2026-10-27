/***********************************************************************************************************************
 * File Name    : rs_spi_display_data_fpb_ra4e2_TCXD015IWLON.h
 * Description  : Contains pre-set configuration declarations for fpb-ra4e2 and external display TCXD015IWLON.
 **********************************************************************************************************************/
/***********************************************************************************************************************
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/

#ifndef RS_SPI_DISPLAY_CONFIG_RS_SPI_DISPLAY_DATA_FPB_RA4E2_TCXD015IWLON_H_
#define RS_SPI_DISPLAY_CONFIG_RS_SPI_DISPLAY_DATA_FPB_RA4E2_TCXD015IWLON_H_

#include <stdint.h>
#include "bsp_api.h"
#include "common_data.h"
#include "r_dtc.h"
#include "r_transfer_api.h"
#include "r_sci_spi.h"
#include "r_spi_api.h"
FSP_HEADER

/* Pinout for the Display Reset, Chip Select, and Data/Command signals to Arduino header. */
#ifndef DISP_RESET
#define DISP_RESET (BSP_IO_PORT_00_PIN_06)
#endif
#ifndef DISP_CS
#define DISP_CS (BSP_IO_PORT_03_PIN_01)
#endif
#ifndef DISP_DC
#define DISP_DC (BSP_IO_PORT_04_PIN_03)
#endif

/* Physical maximum X and Y resolution of the external display. */
#define X_RES_TCXD015IWLON  (128)
#define Y_RES_TCXD015IWLON  (128)

/* Offset to remove visual snow effect. */
#define X_OFFSET_TCXD015IWLON   (2)
#define Y_OFFSET_TCXD015IWLON   (1)

/* Transfer on DTC Instance. */
extern const transfer_instance_t g_transfer1_preset;

/** Access the DTC instance using these structures when calling API functions directly (::p_api is not used). */
extern dtc_instance_ctrl_t g_transfer1_preset_ctrl;
extern const transfer_cfg_t g_transfer1_preset_cfg;
/* Transfer on DTC Instance. */
extern const transfer_instance_t g_transfer0_preset;

/** Access the DTC instance using these structures when calling API functions directly (::p_api is not used). */
extern dtc_instance_ctrl_t g_transfer0_preset_ctrl;
extern const transfer_cfg_t g_transfer0_preset_cfg;
/** SPI on SCI Instance. */
extern const spi_instance_t g_spi_display_preset;

/** Access the SCI_SPI instance using these structures when calling API functions directly (::p_api is not used). */
extern sci_spi_instance_ctrl_t g_spi_display_ctrl;
extern const spi_cfg_t g_spi_display_cfg;

/** Called by the driver when a transfer has completed or an error has occurred (Must be implemented by the user). */
#ifndef spi_display_callback
void spi_display_callback(spi_callback_args_t *p_args);
#endif

#endif /* RS_SPI_DISPLAY_CONFIG_RS_SPI_DISPLAY_DATA_FPB_RA4E2_TCXD015IWLON_H_ */
