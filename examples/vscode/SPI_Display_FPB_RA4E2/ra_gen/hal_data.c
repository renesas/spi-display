/* generated HAL source file - do not edit */
#include "hal_data.h"
dtc_instance_ctrl_t g_transfer1_ctrl;

#if (BSP_CFG_DCACHE_ENABLED) && (1 == 1)
const transfer_info_t g_transfer1_user_config_info =
{
    .transfer_settings_word_b.dest_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED,
    .transfer_settings_word_b.repeat_area    = TRANSFER_REPEAT_AREA_DESTINATION,
    .transfer_settings_word_b.irq            = TRANSFER_IRQ_END,
    .transfer_settings_word_b.chain_mode     = TRANSFER_CHAIN_MODE_DISABLED,
    .transfer_settings_word_b.src_addr_mode  = TRANSFER_ADDR_MODE_FIXED,
    .transfer_settings_word_b.size           = TRANSFER_SIZE_1_BYTE,
    .transfer_settings_word_b.mode           = TRANSFER_MODE_NORMAL,
    .p_dest                                  = (void *) NULL,
    .p_src                                   = (void const *) NULL,
    .num_blocks                              = (uint16_t) 0,
    .length                                  = (uint16_t) 0,
};
#endif

#if BSP_CFG_DCACHE_ENABLED
    #if (1 > 0)
    transfer_info_t g_transfer1_info_fsp_nocache[1] DTC_TRANSFER_INFO_ALIGNMENT;
    #else
    /* User must call api::reconfigure before enable DTC transfer. */
    #endif
#else
    #if (1 == 1)
    transfer_info_t g_transfer1_info DTC_TRANSFER_INFO_ALIGNMENT =
    {
        .transfer_settings_word_b.dest_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED,
        .transfer_settings_word_b.repeat_area    = TRANSFER_REPEAT_AREA_DESTINATION,
        .transfer_settings_word_b.irq            = TRANSFER_IRQ_END,
        .transfer_settings_word_b.chain_mode     = TRANSFER_CHAIN_MODE_DISABLED,
        .transfer_settings_word_b.src_addr_mode  = TRANSFER_ADDR_MODE_FIXED,
        .transfer_settings_word_b.size           = TRANSFER_SIZE_1_BYTE,
        .transfer_settings_word_b.mode           = TRANSFER_MODE_NORMAL,
        .p_dest                                  = (void *) NULL,
        .p_src                                   = (void const *) NULL,
        .num_blocks                              = (uint16_t) 0,
        .length                                  = (uint16_t) 0,
    };
    #elif (1 > 1)
    /* User is responsible to initialize the array. */
    transfer_info_t g_transfer1_info[1] DTC_TRANSFER_INFO_ALIGNMENT;
    #else
    /* User must call api::reconfigure before enable DTC transfer. */
    #endif
#endif

const dtc_extended_cfg_t g_transfer1_cfg_extend =
{
    .activation_source   = VECTOR_NUMBER_SCI9_RXI,

#if BSP_CFG_DCACHE_ENABLED
    #if (1 == 1)
        .p_user_config_info =  &g_transfer1_user_config_info,
    #else
        .p_user_config_info = NULL,
    #endif
#else
    /* p_user_config_info not present. */
#endif
};

const transfer_cfg_t g_transfer1_cfg =
{
#if BSP_CFG_DCACHE_ENABLED
    #if (1 > 0)
        .p_info              = g_transfer1_info_fsp_nocache,
    #else
        .p_info = NULL,
    #endif
#else
    #if (1 == 1)
        .p_info              = &g_transfer1_info,
    #elif (1 > 1)
        .p_info              = g_transfer1_info,
    #else
        .p_info = NULL,
    #endif
#endif
    .p_extend            = &g_transfer1_cfg_extend,
};

/* Instance structure to use this module. */
const transfer_instance_t g_transfer1 =
{
    .p_ctrl        = &g_transfer1_ctrl,
    .p_cfg         = &g_transfer1_cfg,
    .p_api         = &g_transfer_on_dtc
};
dtc_instance_ctrl_t g_transfer0_ctrl;

#if (BSP_CFG_DCACHE_ENABLED) && (1 == 1)
const transfer_info_t g_transfer0_user_config_info =
{
    .transfer_settings_word_b.dest_addr_mode = TRANSFER_ADDR_MODE_FIXED,
    .transfer_settings_word_b.repeat_area    = TRANSFER_REPEAT_AREA_SOURCE,
    .transfer_settings_word_b.irq            = TRANSFER_IRQ_END,
    .transfer_settings_word_b.chain_mode     = TRANSFER_CHAIN_MODE_DISABLED,
    .transfer_settings_word_b.src_addr_mode  = TRANSFER_ADDR_MODE_INCREMENTED,
    .transfer_settings_word_b.size           = TRANSFER_SIZE_1_BYTE,
    .transfer_settings_word_b.mode           = TRANSFER_MODE_NORMAL,
    .p_dest                                  = (void *) NULL,
    .p_src                                   = (void const *) NULL,
    .num_blocks                              = (uint16_t) 0,
    .length                                  = (uint16_t) 0,
};
#endif

