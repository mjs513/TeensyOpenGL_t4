#include "SPI.h"
//#include "ST7789_t3.h"
#include "ILI9341_t3n.h"
#include <TeensyGL.h> 
#include "T4_PowerButton.h"

float angle = -0.;

// For the Adafruit shield, these are the default.
#define TFT_DC  9
#define TFT_CS  10

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Teensy_OpenGL tft = Teensy_OpenGL(TFT_CS, TFT_DC, 8);
uint8_t use_fb = 1;

#define _use_FacetShader  0     //Phong shading, no lighting
#define _use_SimpleShader 0     //flat shading (use single color)
                                //Interpolation shading each vertex has a different color
#define _use_SmoothShader 1     //Phong: "Phong", Gourand: "Gourand"
#define _use_perspective  0

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
  flexRamInfo();

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
}

void loop() {
  tft.glClear(ILI9341_BLACK); 
  reShape();
  tft.setCursor(0,0);
  tft.println("Basic  Triangle");
  tft.println("Press Any Key to Cont.");
  tft.glRotatef(angle, 0., 1., 1.f);  //note to self -75 for torus
  tft.glScalef(2.0, 2.0, 2.0);  //was
  drawTri0();
  tft.updateScreen();

  nextAngle();

  tft.glClear(ILI9341_BLACK);
  tft.setCursor(0,0);
  tft.println("Wire Frame Tri.");
  tft.println("Press Any Key to Cont.");
  reShape();
  tft.glRotatef(angle, 0., 1., 1.f);  //note to self -75 for torus
  tft.glScalef(2.0, 2.0, 2.0);  //was
  drawTri1();
  tft.updateScreen();

  nextAngle();
  
  tft.glClear(ILI9341_BLACK); 
  tft.setCursor(0,0);
  tft.println("Tri-color Wire");
  tft.println("Press Any Key to Cont.");
  reShape();
  tft.glRotatef(angle, 0., 1., 1.f);  //note to self -75 for torus
  tft.glScalef(2.0, 2.0, 2.0);  //was
  drawTri();
  tft.updateScreen();

  nextAngle();
  
  tft.glClear(ILI9341_BLACK); 
  tft.setCursor(0,0);
  tft.println("Gradient Triangle");
  tft.println("SimpleVertex Shader");
  tft.println("Press Any Key to Cont.");
  reShape();
  tft.glAttachShader(SimpleVertexShader);
  tft.glRotatef(angle, 0., 1., 1.f);  //note to self -75 for torus
  tft.glScalef(2.0, 2.0, 2.0);  //was
  drawTri();
  tft.updateScreen();
  tft.glAttachShader(NONE);

  nextAngle();

  tft.glClear(ILI9341_BLACK); 
  tft.setCursor(0,0);
  tft.println("FacetShader Tri.");
  tft.println("Press Any Key to Cont.");
  reShape();
  tft.glAttachShader(FacetShader);
  tft.glRotatef(angle, 0., 1., 1.f);  //note to self -75 for torus
  tft.glScalef(2.0, 2.0, 2.0);  //was
  drawTri2();
  tft.updateScreen();
  tft.glAttachShader(NONE);

  nextAngle();

  tft.glAttachShader(FacetShader);
  while(abs(angle) < 370.0){
    tft.glClear(ILI9341_BLACK); 
    tft.setCursor(0,0);
    tft.println("Rotating Tri.");
    reShape();
    tft.glRotatef(angle, 0., 1., 1.f);  //note to self -75 for torus
    tft.glScalef(1.5, 1.5, 1.5);  //was
    drawPyramid();
    tft.updateScreen();
    delay(100);
    angle -= 10.;
  }
  tft.println("Press Any Key to Cont.");
  tft.updateScreen();
  if(abs(angle) > 350) angle = 0;
  tft.glAttachShader(NONE);

  nextAngle();

  tft.glAttachShader(FacetShader);
  
  while(abs(angle) < 370.0){
    tft.glClear(ILI9341_BLACK);
    tft.setCursor(0,0);
    tft.println("Rotating Diamond"); 
    reShape();
    tft.glRotatef(angle, 0., 1., 1.f);  //note to self -75 for torus
    tft.glScalef(1.5, 1.5, 1.5);  //was
    drawDiamond();
    tft.updateScreen();
    delay(100);
    angle -= 10.;
  }
  if(abs(angle) > 350) angle = 0;
  tft.glAttachShader(NONE);
  tft.println("Press Any Key to Cont.");
  tft.updateScreen();

  nextAngle();
  
  tft.glAttachShader(SmoothShader,"Gourand");
  while(abs(angle) < 370.0){
    tft.glClear(ILI9341_BLACK);
    tft.setCursor(0,0);
    tft.println("Gourand Shading"); 
    reShape();
    tft.glRotatef(angle, 0., 1., 1.f);  //note to self -75 for torus
    tft.glScalef(1.5, 1.5, 1.5);  //was
    drawDiamondShaded();
    tft.updateScreen();
    delay(100);
    angle -= 10.;
  }
  if(abs(angle) > 350) angle = 0;
  tft.glAttachShader(NONE);
  tft.println("Press Any Key to Cont.");
  tft.updateScreen();

  nextAngle();

  tft.glAttachShader(SmoothShader,"Phong");
  while(abs(angle) < 370.0){
    tft.glClear(ILI9341_BLACK);
    tft.setCursor(0,0);
    tft.println("Phong Shading"); 
    reShape();
    tft.glRotatef(angle, 0., 1., 1.f);  //note to self -75 for torus
    tft.glScalef(1.5, 1.5, 1.5);  //was
    drawDiamondShaded();
    tft.updateScreen();
    delay(100);
    angle -= 10.;
  }
  if(abs(angle) > 350) angle = 0;
  tft.glAttachShader(NONE);
  tft.println("Press Any Key to Cont.");
  tft.updateScreen();

  nextAngle();
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

void nextAngle()
{
  Serial.println("Press anykey to continue");
  while (Serial.read() == -1) ;
  while (Serial.read() != -1) ;
}
