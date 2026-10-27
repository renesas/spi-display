/***********************************************************************************************************************
 * File Name    : rs_spi_display_config.c
 * Description  : Contains configuration function definitions.
 **********************************************************************************************************************/
/***********************************************************************************************************************
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/

#include "rs_spi_display.h"
#if RS_SPI_DISPLAY_USE_PRESET_CFG   //Use pre-set configuration for SPI Display
#include "rs_spi_display_data_fpb_ra4e2_TCXD015IWLON.h"
#else
#include "hal_data.h"
#endif


fsp_err_t rs_spi_display_ConfigGen(rs_spi_display_ctrl_t *p_spi_display_ctrl, const spi_instance_t * p_spi_display_bus)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Check parameters. */
    FSP_ERROR_RETURN(NULL != p_spi_display_ctrl, FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN(NULL != p_spi_display_bus, FSP_ERR_INVALID_POINTER);

    /* Clear configuration. */
    memset(&p_spi_display_ctrl->spi_bus_cfg, 0, sizeof(spi_cfg_t));
    memset(&p_spi_display_ctrl->spi_bus_cfg_extend, 0, sizeof(sci_spi_extended_cfg_t));

    /* Copy configurations from the SPI module instance into SRAM */
    memcpy(&p_spi_display_ctrl->spi_bus_cfg, p_spi_display_bus->p_cfg, sizeof(spi_cfg_t));
    memcpy(&p_spi_display_ctrl->spi_bus_cfg_extend, p_spi_display_bus->p_cfg->p_extend, sizeof(sci_spi_extended_cfg_t));

    /* Manually assign address of p_extend to the extended config in SRAM. */
    p_spi_display_ctrl->spi_bus_cfg.p_extend = (sci_spi_extended_cfg_t *) &p_spi_display_ctrl->spi_bus_cfg_extend;

    /* Build SPI wrapper. */
    p_spi_display_ctrl->spi_bus.p_ctrl = &p_spi_display_ctrl->spi_bus_ctrl;
    p_spi_display_ctrl->spi_bus.p_cfg = &p_spi_display_ctrl->spi_bus_cfg;
    p_spi_display_ctrl->spi_bus.p_api = p_spi_display_bus->p_api;

    return err;
}

fsp_err_t rs_spi_display_ConfigCheck(rs_spi_display_ctrl_t *p_spi_display_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Check parameters. */
    FSP_ERROR_RETURN(NULL != p_spi_display_ctrl, FSP_ERR_INVALID_POINTER);

    /* Ensure that the ConfigGen operations were successful. */
    FSP_ERROR_RETURN(p_spi_display_ctrl->spi_bus.p_ctrl == &p_spi_display_ctrl->spi_bus_ctrl, FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN(p_spi_display_ctrl->spi_bus.p_cfg == &p_spi_display_ctrl->spi_bus_cfg, FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN(p_spi_display_ctrl->spi_bus_cfg.p_extend == &p_spi_display_ctrl->spi_bus_cfg_extend, FSP_ERR_INVALID_POINTER);

    return err;

}
