/***********************************************************************************************************************
 * File Name    : rs_spi_display.c
 * Description  : Contains pre-set configuration settings for fpb-ra4e2.
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

/* INTERNAL DATA */

static volatile bool g_transfer_complete = false; //SPI transfer complete flag

static const uint16_t g_color_bar_lut[RS_SPI_DISPLAY_NUM_DEF_COLORS] = //color bar look up table
{
    RS_SPI_DISPLAY_RGB565_WHITE,
    RS_SPI_DISPLAY_RGB565_YELLOW,
    RS_SPI_DISPLAY_RGB565_CYAN,
    RS_SPI_DISPLAY_RGB565_GREEN,
    RS_SPI_DISPLAY_RGB565_PURPLE,
    RS_SPI_DISPLAY_RGB565_RED,
    RS_SPI_DISPLAY_RGB565_BLUE,
    RS_SPI_DISPLAY_RGB565_BLACK
};

/* INTERNAL FUNCTIONS */

/***********************************************************************************************************************
 * @brief Changes the state of an I/O pin.
 *
 * @param[in] pin    I/O pin to modify.
 * @param[in] state  State to set the I/O pin to.
 **********************************************************************************************************************/
static void rs_spi_display_pin_set(bsp_io_port_pin_t pin, bsp_io_level_t state)
{
    R_BSP_PinAccessEnable();
    R_BSP_PinWrite(pin, state);
    R_BSP_PinAccessDisable();
}

/***********************************************************************************************************************
 * @brief Waits for the SPI transfer to complete.
 *
 * @retval FSP_SUCCESS      SPI transfer completed successfully.
 * @retval FSP_ERR_TIMEOUT  SPI transfer did not complete before the timeout expired.
 **********************************************************************************************************************/
static fsp_err_t rs_spi_display_wait_tx_complete(void)
{
    uint32_t timeout = RS_SPI_DISPLAY_TRANSFER_TIMEOUT;

    while ((!g_transfer_complete) && timeout)
    {
        timeout--;
    }

    if (0U == timeout)
    {
        return FSP_ERR_TIMEOUT;
    }

    g_transfer_complete = false;

    return FSP_SUCCESS;
}

/***********************************************************************************************************************
 * @brief Writes a single byte of data to the display over SPI.
 *
 * @param[in] p_spi_display_ctrl  Pointer to the SPI display control structure.
 * @param[in] data                Data byte to write.
 *
 * @retval FSP_SUCCESS  Data byte written successfully.
 * @return              Error code returned by the SPI write or transfer wait operation.
 *
 * @note The DC line must be set to data mode before calling this function.
 **********************************************************************************************************************/
static fsp_err_t rs_spi_display_write_data_byte(rs_spi_display_ctrl_t * p_spi_display_ctrl, uint8_t data)
{
    fsp_err_t err = FSP_SUCCESS;

    err = R_SCI_SPI_Write(p_spi_display_ctrl->spi_bus.p_ctrl,
                          &data,
                          sizeof(data),
                          SPI_BIT_WIDTH_8_BITS);
    if(err) return err;

    /* Wait for SPI tx. */
    err = rs_spi_display_wait_tx_complete();
    if(err) return err;

    return err;
}

/* R_SCI_SPI Module Callback *\*/

/***********************************************************************************************************************
 * @brief SPI callback that sets the transfer complete flag.
 *
 * @param[in] p_args  Pointer to the SPI callback arguments.
 **********************************************************************************************************************/
void spi_display_callback (spi_callback_args_t * p_args)
{
    switch (p_args->event)
    {
        case SPI_EVENT_TRANSFER_COMPLETE:
            g_transfer_complete = true;
            break;

        default:
            break;
    }

}

/* RS_SPI_DISPLAY LAYER */

/***********************************************************************************************************************
 * @brief Opens and initializes the SPI display layer.
 *
 * @param[in,out] p_spi_display_ctrl     Pointer to the SPI display control structure.
 * @param[in]     p_external_display_cfg Pointer to the external display device configuration.
 *
 * @retval FSP_SUCCESS             SPI display layer opened successfully.
 * @retval FSP_ERR_INVALID_POINTER Invalid pointer provided.
 * @retval FSP_ERR_ALREADY_OPEN    SPI display layer is already open.
 * @retval FSP_ERR_INVALID_ARGUMENT Invalid display configuration.
 * @return                          Error code returned by the SPI driver.
 **********************************************************************************************************************/
