/*
 * Square.ino
 * Created by Fabio de Albuquerque Dela Antonio
 * fabio914 at gmail.com
 * 
 * An OpenGL example that draws a rotated and scaled square.
 */
#include "SPI.h"
#include <ArduinoGL.h> 

//#define ILI9488 1
#define ILI9341 1

// For the Adafruit shield, these are the default.
#define TFT_DC  9
#define TFT_CS 10

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
#if defined(ILI9488)
Arduino_OpenGL tft = Arduino_OpenGL(&SPI, TFT_CS, TFT_DC, 8);
#elif defined(ILI9341)
Arduino_OpenGL tft = Arduino_OpenGL(TFT_CS, TFT_DC, 8);
#endif

// Color definitions
#define BLACK       0x0000      /*   0,   0,   0 */
#define YELLOW      0xFFE0      /* 255, 255,   0 */
#define WHITE       0xFFFF      /* 255, 255, 255 */

uint8_t use_fb = 1;


void setup() {
  tft.begin();
  tft.fillScreen(BLACK);
  tft.setTextColor(YELLOW);
  tft.setTextSize(2);
  tft.println("Waiting for Arduino Serial Monitor...");

  Serial.begin(9600);
  while (!Serial) ; // wait for Arduino Serial Monitor
  Serial.println("OpenGL Test!"); 

  delay(1000);
  tft.useFrameBuffer(use_fb);

  /* Pass the canvas to the OpenGL environment */
  tft.glClear(BLACK);
  tft.glPointSize(4);
    
  tft.glMatrixMode(GL_PROJECTION);
  tft.glLoadIdentity();
  tft.gluOrtho2D(-5.0, 5.0, -5.0, 5.0);
    
  tft.glMatrixMode(GL_MODELVIEW);
}

void loop() {

  /* Read the rotation angle from a potentiometer attached to pin A0 */
  float angle = .4 * 360.f;
  
  static float scale = 3.0, scaleInc = 0.4;
  const float maxScale = 8.0, minScale = 2.0;

  tft.glClear(BLACK); 
  
  tft.glLoadIdentity();
  tft.glRotatef(angle, 0.f, 0.f, 1.f);
  tft.glScalef(scale, scale, 0.f);
  tft.glTranslatef(-0.5f, -0.5f, 0.f);
  
  tft.glBegin(GL_POINTS);
    tft.glVertex3f(0.f, 1.f, 0.f);
    tft.glVertex3f(0.f, 0.f, 0.f);
    tft.glVertex3f(1.f, 0.f, 0.f);
    tft.glVertex3f(1.f, 1.f, 0.f);
  tft.glEnd();

  tft.glBegin(GL_POLYGON);
    tft.glVertex3f(0.f, 1.f, 0.f);
    tft.glVertex3f(0.f, 0.f, 0.f);
    tft.glVertex3f(1.f, 0.f, 0.f);
    tft.glVertex3f(1.f, 1.f, 0.f);
  tft.glEnd();
  tft.updateScreen();

  scale += scaleInc;

  if(scale > maxScale)
    scaleInc *= -1.f;

  if(scale < minScale)
    scaleInc *= -1.f;
  
  delay(1);
}
