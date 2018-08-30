/**
  ******************************************************************************
  * @file    lcd.c
  * @author  Louis Barrett
  * @brief   Main control class for talking to the lcd OLED display
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
  
#include "lcd.h"
#include "ugui.h"
#include "rtc.h"
#include "stm32l0xx_hal_spi.h"
#include <stdbool.h>

// Width of LCD panel
#define LCD_WIDTH   128
// Height of LCD panel
#define LCD_HEIGHT  32
// Frame buffer size
#define FRAME_BUFFER_SIZE         (LCD_HEIGHT * (LCD_WIDTH / 8))

/* LCD pre-defined initialization commands */
#define LCD_CASET                  0x21
#define LCD_PASET                  0x22

#define LCD_SETCONTRAST             0x81
#define LCD_DISPLAYALLON_RESUME     0xA4
#define LCD_DISPLAYALLON            0xA5
#define LCD_NORMALDISPLAY           0xA6
#define LCD_INVERTDISPLAY           0xA7
#define LCD_DISPLAYOFF              0xAE
#define LCD_DISPLAYON               0xAF

#define LCD_SETDISPLAYOFFSET        0xD3
#define LCD_SETCOMPINS              0xDA

#define LCD_SETVCOMDETECT           0xDB

#define LCD_SETDISPLAYCLOCKDIV      0xD5
#define LCD_SETPRECHARGE            0xD9

#define LCD_SETMULTIPLEX            0xA8

#define LCD_SETLOWCOLUMN            0x00
#define LCD_SETHIGHCOLUMN           0x10

#define LCD_SETSTARTLINE            0x40

#define LCD_MEMORYMODE              0x20
#define LCD_COLUMNADDR              0x21
#define LCD_PAGEADDR                0x22

#define LCD_COMSCANINC              0xC0
#define LCD_COMSCANDEC              0xC8

#define LCD_SEGREMAP                0xA0

#define LCD_CHARGEPUMP              0x8D

#define LCD_EXTERNALVCC             0x1
#define LCD_SWITCHCAPVCC            0x2

/* SPI handler */
SPI_HandleTypeDef SpiHandler;

static uint8_t frameBuffer[FRAME_BUFFER_SIZE];
bool firstTime = true;

void WaitForSPI(void);
void delay(uint32_t milliseconds);
void LCD_PutChar(char chr, int16_t x, int16_t y, const UG_FONT *font);
void LCD_Print(char *s, uint16_t x, uint16_t y);
void LCD_Init_GPIO(void);
void WriteCmd(uint8_t command);
void LCD_SetCSPin(GPIO_PinState newState);
void LCD_SetDCPin(GPIO_PinState newState);
void LCD_SetResetPin(GPIO_PinState newState);
void LCD_Transfer(uint16_t * SrcAddress, uint16_t DataLength);

void WaitForSPI(void)
{
  while ((SPIx_PORT->SR & SPI_FLAG_BSY) == SPI_FLAG_BSY)
  {
  }
}

void delay(uint32_t milliseconds)
{
  uint32_t starttime = HAL_GetTick();
  while (HAL_GetTick() - starttime < milliseconds)
  {
    ;
  }
}

/* Adds a given string to the character buffer */
void PrintText(char *s, uint16_t x, uint16_t y, const UG_FONT *font, uint16_t fc, uint16_t bc)
{
  /* Pointer to each incremental character */
  while(*s != 0)
  {
    LCD_PutChar(*s, x, y, font);

    /* Move the next character over by the font width plus one so they don't touch */
    x += font->char_width + 1;
    s++;
  }
}

/* Adds given character to the frame buffer, this code is nearly identical to
   the PutChar function in ugui.c with some minor tweaks for this specific use */
