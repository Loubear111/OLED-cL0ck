/**
  ******************************************************************************
  * @file    gpio.c
  * @author  Louis Barrett
  * @brief   Main class for controlling GPIO pins for buttons, LEDs, etc...
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

#include "gpio.h"

void GPIO_Init(void)
{
	GPIO_InitTypeDef initStruct;
	
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	/* BUTTON GPIO */
	initStruct.Pin = BUTTON1_PIN;
	initStruct.Mode = GPIO_MODE_INPUT;
	initStruct.Pull = GPIO_PULLDOWN;
	initStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	
	HAL_GPIO_Init(BUTTON1_PORT, &initStruct);

	/* LED GPIO */
	initStruct.Pin = DEBUG_LED1_PIN;
	initStruct.Mode = GPIO_MODE_OUTPUT_PP;
	initStruct.Pull = GPIO_PULLDOWN;
	initStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	
	HAL_GPIO_Init(DEBUG_LED1_PORT, &initStruct);
}

void GPIO_Run(void)
{
	static GPIO_PinState state = GPIO_PIN_RESET;
	
	if(HAL_GPIO_ReadPin(BUTTON1_PORT, BUTTON1_PIN) == GPIO_PIN_SET)
	{
		if(state == GPIO_PIN_RESET)
		{
			DEBUG_LED1_SET();
		}
		state = GPIO_PIN_SET;
	}
	else
	{
		if(state == GPIO_PIN_SET)
		{
			DEBUG_LED1_RESET();
		}
		state = GPIO_PIN_RESET;
	}
}

void DEBUG_LED1_SET(void)
{
		HAL_GPIO_WritePin(DEBUG_LED1_PORT, DEBUG_LED1_PIN, GPIO_PIN_SET);
}
void DEBUG_LED1_RESET(void)
{
		HAL_GPIO_WritePin(DEBUG_LED1_PORT, DEBUG_LED1_PIN, GPIO_PIN_RESET);
}

/************************ (C) COPYRIGHT Louis Barrett *****END OF FILE****/
