#include "SPI.h"
//#include "ST7789_t3.h"
#include "ILI9341_t3n.h"
#include <TeensyGL.h> 

// For the Adafruit shield, these are the default.
#define TFT_DC  9
#define TFT_CS  10

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Teensy_OpenGL tft = Teensy_OpenGL(TFT_CS, TFT_DC, 8);
uint8_t use_fb = 1;

bool _use_FacetShader = false;     //Phong shading, no lighting
bool _use_SimpleShader = false;     //flat shading (use single color)
                                //Interpolation shading each vertex has a different color
bool _use_SmoothShader = false;     //Phong: "Phong", Gourand: "Gourand"
bool _use_perspective = false;

void setup() {
  tft.begin();
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_YELLOW);
  tft.setTextSize(2);
  tft.println("Waiting for Arduino Serial Monitor...");
  //tft.setRotation(1);
  
  Serial.begin(9600);
  while (!Serial) ; // wait for Arduino Serial Monitor
  Serial.println("OpenGL Test!"); 

  delay(1000);

  /* Pass the canvas to the OpenGL environment */
  tft.glClear(ILI9341_BLACK);
  
  //copper - taken from
  float light_ambient[] = {.19125, .0735, .0225, 1.0}; // whitelight {r, g, b, Intensity}
  float light_diffuse[] = {.7038, .27048, .0828, 1.0}; // {r, g, b, Intensity}
  float light_specular[] = {.256771, .137622, .137622, 1.0}; // {r, g, b, Intensity}
  
  //float light_ambient[] = {.329412, .223529, .023451, 0.7}; // whitelight {r, g, b, Intensity}
  //float light_diffuse[] = {.780392, .568627, .113725, 0.4}; // {r, g, b, Intensity}  //float light_specular[] = {1., 1., 1., 0.8};

  float light_position[] =  {-1., 1., -1};    // direction of the diffuse light
                                              // (this vector should have length 1)
  tft.glLight(GL_LIGHT0, GL_AMBIENT, light_ambient);
  tft.glLight(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  tft.glLight(GL_LIGHT0, GL_SPECULAR, light_specular);
  tft.glLight(GL_LIGHT0, GL_POSITION, light_position);
  
  tft.useFrameBuffer(1);

  tft.glPointSize(4);
}

float angle = -45.;
const float scale = 1.5;
uint8_t option = -1;

void loop() {
  serial_handler();
  if(option == 0){
    tft.glClear(ILI9341_BLACK); 
    tft.setCursor(0,0);
    tft.println("Demoing GL_LINES with Thickness");
    reShape();   
    tft.glRotatef(angle, 0.f, 0.f, 1.f);
    tft.glScalef(scale, scale, scale);
    drawLines();
    tft.updateScreen();
    angle -= 10;
    if(abs(angle) == 360) angle = 0;
    delay(100);
  }
  if(option == 1){
    tft.glClear(ILI9341_BLACK);
    tft.setCursor(0,0);
    tft.println("Demoing Line Strip with Thickness");
    reShape();   
    tft.glRotatef(angle, 0.f, 0.f, 1.f);
    tft.glScalef(scale, scale, scale);
    drawLineStrip();
    tft.updateScreen();
    angle -= 10;
    if(abs(angle) == 360) angle = 0;
    delay(100);
  }
  if(option == 2){
    tft.glClear(ILI9341_BLACK);
    tft.setCursor(0,0);
    tft.println("Demoing Line Loop with Thickness");
    reShape();   
    tft.glRotatef(angle, 0.f, 0.f, 1.f);
    tft.glScalef(scale, scale, scale);
    drawLineLoop();
    tft.updateScreen();
    angle -= 10;
    if(abs(angle) == 360) angle = 0;
    delay(100);
  }
  if(option == 3){
    tft.glClear(ILI9341_BLACK);
    tft.setCursor(0,0);
    tft.println("Demoing Drawing Polygon");
    reShape();   
    tft.glRotatef(angle, 0.f, 0.f, 1.f);
    tft.glScalef(scale, scale, scale);
    drawPoly();
    tft.updateScreen();
    angle -= 10;
    if(abs(angle) == 360) angle = 0;
    delay(100);
  }
  if(option == 4){
    tft.glClear(ILI9341_BLACK);
    tft.setCursor(0,0);
    tft.println("Demoing WireFrame Quad");
    reShape();   
    tft.glRotatef(angle, 0.f, 0.f, 1.f);
    tft.glScalef(scale, scale, scale);
    drawQuad1();
    tft.updateScreen();
    angle -= 10;
    if(abs(angle) == 360) angle = 0;
    delay(100);
  }
  if(option == 5){
    tft.glClear(ILI9341_BLACK);
    tft.setCursor(0,0);
    tft.println("Demoing Filled Quad");
    reShape();   
    tft.glRotatef(angle, 0.f, 0.f, 1.f);
    tft.glScalef(scale, scale, scale);
    drawQuad2();
    tft.updateScreen();
    angle -= 10;
    if(abs(angle) == 360) angle = 0;
    delay(100);
  }
}

void reShape(){
  tft.glMatrixMode(GL_PROJECTION);
  tft.glLoadIdentity();

  float ar = (float)tft.width() / (float) tft.height();

  if (_use_perspective == 1) {
      tft.gluPerspective(65.0, ar, 0.1f, 9999.f);
   } else {
    if(tft.width() >  tft.height()) {
      tft.glOrtho(-6.0, 6.0, -5.0, 5.0, -5, 5);
    } else {
      tft.glOrtho(-5.0, 5.0, -6.0, 6.0, -5, 5);
    }  }
  
  tft.glMatrixMode(GL_MODELVIEW);

  tft.glLoadIdentity();

  if(_use_perspective == 1)
      tft.gluLookAt(0, 0, -15, 0, 3, 0, 0, 1, 0);
}



void serial_handler() {
    char inChar;
    if ((inChar = Serial.read()) > 0) {
        switch (inChar) {
            case '0': //Lines
                option = 0;
                break;
            case '1':
                option = 1;
                break;
            case '2': // Back presed
                option = 2;
                break;
            case '3': // Select presed
                option = 3;
                break;
            case '4':
                option = 4;
                break;
            case '5': // Display help
                option = 5;
                break;
            case '6': // Display help
                option = 6;
                break;
            case '7': // Display help
                option = 7;
                break;                
            case '8': // Display help
                option = 8;
                break;                  
            case '9': // Display help
                option = 9;
                break;  
            default:
                break;
        }
    }
}
