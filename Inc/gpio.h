/**
  ******************************************************************************
  * @file    gpio.h
  * @author  Louis Barrett
  * @brief   Header file for gpio.c
  *          
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2019 Louis Barrett
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

//Define for debug LEDs
#define DEBUG_LED1_PIN								GPIO_PIN_13
#define DEBUG_LED1_PORT								GPIOA

//Define for buttons
#define BUTTON1_PIN										GPIO_PIN_14
#define BUTTON1_PORT									GPIOA

void DEBUG_LED1_SET(void);
void DEBUG_LED1_RESET(void);
void GPIO_Init(void);
void GPIO_Run(void);

/************************ (C) COPYRIGHT Louis Barrett *****END OF FILE****/
