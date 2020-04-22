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


void drawSphere(float radius, float p) {

  float theta1 = 0.f, theta2 = 0.f, theta3 = 0.f;
  float ex, ey, ez;
        
  for(int i = 0; i < p/2; i++) {
            
    theta1 = i * (M_PI * 2.f)/p - M_PI_2;
    theta2 = (i + 1) * (M_PI * 2.f)/p - M_PI_2;
          
    tft.glBegin(GL_TRIANGLE_STRIP);
    for(int j = 0; j <= p; j++) {
                
      theta3 = j * (M_PI * 2.f)/p;
      ex = cosf(theta2) * cosf(theta3);
      ey = sinf(theta2);
      ez = cosf(theta2) * sinf(theta3);
                
      tft.glVertex3f(radius * ex, radius * ey, radius * ez);
      
      ex = cosf(theta1) * cosf(theta3);
      ey = sinf(theta1);
      ez = cosf(theta1) * sinf(theta3);
                
      tft.glVertex3f(radius * ex, radius * ey, radius * ez);
    }
    tft.glEnd();
  }
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
  /* Read the scale factor from a potentiometer attached to pin A0 */
  float scale = 0.5 * 4.f;
  static int angle = 0.f;

  tft.glClear(ILI9488_BLACK); 
  
  tft.glLoadIdentity();
  tft.gluLookAt(10, 8, -10, 0, 0, 0, 0, 1, 0);
  
  tft.glScalef(scale + 1.f, scale + 1.f, scale + 1.f);
  tft.glRotatef(angle, 0.f, 1.f, 0.f);
  
  drawSphere(1.0, 10);

  angle+=5;
  angle %= 360;
  
  delay(1);
}