#if BSP_CFG_DCACHE_ENABLED
    #if (1 > 0)
    transfer_info_t g_transfer0_info_fsp_nocache[1] DTC_TRANSFER_INFO_ALIGNMENT;
    #else
    /* User must call api::reconfigure before enable DTC transfer. */
    #endif
#else
    #if (1 == 1)
    transfer_info_t g_transfer0_info DTC_TRANSFER_INFO_ALIGNMENT =
    {
        .transfer_settings_word_b.dest_addr_mode = TRANSFER_ADDR_MODE_FIXED,
        .transfer_settings_word_b.repeat_area    = TRANSFER_REPEAT_AREA_SOURCE,
        .transfer_settings_word_b.irq            = TRANSFER_IRQ_END,
        .transfer_settings_word_b.chain_mode     = TRANSFER_CHAIN_MODE_DISABLED,
        .transfer_settings_word_b.src_addr_mode  = TRANSFER_ADDR_MODE_INCREMENTED,
        .transfer_settings_word_b.size           = TRANSFER_SIZE_1_BYTE,
        .transfer_settings_word_b.mode           = TRANSFER_MODE_NORMAL,
        .p_dest                                  = (void *) NULL,
        .p_src                                   = (void const *) NULL,
        .num_blocks                              = (uint16_t) 0,
        .length                                  = (uint16_t) 0,
    };
    #elif (1 > 1)
    /* User is responsible to initialize the array. */
    transfer_info_t g_transfer0_info[1] DTC_TRANSFER_INFO_ALIGNMENT;
    #else
    /* User must call api::reconfigure before enable DTC transfer. */
    #endif
#endif

const dtc_extended_cfg_t g_transfer0_cfg_extend =
{
    .activation_source   = VECTOR_NUMBER_SCI9_TXI,

#if BSP_CFG_DCACHE_ENABLED
    #if (1 == 1)
        .p_user_config_info =  &g_transfer0_user_config_info,
    #else
        .p_user_config_info = NULL,
    #endif
#else
    /* p_user_config_info not present. */
#endif
};

const transfer_cfg_t g_transfer0_cfg =
{
#if BSP_CFG_DCACHE_ENABLED
    #if (1 > 0)
        .p_info              = g_transfer0_info_fsp_nocache,
    #else
        .p_info = NULL,
    #endif
#else
    #if (1 == 1)
        .p_info              = &g_transfer0_info,
    #elif (1 > 1)
        .p_info              = g_transfer0_info,
    #else
        .p_info = NULL,
    #endif
#endif
    .p_extend            = &g_transfer0_cfg_extend,
};

/* Instance structure to use this module. */
const transfer_instance_t g_transfer0 =
{
    .p_ctrl        = &g_transfer0_ctrl,
    .p_cfg         = &g_transfer0_cfg,
    .p_api         = &g_transfer_on_dtc
};
sci_spi_instance_ctrl_t g_spi_display_ctrl;

/** SPI extended configuration */
const sci_spi_extended_cfg_t g_spi_display_cfg_extend =
{
    .clk_div = {
        /* Actual calculated bitrate: 25000000. */ .cks = 0, .brr = 0, .mddr = 0,
    }
};

const spi_cfg_t g_spi_display_cfg =
{
    .channel         = 9,
    .operating_mode  = SPI_MODE_MASTER,
    .clk_phase       = SPI_CLK_PHASE_EDGE_ODD,
    .clk_polarity    = SPI_CLK_POLARITY_LOW,
    .mode_fault      = SPI_MODE_FAULT_ERROR_DISABLE,
    .bit_order       = SPI_BIT_ORDER_MSB_FIRST,
#define RA_NOT_DEFINED (1)
#if (RA_NOT_DEFINED == g_transfer0)
    .p_transfer_tx   = NULL,
#else
    .p_transfer_tx   = &g_transfer0,
#endif
#if (RA_NOT_DEFINED == g_transfer1)
    .p_transfer_rx   = NULL,
#else
    .p_transfer_rx   = &g_transfer1,
#endif
#undef RA_NOT_DEFINED
    .p_callback      = spi_display_callback,
    .p_context       = NULL,
    .rxi_irq         = VECTOR_NUMBER_SCI9_RXI,
    .txi_irq         = VECTOR_NUMBER_SCI9_TXI,
    .tei_irq         = VECTOR_NUMBER_SCI9_TEI,
    .eri_irq         = VECTOR_NUMBER_SCI9_ERI,
    .rxi_ipl         = (12),
    .txi_ipl         = (12),
    .tei_ipl         = (12),
    .eri_ipl         = (12),
    .p_extend        = &g_spi_display_cfg_extend,
};
/* Instance structure to use this module. */
const spi_instance_t g_spi_display =
{
    .p_ctrl          = &g_spi_display_ctrl,
    .p_cfg           = &g_spi_display_cfg,
    .p_api           = &g_spi_on_sci
};
void g_hal_init(void) {
g_common_init();
}