void LCD_PutChar(char chr, int16_t x, int16_t y, const UG_FONT *font)
{
  uint16_t i,j,k;
  uint16_t xo;
  uint16_t yo;
  uint16_t c;
  uint16_t bn;
  uint8_t b;
  uint8_t bt;
  uint8_t* p;
  uint8_t* lut;
  
  bt = (uint8_t)chr;
  switch ( bt )
  {
    case 0xF6: bt = 0x94; break; // ö
    case 0xD6: bt = 0x99; break; // Ö
    case 0xFC: bt = 0x81; break; // ü
    case 0xDC: bt = 0x9A; break; // Ü
    case 0xE4: bt = 0x84; break; // ä
    case 0xC4: bt = 0x8E; break; // Ä
    case 0xB5: bt = 0xE6; break; // µ
    case 0xB0: bt = 0xF8; break; // °
  }

  yo = y;
  if (font->char_width == 0)
  {
    return;
  }
  
  bn = font->char_width;
  bn >>= 3;
  if ( font->char_width % 8 ) 
  {
    bn++;
  }
  
  // Pointer to start of font bit table
  p = font->p;
  lut = font->LUT;
  // If the given font has a LUT, use this for computing the character's pixel definition
  if(lut == NULL)
  {
    p+= bt * font->char_height * bn;
  }
  else
  {
    lut += bt - 1;
    p += *lut * font->char_height * bn;
  }
  
  for( j = 0; j < font->char_height; j++ )
  {
    xo = x;
    c = font->char_width;
    /* Iterate each row of pixels of the character */
    for( i = 0; i < bn; i++ )
    {
      b = *p++;
      for( k=0; (k<8) && c; k++ )
      {
        if( b & 0x01 )
        {
          // Print the pixel as a foreground (white)
          frameBuffer[xo + (yo/8)*LCD_WIDTH] |= (1 << (yo & 7));
        }
        else
        {
          // Print the pixel as a background (black)
          frameBuffer[xo + (yo/8)*LCD_WIDTH] &= ~(1 << (yo & 7));
        }
        b >>= 1;
        xo++;
        c--;
      }
    }
    yo++;
  }
  return;
}

void LCD_Init_GPIO(void)
{
  GPIO_InitTypeDef initStruct;
  
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  //DC Pin
  initStruct.Pin = LCD_DC_GPIOPIN;
  initStruct.Mode = GPIO_MODE_OUTPUT_PP;
  initStruct.Pull = GPIO_NOPULL;
  initStruct.Speed = GPIO_SPEED_LOW;
  HAL_GPIO_Init(LCD_DC_GPIOPORT, &initStruct);
    
  //CS Pin
  initStruct.Pin = LCD_CS_GPIOPIN;
  initStruct.Mode = GPIO_MODE_OUTPUT_PP;
  initStruct.Pull = GPIO_NOPULL;
  initStruct.Speed = GPIO_SPEED_LOW;
  HAL_GPIO_Init(LCD_CS_GPIOPORT, &initStruct);
  
  //Reset Pin
  initStruct.Pin =  LCD_RESET_GPIOPIN;
  initStruct.Mode = GPIO_MODE_OUTPUT_PP;
  initStruct.Pull = GPIO_NOPULL;
  initStruct.Speed = GPIO_SPEED_LOW;
  HAL_GPIO_Init(LCD_RESET_GPIOPORT, &initStruct);
}

void LCD_InitCommands()
{
  LCD_SetResetPin(GPIO_PIN_SET);
  delay(6);
  LCD_SetResetPin(GPIO_PIN_RESET);
  delay(6);
  LCD_SetResetPin(GPIO_PIN_SET);
  delay(6);
  
  WriteCmd(LCD_DISPLAYOFF);
  WriteCmd(LCD_SETDISPLAYCLOCKDIV);
  WriteCmd(0x80);
  
  WriteCmd(LCD_SETMULTIPLEX);
  WriteCmd(0x1F);
  
  WriteCmd(LCD_SETDISPLAYOFFSET);
  WriteCmd(0x00);
  WriteCmd(LCD_SETSTARTLINE | 0x00);
  WriteCmd(LCD_CHARGEPUMP);
  WriteCmd(0x14);
  
  WriteCmd(LCD_MEMORYMODE);
  WriteCmd(0x00);
  
  //To flip 180 degrees use "LCD_SEGREMAP | 0x01" and
  //"LCD_COMSCANDEC"
  //OR (if already set to above)
  //use "LCD_SEGREMAP | 0x00" and
  //"LCD_COMSCANINC"
  WriteCmd(LCD_SEGREMAP | 0x01);
  WriteCmd(LCD_COMSCANDEC);
  
  WriteCmd(LCD_SETCOMPINS);
  WriteCmd(0x02);
  WriteCmd(LCD_SETCONTRAST);
  WriteCmd(0x8F);
  
  WriteCmd(LCD_SETPRECHARGE);
  WriteCmd(0xF1);
  
  WriteCmd(LCD_SETVCOMDETECT);
  WriteCmd(0x40);
  WriteCmd(LCD_DISPLAYALLON_RESUME);
  WriteCmd(LCD_NORMALDISPLAY);
  
  WriteCmd(LCD_DISPLAYON);
}

