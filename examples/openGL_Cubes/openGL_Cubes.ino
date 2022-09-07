#include "SPI.h"
//#include "ST7789_t3.h"
#include "ILI9341_t3n.h"
#include <TeensyGL.h> 

float angle = -0.;

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
}

void loop() {
  tft.glClear(ILI9341_BLACK); 
  reShape();
  tft.setCursor(0,0);
  tft.println("Basic Cube");
  tft.println("using GL_QUADS");
  tft.setCursor(0,tft.height() - 50);
  tft.println("Lib converts to Triangs");
  tft.println("Press Any Key to Cont");
  tft.glRotatef(-45., 0., 1., 1.f);  //note to self -75 for torus
  tft.glScalef(2.0, 2.0, 2.0);  //was
  drawCube();
  tft.updateScreen();

  nextAngle();

  tft.glClear(ILI9341_BLACK);
  tft.setCursor(0,0);
  tft.println("Cube w/Triangs");
  tft.println("Press Any Key to Cont.");
  reShape();
  tft.glRotatef(-45., 0., 1., 1.f);  //note to self -75 for torus
  tft.glScalef(2.0, 2.0, 2.0);  //was
  drawCube1();
  tft.updateScreen();

  nextAngle();

  _use_SmoothShader = true;
  tft.glAttachShader(SmoothShader,"Gourand");
  while(abs(angle) < 370.0){
    tft.glClear(ILI9341_BLACK);
    tft.setCursor(0,0);
    tft.println("Cube(Triags) Gourand");
    reShape();
    tft.glRotatef(angle, 0., 1., 1.f);  //note to self -75 for torus
    tft.glScalef(2.0, 2.0, 2.0);  //was
    drawCube1();
    tft.updateScreen();
    delay(100);
    angle -= 10.;
  }
  tft.println("Press Any Key to Cont.");
  tft.updateScreen();
  if(abs(angle) > 350) angle = 0;
  tft.glAttachShader(NONE);

  nextAngle();
  
  while(abs(angle) < 370.0){
    tft.glClear(ILI9341_BLACK);
    tft.setCursor(0,0);
    tft.println("Rotating Cubes");
    _use_SmoothShader = true;
    tft.glAttachShader(SmoothShader,"Gourand");
    reShape();
    tft.glTranslatef(0.0, -2.5, 0.0);
    tft.glRotatef(angle, 0., 1., 1.f);
    tft.glScalef(1.5, 1.5, 1.5);  //was 2.5
    drawCube1();
    tft.glAttachShader(NONE);
    
    _use_SmoothShader = false;
    tft.glAttachShader(SimpleVertexShader);
    reShape();
    tft.glTranslatef(0.0, 2.5, 0.0);
    tft.glRotatef(-angle, 0., 1., 1.f);
    tft.glScalef(1.5, 1.5, 1.5);  //was 2.5
    drawCube();
    tft.glAttachShader(NONE);
    tft.updateScreen(); 
    delay(100);
    angle -= 10.;
  }
  tft.println("Press Any Key to Cont.");
  tft.updateScreen();
  if(abs(angle) > 350) angle = 0;
  tft.glAttachShader(NONE);

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
