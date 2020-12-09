/************************************************************************
 * Wireling OLED Display of text and graphics Demo/Tutorial:
 * This code will display text bouncing around the screen and a Sprite 
 * running across the screen at the same time when compiled. 
 * 
 * As written, a bunny sprite will run across the screen. There is a 
 * commented option to change the bunny sprite to a pacman in order to 
 * show you what definitions and initializations need made to move a 
 * new sprite. 
 * 
 * Sprite definition - a computer graphic which may be moved on-screen and 
 * otherwise manipulated as a single entity.
 *
 * Hardware by: TinyCircuits
 * Written by: Laveréna Wienclaw for TinyCircuits
 *
 * Initiated: Nov 6, 2020
 ************************************************************************/

#include <Wire.h>                   // For I2C communication
#include <SPI.h>
#include <Wireling.h>
#include "exampleSprites.h"         // Holds arrays of example Sprites
#include <TinierScreen.h>
#include <GraphicsBuffer.h>


// 0.42" Screen Variables
TinierScreen display = TinierScreen(TinierScreen042);
int xPixel = 72;
int yPixel = 40;

// 0.69" Screen Variables
//TinierScreen display = TinierScreen(TinierScreen069);
//int xPixel = 96;
//int yPixel = 16;

// 0.96" Screen Variables
//TinierScreen display = TinierScreen(TinierScreen096);
//int xPixel = 128;
//int yPixel = 64;

GraphicsBuffer screenBuffer = GraphicsBuffer(xPixel, xPixel, colorDepth1BPP);

int displayPort = 0;
int resetPin = A0+displayPort;

int increment = 0;
int xMax, yMax, x, y;
void boundedBouncyText(char*, int);

// This is the data structure for a Sprite
typedef struct {
  int x;             // X coordinate (top left corner) of where Sprite is placed on screen initially 
  int y;             // Y coordinate (top left corner) of where Sprite is placed on screen initially 
  int width;         // Wideness of Sprite
  int height;        // Height of Sprite
  int bitmapNum;     // Index of animation stage of Sprite (only used when a Sprite is animated)
  const unsigned int * bitmap; // The array of 0's and 1's that determines appearance of Sprite
} Sprite;

// The Sprite is initialized to appear on the screen at coordinate (41, 2)
// and exist in a space of 13 by 13 pixels. The 13 by 13 Bitmap of pixel information
// is assigned in file exampleSprites.h
Sprite bunnySprite = {41, 2, 13, 13, 0, bunnyBitmap};
Sprite pacmanSprite = {41, 2, 13, 13, 0, pacManRightBitmap}; // optional pacman sprite

// Declares how many Sprites are to appear on the screen. This info is used later
// on when the pixel bitmaps are sent to the OLED screen. 
// *** If you want more than one Sprite to appear, it must be added to this list***
int amtSprites = 1; 
Sprite * spriteList[1] = {
  &bunnySprite,   
//  &pacmanSprite, // other sprite option
};

int bufIndex = 0;    // Buffer index in respect to the array of pixels on the screen
int textPos;         // Used to make text move left or right

void setup() {
  // Initialize Wireling hardware
  Wire.begin();
  Wireling.begin();
  Wireling.selectPort(displayPort);
  display.begin(resetPin);

//  while(!SerialUSB);
//  SerialUSB.println("test");

  if (screenBuffer.begin()) {
    //memory allocation error- buffer too big!
  }
  
  screenBuffer.setFont(thinPixel7_10ptFontInfo);
}


void loop() {
  boundedBouncyText("Bunny!", displayPort); 
//  boundedBouncyText("Pacman!", displayPort); // other sprite option
  
  delay(10);
  
  bunnySprite.x += 2; // Changes speed of Sprite, bigger increment = faster
  if (bunnySprite.x > xPixel){
    bunnySprite.x = 0;
    
    bunnySprite.y += 5; // Height of Sprite, bigger increment = down faster
    if (bunnySprite.y > (yPixel - 13)){
      bunnySprite.y = 0;
    }   
  }
  
/* // other sprite option
  pacmanSprite.x += 2; // Changes speed of Sprite, bigger increment = faster
  if (pacmanSprite.x > xPixel){
    pacmanSprite.x = 0;
    
    pacmanSprite.y += 5; // Height of Sprite, bigger increment = down faster
    if (pacmanSprite.y > (yPixel - 13)){
      pacmanSprite.y = 0;
    }   
  }
*/
  drawSprites();
  display.writeBuffer(screenBuffer.getBuffer(), screenBuffer.getBufferSize());
}

void boundedBouncyText(char* text, int port) {
  xMax = screenBuffer.width + 20 - screenBuffer.getPrintWidth(text);
  yMax = screenBuffer.height + 8 - screenBuffer.getFontHeight();
  x = increment % xMax; if ((increment / xMax) & 1) x = xMax - x;
  y = increment % yMax; if ((increment / yMax) & 1) y = yMax - y;
  x -= 10;
  y -= 4;

  Wireling.selectPort(port);
  screenBuffer.clear();
  screenBuffer.setCursor(x, y);
  screenBuffer.print(text);
  Wire.setClock(500000);
  display.writeBuffer(screenBuffer.getBuffer(), screenBuffer.getBufferSize());
  Wire.setClock(500000);

  increment++;
}

void drawSprites() {
//  display.goTo(0, 0);
//  display.startData();

//  clearTinierScreen();
  screenBuffer.clear();

  for (int y = 0; y < yPixel; y++) { // Iterates through all y coordinates of the screen
    for (int spriteIndex = 0; spriteIndex < amtSprites; spriteIndex++) { // Iterates pixels for each Sprite

      // Sets currentSprite to the Current Sprite being accessed in the array
      Sprite *currentSprite = spriteList[spriteIndex]; 
      
      // Checks if the current Y-coordinate is within the current sprite's area
      if (y >= currentSprite->y && (y < (currentSprite->y + currentSprite->height))) { 
        int endX = currentSprite->x + currentSprite->width;
        if (currentSprite->x < xPixel && endX > 0) { //checks if the sprite is within the X-coordinate bounds of the screen
          int xBitmapOffset = 0;
          int xStart = 0;
          if (currentSprite->x < 0) {
            xBitmapOffset -= currentSprite->x;
          }
          if (currentSprite->x > 0) {
            xStart = currentSprite->x;
          }
          int yBitmapOffset = (y - currentSprite->y) * currentSprite->width;

          for (int x = xStart; x < endX && x < xPixel; x++) { //iterates through the X-bounds of the sprite
            bool pixelOn = currentSprite->bitmap[xBitmapOffset + yBitmapOffset++];
            if (pixelOn) {
              screenBuffer.drawPixel(x, y, 0xFFFF); //sets the pixel if a 1 is found in the bitmap
            }
          }
        }
      }
    }
  }
}
