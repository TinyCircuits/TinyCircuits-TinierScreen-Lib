# TinyCircuits Tinier Screen Arduino Library

This Arduino library is intended for use with TinyCircuits' **[0.42" OLED Wireling](https://tinycircuits.com/collections/wireling-displays-leds/products/0-42-oled-screen-wireling)**, **[0.69" OLED Wireling](https://tinycircuits.com/collections/wireling-displays-leds/products/0-69-oled-screen-wireling)**, and **[0.96" OLED Wireling](https://tinycircuits.com/collections/wireling-displays-leds/products/0-96-oled-screen-wireling)**. 

*Support this library by buying products from **[TinyCircuits](https://tinycircuits.com/)***


## Tinier Screen Class Basics

The Tinier Screen Library relies upon the **[Graphics Buffer Library](https://github.com/TinyCircuits/TinyCircuits-GraphicsBuffer-Lib)** to create a graphics buffer, and this library will then use that buffer to print it to the screen used.

### Initialization & Control

* **void startData(void)**
* **void startCommand(void)**
* **void endTransfer(void)**
* **void begin(void)**
* **void begin(uint8_t resetPin)**
* **void on(void)**
* **void off(void)**
* **void setFlip(uint8_t)**
* **void setMirror(uint8_t)**
* **void setBitDepth(uint8_t)**
* **void setBrightness(uint8_t)**
* **void writeRemap(void)**

### Built-In Drawing Commands

* **void drawPixel(uint8_t, uint8_t, uint16_t)**
* **void drawLine(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t)**
* **void drawLine(uint8_t, uint8_t, uint8_t, uint8_t, uint16_t)**
* **void drawRect(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t)**
* **void drawRect(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint16_t)**
* **void clearWindow(uint8_t, uint8_t, uint8_t, uint8_t)**

### Basic Graphic Commands

* **void drawPixel(uint8_t, uint8_t, uint16_t)**
* **void drawLine(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t)**
* **void drawLine(uint8_t, uint8_t, uint8_t, uint8_t, uint16_t)**
* **void drawRect(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t)**
* **void drawRect(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint16_t)**
* **void clearWindow(uint8_t, uint8_t, uint8_t, uint8_t)**
* **void clearScreen(void)**

### I2C / GPIO

* **uint8_t getButtons(uint8_t)**
* **uint8_t getButtons(void)**
* **void writeGPIO(uint8_t, uint8_t)**

### Font

* **void setFont(void)**
* **uint8_t getFontHeight(void)**
* **uint8_t getPrintWidth(char \*)**
* **void setCursor(uint8_t, uint8_t)**
* **void fontColor(uint16_t, uint16_t)**
* **virtual size_t write(uint8_t)**

### DMA for SAMD

* **void initDMA(void)**
* **uint8_t getReadyStatusDMA(void)**
* **void writeBufferDMA(uint8_t \*,int)**
  
  
  
