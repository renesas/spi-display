/***********************************************************************************************************************
 * File Name    : rs_spi_display_data_fpb_ra4e2_TCXD015IWLON.c
 * Description  : Contains pre-set configuration settings for interfacing fpb-ra4e2 to external display TCXD015IWLON.
 **********************************************************************************************************************/
/***********************************************************************************************************************
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/

/* generated HAL source file - do not edit */
#include "rs_spi_display_data_fpb_ra4e2_TCXD015IWLON.h"

dtc_instance_ctrl_t g_transfer1_preset_ctrl;

transfer_info_t g_transfer1_preset_info DTC_TRANSFER_INFO_ALIGNMENT =
{
    .transfer_settings_word_b.dest_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED,
    .transfer_settings_word_b.repeat_area = TRANSFER_REPEAT_AREA_DESTINATION,
    .transfer_settings_word_b.irq = TRANSFER_IRQ_END,
    .transfer_settings_word_b.chain_mode = TRANSFER_CHAIN_MODE_DISABLED,
    .transfer_settings_word_b.src_addr_mode = TRANSFER_ADDR_MODE_FIXED,
    .transfer_settings_word_b.size = TRANSFER_SIZE_1_BYTE,
    .transfer_settings_word_b.mode = TRANSFER_MODE_NORMAL,
    .p_dest = (void*) NULL,
    .p_src = (void const*) NULL,
    .num_blocks = (uint16_t) 0,
    .length = (uint16_t) 0,
};

const dtc_extended_cfg_t g_transfer1_preset_cfg_extend =
{
    .activation_source = VECTOR_NUMBER_SCI9_RXI,
};

const transfer_cfg_t g_transfer1_preset_cfg =
{
    .p_info = &g_transfer1_preset_info,
    .p_extend = &g_transfer1_preset_cfg_extend,
};

/* Instance structure to use this module. */
const transfer_instance_t g_transfer1_preset =
{
    .p_ctrl = &g_transfer1_preset_ctrl,
    .p_cfg = &g_transfer1_preset_cfg,
    .p_api = &g_transfer_on_dtc
};

dtc_instance_ctrl_t g_transfer0_preset_ctrl;

transfer_info_t g_transfer0_preset_info DTC_TRANSFER_INFO_ALIGNMENT =
{
    .transfer_settings_word_b.dest_addr_mode = TRANSFER_ADDR_MODE_FIXED,
    .transfer_settings_word_b.repeat_area = TRANSFER_REPEAT_AREA_SOURCE,
    .transfer_settings_word_b.irq = TRANSFER_IRQ_END,
    .transfer_settings_word_b.chain_mode = TRANSFER_CHAIN_MODE_DISABLED,
    .transfer_settings_word_b.src_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED,
    .transfer_settings_word_b.size = TRANSFER_SIZE_1_BYTE,
    .transfer_settings_word_b.mode = TRANSFER_MODE_NORMAL,
    .p_dest = (void*) NULL,
    .p_src = (void const*) NULL,
    .num_blocks = (uint16_t) 0,
    .length = (uint16_t) 0,
};


const dtc_extended_cfg_t g_transfer0_preset_cfg_extend =
{
    .activation_source = VECTOR_NUMBER_SCI9_TXI,
};

const transfer_cfg_t g_transfer0_preset_cfg =
{
    .p_info = &g_transfer0_preset_info,
    .p_extend = &g_transfer0_preset_cfg_extend,
};

/* Instance structure to use this module. */
const transfer_instance_t g_transfer0_preset =
{
    .p_ctrl = &g_transfer0_preset_ctrl,
    .p_cfg = &g_transfer0_preset_cfg,
    .p_api = &g_transfer_on_dtc
};
sci_spi_instance_ctrl_t g_spi_display_preset_ctrl;

/** SPI extended configuration */
const sci_spi_extended_cfg_t g_spi_display_preset_cfg_extend =
{
    .clk_div =
    {/* Actual calculated bitrate: 25000000. */
         .cks = 0,
         .brr = 0,
         .mddr = 0,
    }
};

const spi_cfg_t g_spi_display_preset_cfg =
{
    .channel = 9,
    .operating_mode = SPI_MODE_MASTER,
    .clk_phase = SPI_CLK_PHASE_EDGE_ODD,
    .clk_polarity = SPI_CLK_POLARITY_LOW,
    .mode_fault = SPI_MODE_FAULT_ERROR_DISABLE,
    .bit_order = SPI_BIT_ORDER_MSB_FIRST,
    .p_transfer_tx = &g_transfer0_preset,
    .p_transfer_rx = &g_transfer1_preset,
    .p_callback = spi_display_callback,
    .p_context = NULL,
    .rxi_irq = VECTOR_NUMBER_SCI9_RXI,
    .txi_irq = VECTOR_NUMBER_SCI9_TXI,
    .tei_irq = VECTOR_NUMBER_SCI9_TEI,
    .eri_irq = VECTOR_NUMBER_SCI9_ERI,
    .rxi_ipl = (12),
    .txi_ipl = (12),
    .tei_ipl = (12),
    .eri_ipl = (12),
    .p_extend = &g_spi_display_preset_cfg_extend,
};

/* Instance structure to use this module. */
const spi_instance_t g_spi_display_preset =
{
    .p_ctrl = &g_spi_display_preset_ctrl,
    .p_cfg = &g_spi_display_preset_cfg,
    .p_api = &g_spi_on_sci
};