fsp_err_t rs_spi_display_Open(rs_spi_display_ctrl_t *p_spi_display_ctrl, const rs_spi_display_device_cfg_t *p_external_display_cfg)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Valid pointer check. */
    FSP_ERROR_RETURN(NULL != p_spi_display_ctrl, FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN(NULL != p_external_display_cfg, FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN(NULL != p_external_display_cfg->p_display_init_sequence, FSP_ERR_INVALID_POINTER);
    /* Open SPI display layer check. */
    FSP_ERROR_RETURN(p_spi_display_ctrl->open == false, FSP_ERR_ALREADY_OPEN);
    /* Signal level check. */
    FSP_ERROR_RETURN(p_external_display_cfg->reset_active_lvl !=  p_external_display_cfg->reset_inactive_lvl, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(p_external_display_cfg->cs_active_lvl !=  p_external_display_cfg->cs_inactive_lvl, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(p_external_display_cfg->data_lvl !=  p_external_display_cfg->command_lvl, FSP_ERR_INVALID_ARGUMENT);
    /* Resolution check. */
    FSP_ERROR_RETURN(p_external_display_cfg->canvas_x_resolution >= RS_SPI_DISPLAY_MIN_X_RES, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(p_external_display_cfg->canvas_x_resolution <= RS_SPI_DISPLAY_MAX_X_RES, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(p_external_display_cfg->canvas_y_resolution >= RS_SPI_DISPLAY_MIN_Y_RES, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(p_external_display_cfg->canvas_y_resolution <= RS_SPI_DISPLAY_MAX_Y_RES, FSP_ERR_INVALID_ARGUMENT);

    /* Set globals.*/
    g_transfer_complete = false;

    /* Assign the external device configuration to the control block. */
    p_spi_display_ctrl->p_device = p_external_display_cfg;

    p_spi_display_ctrl->canvas_pixel_count = (uint32_t) (p_external_display_cfg->canvas_x_resolution
                                                            * p_external_display_cfg->canvas_y_resolution);

    /* Ensure CS is inactive. */
    rs_spi_display_pin_set(p_spi_display_ctrl->p_device->chip_select_pinout, p_spi_display_ctrl->p_device->cs_inactive_lvl);

    /* Configures and initializes SPI bus. */
    err = R_SCI_SPI_Open(p_spi_display_ctrl->spi_bus.p_ctrl ,p_spi_display_ctrl->spi_bus.p_cfg );
    if(err) return err;

    p_spi_display_ctrl->open = true;

    return err;
}

/***********************************************************************************************************************
 * @brief Closes the SPI display layer.
 *
 * @param[in,out] p_spi_display_ctrl  Pointer to the SPI display control structure.
 *
 * @retval FSP_SUCCESS              SPI display layer closed successfully.
 * @retval FSP_ERR_INVALID_POINTER  Invalid control pointer provided.
 * @retval FSP_ERR_NOT_OPEN         SPI display layer is not open.
 * @return                          Error code returned by the SPI driver.
 **********************************************************************************************************************/
fsp_err_t rs_spi_display_Close(rs_spi_display_ctrl_t *p_spi_display_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;

    FSP_ERROR_RETURN(NULL != p_spi_display_ctrl, FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN(true == p_spi_display_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Ensure CS is inactive. */
    rs_spi_display_pin_set(p_spi_display_ctrl->p_device->chip_select_pinout, p_spi_display_ctrl->p_device->cs_inactive_lvl);

    /* De-initializes SPI bus. */
    err = R_SCI_SPI_Close(p_spi_display_ctrl->spi_bus.p_ctrl );
    if(err) return err;

    p_spi_display_ctrl->open = false;

    return err;
}

/***********************************************************************************************************************
 * @brief Resets the external display and sends the user-defined initialization sequence.
 *
 * @param[in] p_spi_display_ctrl  Pointer to the SPI display control structure.
 * @param[in] addr                Pointer to the display initialization sequence.
 *
 * @retval FSP_SUCCESS  Display initialization sequence sent successfully.
 * @return              Error code returned by the SPI command or data transfer operation.
 **********************************************************************************************************************/
fsp_err_t rs_spi_display_SendInitSequence( rs_spi_display_ctrl_t *p_spi_display_ctrl, const uint8_t * addr)
{
    volatile uint8_t num_commands, num_args, args_delay, command, data_arg, use_delay, delay_per = 0;
    fsp_err_t err = FSP_SUCCESS;

    /* Cycle display through hardware reset. */
    rs_spi_display_pin_set(p_spi_display_ctrl->p_device->reset_pinout, p_spi_display_ctrl->p_device->reset_active_lvl);
    R_BSP_SoftwareDelay(p_spi_display_ctrl->p_device->reset_delay_ms, BSP_DELAY_UNITS_MILLISECONDS);

    rs_spi_display_pin_set(p_spi_display_ctrl->p_device->reset_pinout, p_spi_display_ctrl->p_device->reset_inactive_lvl);
    R_BSP_SoftwareDelay(p_spi_display_ctrl->p_device->reset_delay_ms, BSP_DELAY_UNITS_MILLISECONDS);

    /* Chip Select Active */
    rs_spi_display_pin_set(p_spi_display_ctrl->p_device->chip_select_pinout, p_spi_display_ctrl->p_device->cs_active_lvl);

    /* Run through Initialization Sequence */

    /* Get the number of commands in the sequence*/
    num_commands = *addr;
    ++addr;

    /* Send each command in the sequence. After, if needed, send any data args or delay.*/
    while(num_commands--)
    {
        /* Send command */
        command = *addr;
        err = rs_spi_display_SendCommand(p_spi_display_ctrl, command);
        if(err) return err;
        ++addr;

        /* Get the combined input holding the number of data arguments and delay flag. */
        args_delay = *addr;
        num_args = args_delay & ~(RS_SPI_DISPLAY_USE_DELAY);
        use_delay = args_delay & RS_SPI_DISPLAY_USE_DELAY;
        ++addr;

        /* Send the number of data arguments specified for the command. */
        while(num_args--)
        {
            data_arg = *addr;
            err = rs_spi_display_SendData(p_spi_display_ctrl, data_arg);
            if(err) return err;
            ++addr;
        }

        /* Add a delay if specified for the command. */
        if(use_delay)
        {
            delay_per = *addr;
            ++addr;
            R_BSP_SoftwareDelay(delay_per, BSP_DELAY_UNITS_MILLISECONDS);
        }

    }

    /* Chip Select Inactive */
    rs_spi_display_pin_set(p_spi_display_ctrl->p_device->chip_select_pinout, p_spi_display_ctrl->p_device->cs_inactive_lvl);

    return err;
}

/***********************************************************************************************************************
 * @brief Sends an 8-bit data packet to the external display.
 *
 * @param[in] p_spi_display_ctrl  Pointer to the SPI display control structure.
 * @param[in] data                8-bit data value to send.
 *
 * @retval FSP_SUCCESS  Data sent successfully.
 * @return              Error code returned by the SPI write or transfer wait operation.
 **********************************************************************************************************************/
fsp_err_t rs_spi_display_SendData(rs_spi_display_ctrl_t *p_spi_display_ctrl, uint8_t data)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Set DC pin to data level. */
    rs_spi_display_pin_set(p_spi_display_ctrl->p_device->data_command_pinout, p_spi_display_ctrl->p_device->data_lvl);

    /* Chip Select active.*/
    rs_spi_display_pin_set(p_spi_display_ctrl->p_device->chip_select_pinout, p_spi_display_ctrl->p_device->cs_active_lvl);

    /* Send data packet. */
    err = R_SCI_SPI_Write(p_spi_display_ctrl->spi_bus.p_ctrl, &data, sizeof(data), SPI_BIT_WIDTH_8_BITS);
    if(err) return err;

    /* Wait for SPI tx. */
    err = rs_spi_display_wait_tx_complete();
    if(err) return err;

    /* Chip Select Inactive */
    rs_spi_display_pin_set(p_spi_display_ctrl->p_device->chip_select_pinout, p_spi_display_ctrl->p_device->cs_inactive_lvl);

    return err;
}

/***********************************************************************************************************************
 * @brief Sends an 8-bit command packet to the external display.
 *
 * @param[in] p_spi_display_ctrl  Pointer to the SPI display control structure.
 * @param[in] command             8-bit command value to send.
 *
 * @retval FSP_SUCCESS  Command sent successfully.
 * @return              Error code returned by the SPI write or transfer wait operation.
 **********************************************************************************************************************/
fsp_err_t rs_spi_display_SendCommand(rs_spi_display_ctrl_t *p_spi_display_ctrl, uint8_t command)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Set DC pin to command level. */
    rs_spi_display_pin_set(p_spi_display_ctrl->p_device->data_command_pinout,  p_spi_display_ctrl->p_device->command_lvl);

    /* Chip Select active.*/
    rs_spi_display_pin_set(p_spi_display_ctrl->p_device->chip_select_pinout, p_spi_display_ctrl->p_device->cs_active_lvl);

    /* Send command packet. */
    err = R_SCI_SPI_Write(p_spi_display_ctrl->spi_bus.p_ctrl, &command, sizeof(command), SPI_BIT_WIDTH_8_BITS);
    if(err) return err;

    /* Wait for SPI tx. */
    err = rs_spi_display_wait_tx_complete();
    if(err) return err;

    /* Chip Select Inactive */
    rs_spi_display_pin_set(p_spi_display_ctrl->p_device->chip_select_pinout, p_spi_display_ctrl->p_device->cs_inactive_lvl);

    return err;
}

/***********************************************************************************************************************
 * @brief Fills the display canvas with a solid 16-bit RGB565 color.
 *
 * @param[in] p_spi_display_ctrl  Pointer to the SPI display control structure.
 * @param[in] color               16-bit RGB565 color value.
 *
 * @retval FSP_SUCCESS  Display filled successfully.
 * @return              Error code returned by the SPI command or data transfer operation.
 *
 * @note The RGB565 color value is transmitted as two 8-bit packets, most significant byte first.
 **********************************************************************************************************************/
fsp_err_t rs_spi_display_FillScreen(rs_spi_display_ctrl_t *p_spi_display_ctrl, uint16_t color)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Send Command: Write to GDDRAM. */
    err = rs_spi_display_SendCommand(p_spi_display_ctrl, p_spi_display_ctrl->p_device->write_gddram_command);
    if(err) return err;

    /* Retrieve canvas resolution. */
    uint32_t canvas_pixels = p_spi_display_ctrl->canvas_pixel_count;

    /* Set DC line to data level. */
    rs_spi_display_pin_set(p_spi_display_ctrl->p_device->data_command_pinout, p_spi_display_ctrl->p_device->data_lvl);

    /* Chip Select active.*/
    rs_spi_display_pin_set(p_spi_display_ctrl->p_device->chip_select_pinout, p_spi_display_ctrl->p_device->cs_active_lvl);

    uint8_t upper = (uint8_t) (color >> 8);
    uint8_t lower = (uint8_t) color;

    /* Send color over SPI bus for each pixel. */
    while(canvas_pixels --)
    {
        err = rs_spi_display_write_data_byte(p_spi_display_ctrl, upper);
        if (err) return err;

        err = rs_spi_display_write_data_byte(p_spi_display_ctrl, lower);
        if (err) return err;
    }

    /* Chip Select Inactive */
    rs_spi_display_pin_set(p_spi_display_ctrl->p_device->chip_select_pinout, p_spi_display_ctrl->p_device->cs_inactive_lvl);

    return err;
}

/***********************************************************************************************************************
 * @brief Draws horizontal colored bars across the display using the default color lookup table.
 *
 * @param[in] p_spi_display_ctrl  Pointer to the SPI display control structure.
 *
 * @retval FSP_SUCCESS  Colored bars drawn successfully.
 * @return              Error code returned by the SPI command or data transfer operation.
 *
 * @note RGB565 color values are transmitted as two 8-bit packets, most significant byte first.
 **********************************************************************************************************************/
fsp_err_t rs_spi_display_DrawColoredBars(rs_spi_display_ctrl_t *p_spi_display_ctrl)
{
    uint16_t bar_height = 0;
    fsp_err_t err = FSP_SUCCESS;

    bar_height = p_spi_display_ctrl->p_device->canvas_y_resolution / RS_SPI_DISPLAY_NUM_DEF_COLORS;

    /* Send Command: Write to GDDRAM. */
    err = rs_spi_display_SendCommand(p_spi_display_ctrl, p_spi_display_ctrl->p_device->write_gddram_command);
    if(err) return err;

    /* Set DC line to data level. */
    rs_spi_display_pin_set(p_spi_display_ctrl->p_device->data_command_pinout,
                           p_spi_display_ctrl->p_device->data_lvl);

    /* Chip Select active.*/
    rs_spi_display_pin_set(p_spi_display_ctrl->p_device->chip_select_pinout,
                           p_spi_display_ctrl->p_device->cs_active_lvl);

    for (int color_idx = 0; color_idx < RS_SPI_DISPLAY_NUM_DEF_COLORS; color_idx++)
    {
        uint16_t color = g_color_bar_lut[color_idx];

        uint8_t upper = (uint8_t) (color >> 8);
        uint8_t lower = (uint8_t) color;

        /* Write each row of the colored bar. */
        for (uint32_t row_idx = 0; row_idx < bar_height; row_idx++)
        {
            /* Write each pixel in the row. */
            for (uint16_t column_idx = 0; column_idx < p_spi_display_ctrl->p_device->canvas_x_resolution; column_idx++)
            {
              err = rs_spi_display_write_data_byte(p_spi_display_ctrl, upper);
              if (err) return err;

              err = rs_spi_display_write_data_byte(p_spi_display_ctrl, lower);
              if (err) return err;
            }
        }
    }

    /* Chip Select Inactive */
    rs_spi_display_pin_set(p_spi_display_ctrl->p_device->chip_select_pinout, p_spi_display_ctrl->p_device->cs_inactive_lvl);

    return err;
}

/***********************************************************************************************************************
 * @brief Draws a framebuffer to the external display.
 *
 * @param[in] p_spi_display_ctrl  Pointer to the SPI display control structure.
 * @param[in] p_framebuffer       Pointer to the RGB565 framebuffer.
 *
 * @retval FSP_SUCCESS  Framebuffer drawn successfully.
 * @return              Error code returned by the SPI command or data transfer operation.
 *
 * @note The framebuffer must use RGB565 encoding and match the configured display canvas resolution.
 *       Each pixel is transmitted as two 8-bit packets, most significant byte first.
 **********************************************************************************************************************/
fsp_err_t rs_spi_display_DrawFramebuffer( rs_spi_display_ctrl_t *p_spi_display_ctrl, const uint16_t * p_framebuffer)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Send Command: Write to GDDRAM. */
    err = rs_spi_display_SendCommand(p_spi_display_ctrl, p_spi_display_ctrl->p_device->write_gddram_command);
    if(err) return err;

    /* Set DC line to data level. */
    rs_spi_display_pin_set(p_spi_display_ctrl->p_device->data_command_pinout, p_spi_display_ctrl->p_device->data_lvl);

    /* Chip Select active.*/
    rs_spi_display_pin_set(p_spi_display_ctrl->p_device->chip_select_pinout, p_spi_display_ctrl->p_device->cs_active_lvl);

    for(uint32_t i = 0; i < p_spi_display_ctrl->canvas_pixel_count; ++i )
    {
        uint16_t pixel = p_framebuffer[i];

        uint8_t upper = (uint8_t)(pixel >> 8);
        uint8_t lower = (uint8_t) pixel;

        err = rs_spi_display_write_data_byte(p_spi_display_ctrl, upper);
        if (err) return err;

        err = rs_spi_display_write_data_byte(p_spi_display_ctrl, lower);
        if (err) return err;
    }

    /* Chip Select Inactive */
    rs_spi_display_pin_set(p_spi_display_ctrl->p_device->chip_select_pinout, p_spi_display_ctrl->p_device->cs_inactive_lvl);


    return err;
}
