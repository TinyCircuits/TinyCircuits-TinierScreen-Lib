/*
TinierScreen.cpp - Last modified 6 January 2020

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

The latest version of this library can be found at https://tiny-circuits.com/
*/

#include "TinierScreen.h"
#include <avr/pgmspace.h>
#include "pins_arduino.h"
#include "wiring_private.h"
#include <Wire.h>

/*
TinierScreen uses an I2C GPIO chip to interface with the OLED control lines and buttons
TinierScreen+ has direct IO and uses the Arduino digital IO interface
writeGPIO(address, data);//write to SX1505
startCommand();//write SSD1331 chip select active with data/command signalling a command
startData();//write SSD1331 chip select active with data/command signalling data
endTransfer();//write SSD1331 chip select inactive
getButtons();//read button states, return as four LSBs in a byte- optional button mask
*/
void sendCommand(uint8_t command);
void sendCommand(uint8_t command) {
  Wire.beginTransmission(SSD1306_DEFAULT_ADDRESS);
  Wire.write(0x00);
  Wire.write(command);
  Wire.endTransmission();
}

void TinierScreen::writeGPIO(uint8_t regAddr, uint8_t regData)
{
  //
}

void TinierScreen::startCommand(void) {
  //
}

void TinierScreen::startData(void) {
  //
}

void TinierScreen::endTransfer(void) {
  //
}

uint8_t TinierScreen::getButtons(uint8_t buttonMask) {
  return 0;
}

uint8_t TinierScreen::getButtons(void) {
  return 0;
}

/*
SSD1331 Basics
goTo(x,y);//set OLED RAM to pixel address (x,y) with wrap around at x and y max
setX(x start, x end);//set OLED RAM to x start, wrap around at x end
setY(y start, y end);//set OLED RAM to y start, wrap around at y end
*/

void TinierScreen::goTo(uint8_t x, uint8_t y) {

}

void TinierScreen::setX(uint8_t x, uint8_t end) {

}

void TinierScreen::setY(uint8_t y, uint8_t end) {

}

/*
Hardware accelerated drawing functions:
clearWindow(x start, y start, width, height);//clears specified OLED controller memory
clearScreen();//clears entire screen
drawRect(x stary, y start, width, height, fill, 8bitcolor);//sets specified OLED controller memory to an 8 bit color, fill is a boolean
drawRect(x stary, y start, width, height, fill, 16bitcolor);//sets specified OLED controller memory to an 8 bit color, fill is a boolean
drawRect(x stary, y start, width, height, fill, red, green, blue);//like above, but uses 6 bit color values. Red and blue ignore the LSB.
drawLine(x1, y1, x2, y2, 8bitcolor);//draw a line from (x1,y1) to (x2,y2) with an 8 bit color
drawLine(x1, y1, x2, y2, 16bitcolor);//draw a line from (x1,y1) to (x2,y2) with an 16 bit color
drawLine(x1, y1, x2, y2, red, green, blue);//like above, but uses 6 bit color values. Red and blue ignore the LSB.
*/

void TinierScreen::clearWindow(uint8_t x, uint8_t y, uint8_t w, uint8_t h) {  

}

void TinierScreen::clearScreen(){

}

void TinierScreen::drawRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t f, uint8_t r, uint8_t g, uint8_t b) 
{

}

void TinierScreen::drawRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t f, uint16_t color) 
{

}

void TinierScreen::drawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t r, uint8_t g, uint8_t b) {  
 
}

void TinierScreen::drawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint16_t color) {
 
}

/*
Pixel manipulation
drawPixel(x,y,color);//set pixel (x,y) to specified color. This is slow because we need to send commands setting the x and y, then send the pixel data.
writePixel(color);//write the current pixel to specified color. Less slow than drawPixel, but still has to ready display for pixel data
writeBuffer(buffer,count);//optimized write of a large buffer of 8 bit data. Must be wrapped with startData() and endTransfer(), but there can be any amount of calls to writeBuffer between.
*/

void TinierScreen::drawPixel(uint8_t x, uint8_t y, uint16_t color)
{
 
}

void TinierScreen::writePixel(uint16_t color) {

}

void TinierScreen::writeBuffer(uint8_t *buffer,int count) {
  
  if (_type == 72){
    
  sendCommand(SSD1306_COLUMNADDR);
  sendCommand(28 + 0x00);
  sendCommand(28 + 72 - 1);

  sendCommand(SSD1306_PAGEADDR);
  sendCommand(0x00);
  sendCommand(0x05);/////////////////////////////////////////////////////check these
  for (uint8_t packet = 0; packet < 45; packet++) {
    Wire.beginTransmission(SSD1306_DEFAULT_ADDRESS);
    Wire.write(0x40);
    for (uint8_t packet_byte = 0; packet_byte < 8; ++packet_byte) {
      Wire.write(buffer[packet * 8 + packet_byte]);
    }
    Wire.endTransmission();
  }
  }
  if (_type == 96){
    
  sendCommand(SSD1306_COLUMNADDR);
  sendCommand(32+0x00);
  sendCommand(32+0x5F);

  sendCommand(SSD1306_PAGEADDR);
  sendCommand(0x00);
  sendCommand(0x01);
  for (uint8_t packet = 0; packet < 24; packet++) {
    Wire.beginTransmission(SSD1306_DEFAULT_ADDRESS);
    Wire.write(0x40);
    for (uint8_t packet_byte = 0; packet_byte < 8; ++packet_byte) {
      int buffPos = packet * 8 + packet_byte;
      //if (buffPos > 95)buffPos += (textBuffCharWidth - 96);
      Wire.write(buffer[buffPos]);
    }
    Wire.endTransmission();
  }
  }
  if (_type == 128){
  sendCommand(SSD1306_COLUMNADDR);
  sendCommand(0x00);
  sendCommand(0x7F);

  sendCommand(SSD1306_PAGEADDR);
  sendCommand(0x00);
  sendCommand(0x07);
  for (uint8_t packet = 0; packet < 64; packet++) {
    Wire.beginTransmission(SSD1306_DEFAULT_ADDRESS);
    Wire.write(0x40);
    for (uint8_t packet_byte = 0; packet_byte < 16; ++packet_byte) {
      int buffPos = (int)(packet * 16) + (int)packet_byte;
      Wire.write(buffer[buffPos]);
    }
    Wire.endTransmission();
  }

    
  }
  

}