void LCD_SPI_Init(void)
{
  /* Initialize SPI */
  SpiHandler.Instance                = SPIx_PORT;
  SpiHandler.Init.Mode               = SPI_MODE_MASTER;
  SpiHandler.Init.Direction          = SPI_DIRECTION_2LINES;
  SpiHandler.Init.DataSize           = SPI_DATASIZE_8BIT;
  SpiHandler.Init.CLKPolarity        = SPI_POLARITY_LOW;
  SpiHandler.Init.CLKPhase           = SPI_PHASE_1EDGE;
  SpiHandler.Init.NSS                = SPI_NSS_SOFT;
  SpiHandler.Init.BaudRatePrescaler  = SPI_BAUDRATEPRESCALER_2;
  SpiHandler.Init.FirstBit           = SPI_FIRSTBIT_MSB;
  SpiHandler.Init.TIMode             = SPI_TIMODE_DISABLED;
  SpiHandler.Init.CRCCalculation     = SPI_CRCCALCULATION_DISABLED;
  SpiHandler.Init.CRCPolynomial      = 7;
  //SpiHandler.hdmatx = &SPIDMAStruct;
  
  HAL_SPI_Init(&SpiHandler);
  __HAL_SPI_ENABLE(&SpiHandler);
}

/* HAL Level init taken from HAL libraries */
void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
  GPIO_InitTypeDef  GPIO_InitStruct;

  if (hspi->Instance == SPIx_PORT)
  {
    /*##-1- Enable peripherals and GPIO Clocks #################################*/
    /* Enable GPIO TX/RX clock */
    SPIx_SCK_GPIO_CLK_ENABLE();
    SPIx_MOSI_GPIO_CLK_ENABLE();
    /* Enable SPIx clock */
    SPIx_CLK_ENABLE();
    /* Enable DMA clock */
    DMA1_CLK_ENABLE();

    /*##-2- Configure peripheral GPIO ##########################################*/  
    /* SPI SCK GPIO pin configuration  */
    GPIO_InitStruct.Pin       = SPIx_SCK_PIN;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_NOPULL;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = SPIx_SCK_AF;
    HAL_GPIO_Init(SPIx_SCK_GPIO_PORT, &GPIO_InitStruct);
    
    /* SPI MOSI GPIO pin configuration  */
    GPIO_InitStruct.Pin       = SPIx_MOSI_PIN;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_NOPULL;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = SPIx_MOSI_AF;
    HAL_GPIO_Init(SPIx_MOSI_GPIO_PORT, &GPIO_InitStruct);

    /*##-4- Configure the NVIC for DMA #########################################*/ 
    /* NVIC configuration for DMA transfer complete interrupt (SPIx_TX) */
    HAL_NVIC_SetPriority(DMA1_Channel2_3_IRQn, 1, 1);
    HAL_NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);
  }
}

/* Used to fill a rectangle of a given color (black or white), primarily used
   to clear the screen. */
void FillRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, bool color)
{
  uint16_t count = 0;
  
  //Make sure SPI is not busy
  WaitForSPI();
  
  LCD_SetCSPin(GPIO_PIN_SET);
  LCD_SetCSPin(GPIO_PIN_RESET);

  //Fill the frame buffer with all 0's or all FF's to make the screen
  //white or black
  LCD_SetDCPin(GPIO_PIN_SET);
  if(color == 0)
  {
    for(; count < FRAME_BUFFER_SIZE; count++)
    {
      frameBuffer[count] = 0x00;
    }
  }
  if(color == 1)
  {
    for(; count < FRAME_BUFFER_SIZE; count++)
    {
      frameBuffer[count] = 0xFF;
    }
  }
}

void ClearScreen(bool color)
{
  FillRectangle(0, 0, LCD_WIDTH-1, LCD_HEIGHT-1, color);
}

void LCD_SetCSPin(GPIO_PinState newState)
{
  HAL_GPIO_WritePin(LCD_CS_GPIOPORT, LCD_CS_GPIOPIN, newState);
}

void LCD_SetDCPin(GPIO_PinState newState)
{
  HAL_GPIO_WritePin(LCD_DC_GPIOPORT, LCD_DC_GPIOPIN, newState);
}

void LCD_SetResetPin(GPIO_PinState newState)
{
  HAL_GPIO_WritePin(LCD_RESET_GPIOPORT, LCD_RESET_GPIOPIN, newState);
}

