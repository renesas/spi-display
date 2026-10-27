/***********************************************************************************************************************
 * File Name    : rs_spi_display_ST7735SV.c
 * Description  : Contains library of commands, signal levels, and delays for the ST7735SV IC.
 **********************************************************************************************************************/
/***********************************************************************************************************************
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/

#ifndef RS_SPI_DISPLAY_RS_SPI_DISPLAY_ST7735SV_H_
#define RS_SPI_DISPLAY_RS_SPI_DISPLAY_ST7735SV_H_

/* ST7735SV Commands */
#define ST7735SV_NOP        (0x00)      //No Operation
#define ST7735SV_SWRESET    (0x01)      //Software Reset
#define ST7735SV_RDDID      (0x04)      //Read Display ID
#define ST7735SV_RDDST      (0x09)      //Read Display Status
#define ST7735SV_RDDPM      (0x0A)      //Read Display Power Mode
#define ST7735SV_RDDMADCTL  (0x0B)      //Read Display MADCTL
#define ST7735SV_RDDCOLMOD  (0x0C)      //Read Display Pixel Format
#define ST7735SV_RDDIM      (0x0D)      //Read Display Image Mode
#define ST7735SV_RDDSM      (0x0E)      //Read Display Signal Mode
#define ST7735SV_RDDSDR     (0x0F)      //Read Display Self-Diagnostic

#define ST7735SV_SLPIN      (0x10)      //Sleep In & Booster Off
#define ST7735SV_SLPOUT     (0x11)      //Sleep Out & Booster On
#define ST7735SV_PTLON      (0x12)      //Partial Mode On
#define ST7735SV_NORON      (0x13)      //Partial Off (Normal)

#define ST7735SV_INVOFF     (0x20)      //Display Inversion Off (Normal)
#define ST7735SV_INVON      (0x21)      //Display Inversion On
#define ST7735SV_GAMSET     (0x26)      //Gamma Curve Select
#define ST7735SV_DISPOFF    (0x28)      //Display Off
#define ST7735SV_DISPON     (0x29)      //Display On
#define ST7735SV_CASET      (0x2A)      //Column Address Set
#define ST7735SV_RASET      (0x2B)      //Row Address Set
#define ST7735SV_RAMWR      (0x2C)      //Memory Write Data
#define ST7735SV_RGBSET     (0x2D)      //LUT for 4k,65k,262k Color Display
#define ST7735SV_RAMRD      (0x2E)      //Memory Read

#define ST7735SV_PTLAR      (0x30)      //Partial Start/End Address Set
#define ST7735SV_SCRLAR     (0x33)      //Scroll Area Set
#define ST7735SV_TEOFF      (0x34)      //Tearing Effect Line Off
#define ST7735SV_TEON       (0x35)      //Tearing Effect Mode Set & On
#define ST7735SV_MADCTL     (0x36)      //Memory Data Access Control
#define ST7735SV_VSCSAD     (0x37)      //Scroll Start Address of RAM
#define ST7735SV_IDMOFF     (0x38)      //Idle Mode Off
#define ST7735SV_IDMON      (0x39)      //Idle Mode On
#define ST7735SV_COLMOD     (0x3A)      //Interface Pixel Format

#define ST7735SV_RDID1      (0xDA)      //Read ID1
#define ST7735SV_RDID2      (0xDB)      //Read ID2
#define ST7735SV_RDID3      (0xDC)      //Read ID3

/* ST7735SV D/CX Signal Levels */
#define ST7735SV_DATA_LVL   (BSP_IO_LEVEL_HIGH)
#define ST7735SV_CMD_LVL    (BSP_IO_LEVEL_LOW)

/* ST7735SV CS Signal Levels */
#define ST7735SV_CS_SELECT_LVL      (BSP_IO_LEVEL_LOW)
#define ST7735SV_CS_DESELECT_LVL    (BSP_IO_LEVEL_HIGH)

/* ST7735SV RES Signal LEvels */
#define ST7735SV_RESET_ACTIVE_LVL     (BSP_IO_LEVEL_LOW)
#define ST7735SV_RESET_INACTIVE_LVL   (BSP_IO_LEVEL_HIGH)
#define ST7735SV_RESET_DELAY_MS     (120)


#endif /* RS_SPI_DISPLAY_RS_SPI_DISPLAY_ST7735SV_H_ */