/* 
TinierScreen commands
setBrightness(brightness);//sets main current level, valid levels are 0-15
on();//turns display on
off();//turns display off, uses less power
setBitDepth(depth);//boolean- 0 is 8 bit, 1 is 16 bit
setFlip(flip);//done in hardware on the SSD1331. boolean- 0 is normal, 1 is upside down
setMirror(mirror);//done in hardware on the SSD1331. boolean- 0 is normal, 1 is mirrored across Y axis
*/

void TinierScreen::setBrightness(uint8_t brightness) {
  
}

void TinierScreen::on(void) {
 
}

void TinierScreen::off(void) {
 
}

void TinierScreen::setBitDepth(uint8_t b){
 
}

void TinierScreen::setFlip(uint8_t f){
  sendCommand(SSD1306_SEGREMAP|1);
  sendCommand(SSD1306_COMSCANDEC);
  
}

void TinierScreen::setMirror(uint8_t m){
  
}

void TinierScreen::setColorMode(uint8_t cm){
 
}

/*
The SSD1331 remap command sets a lot of driver variables, these are kept in memory
and are all written when a change is made.
*/

void TinierScreen::writeRemap(void){
 
}

void TinierScreen::begin(void) {
  
  Wire.begin();

  sendCommand(SSD1306_DISPLAYOFF);
  sendCommand(SSD1306_SETDISPLAYCLOCKDIV);
  sendCommand(0x80);
  sendCommand(SSD1306_SETDISPLAYOFFSET);
  sendCommand(0x00);
  sendCommand(SSD1306_SETSTARTLINE | 0x00);
  sendCommand(SSD1306_DISPLAYALLON_RESUME);
  sendCommand(SSD1306_NORMALDISPLAY);
  sendCommand(SSD1306_CHARGEPUMP);
  sendCommand(0x14);       //Internal
  sendCommand(SSD1306_MEMORYMODE);
  sendCommand(0x00);
  sendCommand(SSD1306_SEGREMAP);
  sendCommand(SSD1306_COMSCANINC);
  sendCommand(SSD1306_SETCONTRAST);
  sendCommand(255);//0xAF
  
  sendCommand(SSD1306_SETPRECHARGE);
  sendCommand(0xF1);
  
  sendCommand(SSD1306_SETVCOMDETECT);///////try 0x30 for all?
  if (_type == 72)sendCommand(0x20);
  if (_type == 96)sendCommand(0xFF);//0x40
  if (_type == 128)sendCommand(0x80);//0x40

  sendCommand(SSD1306_SETMULTIPLEX);
  if (_type == 72)sendCommand(40 - 1);
  if (_type == 96)sendCommand(16 - 1);
  if (_type == 128)sendCommand(64 - 1);
  
  sendCommand(SSD1306_SETCOMPINS);
  if (_type == 72)sendCommand(0x12);
  if (_type == 96)sendCommand(0x02);
  if (_type == 128)sendCommand(0x12);

  if (_type == 72){
    sendCommand(0xAD);
    sendCommand(0x30);
  }

  sendCommand(SSD1306_DISPLAYON);

  
}

void TinierScreen::begin(uint8_t resetPin) {
  _resetPin=resetPin;
  pinMode(_resetPin, OUTPUT);
  digitalWrite(_resetPin, LOW);
  digitalWrite(_resetPin, HIGH);
  begin();
}


/*
TinierScreen constructor
type tells us if we're using a regular TinierScreen, alternate addresss TinierScreen, or a TinierScreen+
address sets I2C address of SX1505 to 0x20 or 0x21, which is set by the position of a resistor near SX1505 (see schematic and board design)
*/

TinierScreen::TinierScreen(uint8_t type){
  _type=type;
}

/*
TinierScreen Text Display
setCursor(x,y);//set text cursor position to (x,y)
setFont(descriptor);//set font data to use
fontColor(text color, background color);//sets text and background color
getFontHeight();//returns height of font

getStringWidth
*/

void TinierScreen::setCursor(uint8_t x, uint8_t y){
  _cursorX=x;
  _cursorY=y;
}

void TinierScreen::setFont(void){
}

void TinierScreen::fontColor(uint16_t f, uint16_t g){
}

uint8_t TinierScreen::getFontHeight(void){
  return 0;
}


uint8_t TinierScreen::getPrintWidth(char * st){
  if(!_fontFirstCh)return 0;
  uint8_t i,amtCh,totalWidth;
  return totalWidth;
}

size_t TinierScreen::write(uint8_t ch){

  return 1;
}