/************************************************************************
   OLED Wireling Screen Example Program
   This program uses all three of the Wireling OLEDs:
   Port 0: 0.42" OLED Screen Wireling
   Port 1: 0.69" OLED Screen Wireling
   Port 2: 0.96" OLED Screen Wireling
   Port 3: None

   This program prints the screen size to each screen. This text then 
   floats around the screen bouncing off the sides of the screen.

   Hardware by: TinyCircuits
   Written by: Hunter Hykes for TinyCircuits

   Initiated: 01/06/2020
   Updated: --/--/20--
 ************************************************************************/

#include <Wire.h>           // For I2C communication with sensor
#include <Wireling.h>       // For Wireling interfacing
#include <TinierScreen.h>   
#include <GraphicsBuffer.h> // For building a screen buffer 

// Make compatible with all TinyCircuits processors
#if defined(ARDUINO_ARCH_AVR)
#define SerialMonitorInterface Serial
#elif defined(ARDUINO_ARCH_SAMD)
#define SerialMonitorInterface SerialUSB
#endif

/* * * * * * * * * * 0.42" OLED * * * * * * * * * */
int OLED_042_PORT = 0;
int OLED_042_RESET = A0; // use Port 0 reset pin
int OLED_042_WIDTH = 72;
int OLED_042_HEIGHT = 40;
TinierScreen display042 = TinierScreen(TinierScreen042);
GraphicsBuffer screenBuffer042 = GraphicsBuffer(OLED_042_WIDTH, OLED_042_HEIGHT, colorDepth1BPP);

/* * * * * * * * * * 0.69" OLED * * * * * * * * * */
int OLED_069_PORT = 1; 
int OLED_069_RESET = A1;
int OLED_069_WIDTH = 96;
int OLED_069_HEIGHT = 16;
TinierScreen display069 = TinierScreen(TinierScreen069);
GraphicsBuffer screenBuffer069 = GraphicsBuffer(OLED_069_WIDTH, OLED_069_HEIGHT, colorDepth1BPP);

/* * * * * * * * * * 0.96" OLED * * * * * * * * * */
int OLED_096_PORT = 2; 
int OLED_096_RESET = A2; 
int OLED_096_WIDTH = 128;
int OLED_096_HEIGHT = 64;
TinierScreen display096 = TinierScreen(TinierScreen096);
GraphicsBuffer screenBuffer096 = GraphicsBuffer(OLED_096_WIDTH, OLED_096_HEIGHT, colorDepth1BPP);

void setup() {
  SerialMonitorInterface.begin(115200);
  Wire.begin();
  Wireling.begin(); // Enable power & select port

  /* * * * * * * * * 0.42" Screen Stuff * * * * * * * */
  Wireling.selectPort(OLED_042_PORT);
  display042.begin(OLED_042_RESET);
  if (screenBuffer042.begin()) {
    //memory allocation error- buffer too big!
  }
  screenBuffer042.setFont(thinPixel7_10ptFontInfo);

  /* * * * * * * * * 0.69" Screen Stuff * * * * * * * */
  Wireling.selectPort(OLED_069_PORT);
  display069.begin(OLED_069_RESET);
  if (screenBuffer069.begin()) {
    //memory allocation error- buffer too big!
  }
  screenBuffer069.setFont(thinPixel7_10ptFontInfo);

  /* * * * * * * * * 0.96" Screen Stuff * * * * * * * */
  Wireling.selectPort(OLED_096_PORT);
  display096.begin(OLED_096_RESET);
  if (screenBuffer096.begin()) {
    //memory allocation error- buffer too big!
  }
  screenBuffer096.setFont(thinPixel7_10ptFontInfo);

}

int pos = 0; // current position
int xMax, yMax, x = 0, y = 0;

void loop() {
  // float around the screen type on each screen
  floatText(OLED_042_PORT, display042, screenBuffer042, "0.42\"");
  floatText(OLED_069_PORT, display069, screenBuffer069, "0.69\"");
  floatText(OLED_096_PORT, display096, screenBuffer096, "0.96\"");

  pos++; // increment the position (floatText is dependent on this)
}

void floatText(int port, TinierScreen screen, GraphicsBuffer &buffer, char *text) {
  // get the buffer size passed to the function to determine screen dimensions
  int bufferSize = buffer.getBufferSize();

  int padding_w = 0;  // how many pixels will go offscreen past the left and right sides
  int padding_h = 0;  // how many pixels will go offscreen past the top and bottom sides

  // each byte in the buffer holds data for 8 pixels (one per byte)
  // because of this, the buffer size is determined by 1/8th the
  // value of the ((display width) * (display_height))
  if (bufferSize == OLED_042_WIDTH * (OLED_042_HEIGHT >> 3)) {        // 0.42" OLED
    xMax = OLED_042_WIDTH + padding_w - buffer.getPrintWidth(text);   // set x bounds
    yMax = OLED_042_HEIGHT + 0 - buffer.getFontHeight();              // set y bounds

  } else if (bufferSize == OLED_069_WIDTH * (OLED_069_HEIGHT >> 3)) { // 0.69" OLED
    xMax = OLED_069_WIDTH + padding_w - buffer.getPrintWidth(text);
    yMax = OLED_069_HEIGHT + 0 - buffer.getFontHeight();

  } else if (bufferSize == OLED_096_WIDTH * (OLED_096_HEIGHT >> 3)) { // 0.96" OLED
    xMax = OLED_096_WIDTH + padding_w - buffer.getPrintWidth(text);
    yMax = OLED_096_HEIGHT + 0 - buffer.getFontHeight();
  }

  x = pos % xMax; if ((pos / xMax) & 1) x = xMax - x;
  y = pos % yMax; if ((pos / yMax) & 1) y = yMax - y;
  x -= padding_w >> 1; // subtract half of the width padding value from the x-coordinate
  y -= padding_h >> 1; // subtract half of the height padding value from the y-coordinate

  Wireling.selectPort(port);  // select the Wireling screen port
  buffer.clear();             // clear the graphics buffer
  buffer.setCursor(x, y);     // set the cursor in the buffer to write text
  buffer.print(text);   // the text to be printed
  Wire.setClock(1000000);
  screen.writeBuffer(buffer.getBuffer(), buffer.getBufferSize()); // write buffer to the screen
  Wire.setClock(50000);
}