//Function used primarily to write initialization commands to the LCD
void WriteCmd(uint8_t command)
{
  uint8_t data[] = {command};
  
  WaitForSPI();
  
  LCD_SetCSPin(GPIO_PIN_SET);
  LCD_SetDCPin(GPIO_PIN_RESET);
  LCD_SetCSPin(GPIO_PIN_RESET);
  
  //HAL_SPI_Transmit_DMA(&SpiHandler, (uint8_t*)data, 1);
  HAL_SPI_Transmit(&SpiHandler, (uint8_t*)data, 1, 2000);

  WaitForSPI();
  LCD_SetCSPin(GPIO_PIN_SET);
}

/* Select the whole RAM buffer in the LCD memory to write/update
   the whole screen at once */
void drawScreen(void)
{
  WaitForSPI();
  
  LCD_SetCSPin(GPIO_PIN_SET);
  LCD_SetDCPin(GPIO_PIN_RESET);
  LCD_SetCSPin(GPIO_PIN_RESET);
  
  SPIx_PORT->DR = LCD_CASET;
  while(!(SPIx_PORT->SR & SPI_FLAG_TXE))
  {
  }
  WaitForSPI();
  SPIx_PORT->DR = 0x00;
  while(!(SPIx_PORT->SR & SPI_FLAG_TXE))
  {
  }
  WaitForSPI();
  SPIx_PORT->DR = 0x7F;
  while(!(SPIx_PORT->SR & SPI_FLAG_TXE))
  {
  }
  WaitForSPI();
  SPIx_PORT->DR = LCD_PASET;
  while(!(SPIx_PORT->SR & SPI_FLAG_TXE))
  {
  }
  WaitForSPI();
  SPIx_PORT->DR = 0x00;
  while(!(SPIx_PORT->SR & SPI_FLAG_TXE))
  {
  }
  WaitForSPI();
  SPIx_PORT->DR = 0x1F;

  WaitForSPI();

  LCD_SetDCPin(GPIO_PIN_SET);

  LCD_Transfer((uint16_t *)frameBuffer, FRAME_BUFFER_SIZE);
}

void LCD_Transfer(uint16_t * SrcAddress, uint16_t DataLength)
{
  /* Leaving DMA code here in case I want to use it in the future */
  
  // Set DMA to incriment the memory location
  //__HAL_DMA_DISABLE(&SPIDMAStruct);
  //SET_BIT(DMA1_Channel2->CCR, DMA_CCR_MINC);
  //__HAL_DMA_ENABLE(&SPIDMAStruct);

  //HAL_SPI_Transmit_DMA(&SpiHandler, (uint8_t *)SrcAddress, DataLength);
  HAL_SPI_Transmit(&SpiHandler, (uint8_t *)SrcAddress, DataLength, 1000);
}

void LCD_Init(void)
{
  LCD_Init_GPIO();
  LCD_SPI_Init();
  
  LCD_SetResetPin(GPIO_PIN_SET);
  LCD_SetCSPin(GPIO_PIN_SET);
  LCD_SetDCPin(GPIO_PIN_SET);
  
  delay(10);
  
  LCD_InitCommands();
  
  WaitForSPI();
  LCD_SetCSPin(GPIO_PIN_SET);
  
  delay(10);
  
  LCD_SetCSPin(GPIO_PIN_RESET);
  
  WaitForSPI();
  LCD_SetCSPin(GPIO_PIN_SET);
  
  delay(10);
  ClearScreen(0);
  
  delay(30);
}

void LCD_Run(void)
{
  static uint32_t lastScreenRefresh = 0;
  
  if (firstTime)
  {
    LCD_SetCSPin(GPIO_PIN_RESET);
    
    WaitForSPI();
    LCD_SetCSPin(GPIO_PIN_SET);
    
    LCD_Print("Hi", 0, 9);
    
    firstTime = false;
  }
  
  if (HAL_GetTick() - lastScreenRefresh >= 100)
  {
    LCD_Print((char *)RTC_GetTime(), 0, 9);
    lastScreenRefresh = HAL_GetTick();
    drawScreen();
  }
}

void LCD_Print(char *s, uint16_t x, uint16_t y)
{
  PrintText(s, x, y, &FONT_8X14, C_WHITE, C_BLACK);
}
/************************ (C) COPYRIGHT Louis Barrett *****END OF FILE****/
