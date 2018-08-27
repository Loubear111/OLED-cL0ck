/**
  ******************************************************************************
  * @file    lcd.h
  * @author  Louis Barrett
  * @brief   Header file for lcd.c
  *          
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2018 Louis Barrett
  * Email: louisbarrett98@gmail.com
  *
  * Permission is hereby granted, free of charge, to any person obtaining a copy
  * of this software and associated documentation files (the "Software"), to deal
  * in the Software without restriction, including without limitation the rights
  * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  * copies of the Software, and to permit persons to whom the Software is
  * furnished to do so, subject to the following conditions:
  *
  * The above copyright notice and this permission notice shall be included in all
  * copies or substantial portions of the Software.
  *
  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  * SOFTWARE.
  *
  ******************************************************************************
  */

#include "stm32l0xx_hal.h"

// Definition for SPIx Pins
#define SPIx_PORT                           SPI1
#define SPIx_SCK_PIN                        GPIO_PIN_3
#define SPIx_SCK_GPIO_PORT                  GPIOB
#define SPIx_SCK_AF                         GPIO_AF0_SPI1
#define SPIx_MOSI_PIN                       GPIO_PIN_5
#define SPIx_MOSI_GPIO_PORT                 GPIOB
#define SPIx_MOSI_AF                        GPIO_AF0_SPI1
#define SPIx_CLK_ENABLE()                   __HAL_RCC_SPI1_CLK_ENABLE()
#define DMA1_CLK_ENABLE()                   __HAL_RCC_DMA1_CLK_ENABLE()
#define SPIx_SCK_GPIO_CLK_ENABLE()          __HAL_RCC_GPIOB_CLK_ENABLE()
#define SPIx_MOSI_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOB_CLK_ENABLE()

// LCD SPIO Pinouts
#define LCD_DC_GPIOPORT                     GPIOA
#define LCD_DC_GPIOPIN                      GPIO_PIN_11

#define LCD_CS_GPIOPORT                     GPIOA
#define LCD_CS_GPIOPIN                      GPIO_PIN_15

#define LCD_RESET_GPIOPORT                  GPIOB
#define LCD_RESET_GPIOPIN                   GPIO_PIN_1
  
void LCD_Init(void);

void LCD_Run(void);

/************************ (C) COPYRIGHT Louis Barrett *****END OF FILE****/

