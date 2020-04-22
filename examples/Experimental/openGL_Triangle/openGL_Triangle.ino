/*
 * Square.ino
 * Created by Fabio de Albuquerque Dela Antonio
 * fabio914 at gmail.com
 * 
 * An OpenGL example that draws a rotated and scaled square.
 */
#include "SPI.h"
#include <ArduinoGL.h> 

// For the Adafruit shield, these are the default.
#define TFT_DC  9
#define TFT_CS 10

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Arduino_OpenGL tft = Arduino_OpenGL(&SPI, TFT_CS, TFT_DC, 8);
uint8_t use_fb = 1;


void drawPyramid() {

  /* 3 triangles instead of 4 */
  tft.glBegin(GL_TRIANGLE_STRIP);
    tft.glVertex3f(-1, -1, -1);
    tft.glVertex3f(1, -1, -1);
    tft.glVertex3f(0, 1, 0);
    tft.glVertex3f(1, -1, 1);
    tft.glVertex3f(-1, -1, 1);
  tft.glEnd();
  
  tft.glBegin(GL_POLYGON);
    tft.glVertex3f(-1, -1, 1);
    tft.glVertex3f(1, -1, 1);
    tft.glVertex3f(1, -1, -1);
    tft.glVertex3f(-1, -1, -1);
  tft.glEnd();
}



void setup() {
  tft.begin();
  tft.fillScreen(ILI9488_BLACK);
  tft.setTextColor(ILI9488_YELLOW);
  tft.setTextSize(2);
  tft.println("Waiting for Arduino Serial Monitor...");

  Serial.begin(9600);
  while (!Serial) ; // wait for Arduino Serial Monitor
  Serial.println("OpenGL Test!"); 

  delay(1000);

  /* Pass the canvas to the OpenGL environment */
  tft.glClear(ILI9488_BLACK);
  tft.glPointSize(4);
    
  tft.glMatrixMode(GL_PROJECTION);
  tft.glLoadIdentity();

  tft.gluPerspective(30.0, 0.8, 0.1f, 9999.f);
    
  tft.glMatrixMode(GL_MODELVIEW);
}

void loop() {
  /* Read the rotation angle from a potentiometer attached to pin A0 */
  float angle = analogRead(0)/1024.f * 360.f;
  const float scale = 2.5;

  tft.glClear(ILI9488_BLACK); 
  
  tft.glLoadIdentity();
  tft.gluLookAt(10, 8, -10, 0, 0, 0, 0, 1, 0);
    
  tft.glRotatef(angle, 0.f, 1.f, 0.f);
  tft.glScalef(scale, scale, scale);
  
  drawPyramid();

  
  delay(1);
}
