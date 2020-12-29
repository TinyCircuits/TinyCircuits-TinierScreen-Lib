/*
TinierScreen.h - Last modified 6 January 2020

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

Written by Ben Rose for TinyCircuits.

The latest version of this library can be found at https://TinyCircuits.com/
*/

#ifndef TinierScreen_h
#define TinierScreen_h

#include "Arduino.h"
#include "SPI.h"

#define TinierScreen042 72
#define TinierScreen069 96
#define TinierScreen096 128

#define SSD1306_DEFAULT_ADDRESS 0x3C
#define SSD1306_SETCONTRAST 0x81
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_DISPLAYALLON 0xA5
#define SSD1306_NORMALDISPLAY 0xA6
#define SSD1306_INVERTDISPLAY 0xA7
#define SSD1306_DISPLAYOFF 0xAE
#define SSD1306_DISPLAYON 0xAF
#define SSD1306_SETDISPLAYOFFSET 0xD3
#define SSD1306_SETCOMPINS 0xDA
#define SSD1306_SETVCOMDETECT 0xDB
#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
#define SSD1306_SETPRECHARGE 0xD9
#define SSD1306_SETMULTIPLEX 0xA8
#define SSD1306_SETLOWCOLUMN 0x00
#define SSD1306_SETHIGHCOLUMN 0x10
#define SSD1306_SETSTARTLINE 0x40
#define SSD1306_MEMORYMODE 0x20
#define SSD1306_COLUMNADDR 0x21
#define SSD1306_PAGEADDR   0x22
#define SSD1306_COMSCANINC 0xC0
#define SSD1306_COMSCANDEC 0xC8
#define SSD1306_SEGREMAP 0xA0
#define SSD1306_CHARGEPUMP 0x8D
#define SSD1306_SWITCHCAPVCC 0x2
#define SSD1306_NOP 0xE3

#define SSD1306_WIDTH 128
#define SSD1306_HEIGHT 64
#define SSD1306_BUFFERSIZE (SSD1306_WIDTH*SSD1306_HEIGHT)/8





class TinierScreen : public Print {
 public:
  //init, control
  TinierScreen(uint8_t);
  void startData(void);
  void startCommand(void);
  void endTransfer(void);
  void begin(void);
  void begin(uint8_t resetPin);
  void on(void);
  void off(void);
  void setFlip(uint8_t);
  void setMirror(uint8_t);
  void setBitDepth(uint8_t);
  void setColorMode(uint8_t);
  void setBrightness(uint8_t);
  void writeRemap(void);
  //accelerated drawing commands
  void drawPixel(uint8_t, uint8_t, uint16_t);
  void drawLine(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
  void drawLine(uint8_t, uint8_t, uint8_t, uint8_t, uint16_t);
  void drawRect(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
  void drawRect(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint16_t);
  void clearWindow(uint8_t, uint8_t, uint8_t, uint8_t);
  void clearScreen(void);
  //basic graphics commands
  void writePixel(uint16_t);
  void writeBuffer(uint8_t *, int);
  void setX(uint8_t, uint8_t);
  void setY(uint8_t, uint8_t);
  void goTo(uint8_t x, uint8_t y);
  //I2C GPIO related
  uint8_t getButtons(uint8_t);
  uint8_t getButtons(void);
  void writeGPIO(uint8_t, uint8_t);
  //font
  void setFont(void);
  uint8_t getFontHeight(void);
  uint8_t getPrintWidth(char *);
  void setCursor(uint8_t, uint8_t);
  void fontColor(uint16_t, uint16_t);
  virtual size_t write(uint8_t);
  //DMA for SAMD
  void initDMA(void);
  uint8_t getReadyStatusDMA(void);
  void writeBufferDMA(uint8_t *,int);
  
  static const uint8_t xMax=95;
  static const uint8_t yMax=63;
 private:
  
  uint8_t _addr, _cursorX, _cursorY, _fontHeight, _fontFirstCh, _fontLastCh, _bitDepth, _flipDisplay, _mirrorDisplay, _colorMode, _externalIO, _type, _resetPin;
  uint16_t  _fontColor, _fontBGcolor;
  //const FONT_CHAR_INFO* _fontDescriptor;
  const unsigned char* _fontBitmap;
};

#endif