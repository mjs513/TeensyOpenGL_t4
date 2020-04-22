/*
 * Square.ino
 * Created by Fabio de Albuquerque Dela Antonio
 * fabio914 at gmail.com
 * 
 * An OpenGL example that draws a rotated and scaled square.
 */
#include "SPI.h"
//#include "ST7789_t3.h"
#include "ILI9341_t3n.h"
#include <ArduinoGL.h> 

// For the Adafruit shield, these are the default.
#define TFT_DC  9
#define TFT_CS 10

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Teensy_OpenGL tft = Teensy_OpenGL(TFT_CS, TFT_DC, 8);
uint8_t use_fb = 1;

void setup() {
  tft.begin();
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_YELLOW);
  tft.setTextSize(2);
  tft.println("Waiting for Arduino Serial Monitor...");

  Serial.begin(9600);
  while (!Serial) ; // wait for Arduino Serial Monitor
  Serial.println("OpenGL Test!"); 

  delay(1000);

  /* Pass the canvas to the OpenGL environment */
  tft.glClear(ILI9341_BLACK);
   
  tft.glMatrixMode(GL_PROJECTION);
  tft.glLoadIdentity();
    double ar = tft.width() / tft.height();
  tft.gluOrtho2D(-5.0, 5.0, -6.0, 6.0);
  //tft.glOrtho( -4 * ar, 4 * ar, -4, 4, -1, 1);
  tft.glMatrixMode(GL_MODELVIEW);
  //tft.glAttachShader(SimpleVertexShader);  //only shader available.
                                           //only use with triange_strip
  //tft.glAttachShader(FacetShader);
  tft.useFrameBuffer(1);

}

float angle = 0;
const float scale = 1.5;

void loop() {
  tft.glClear(ILI9341_BLACK); 
  tft.glLoadIdentity();
      
  tft.glRotatef(angle, 0.f, 0.f, 1.f);
  tft.glScalef(scale, scale, scale);
  
  tft.glPointSize(4);
  //drawLines();
  //drawLineStrip();
  //drawLineLoop();
  
  //drawPoly();
  
  //drawQuad3();
  //drawQuad1();
  drawQuad2();
  tft.updateScreen();

  angle -= 10;
  if(abs(angle) == 360) angle = 0;
  delay(100);
}
