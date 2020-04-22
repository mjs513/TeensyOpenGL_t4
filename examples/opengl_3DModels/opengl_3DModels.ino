#include "SPI.h"
//#include "ST7789_t3.h"
#include "ILI9341_t3n.h"
#include <TeensyGL.h> 
#include "T4_PowerButton.h"

//UNCOMMENT THE MODEL YOU WANT TO USE
#include "teapot_high_res.h"
//#include "teapot_low_res.h"
//#include "monkey_high_res.h"
//#include "small_bunny.h"

//SELECT SHADER YOU WANT TO TRY OUT
//USE ALL 0 for WIREFRAME
#define _use_FacetShader  0     //Phong shading, no lighting
#define _use_SimpleShader 0     //flat shading (use single color)
                                //Interpolation shading each vertex has a different color
#define _use_SmoothShader 1     //Phong: "Phong", Gourand: "Gourand"
#define _use_perspective  0

//UNCOMMENT THE LIGHT COLOR (NOTE USING LIGHT COLOR TO 
//SIMULATE MATERIAL COLORING.  ONLY 1 LIGHT SOURCE FOR NOW
  //copper - taken from
  //float light_ambient[] = {.19125, .0735, .0225, 1.0}; // whitelight {r, g, b, Intensity}
  //float light_diffuse[] = {.7038, .27048, .0828, 1.0}; // {r, g, b, Intensity}
  //float light_specular[] = {.256771, .137622, .137622, 1.0}; // {r, g, b, Intensity}
  //Bronze - taken from
  float light_ambient[] = {.2125, .1275, .054, 1.0}; // whitelight {r, g, b, Intensity}
  float light_diffuse[] = {.714, .4284, .1814, 1.0}; // {r, g, b, Intensity}
  float light_specular[] = {.393548, .271906, .166721, 1.0}; // {r, g, b, Intensity}
  //Brass - taken from
  //float light_ambient[] = {.329412, .223529, .023451, 0.7}; // whitelight {r, g, b, Intensity}
  //float light_diffuse[] = {.780392, .568627, .113725, 0.4}; // {r, g, b, Intensity}  //float light_specular[] = {1., 1., 1., 0.8};

  //SET LIGHT POSITION
  float light_position[] =  {-1., 1., -1};    // direction of the diffuse light
                                              // (this vector should have length 1)

// For the Adafruit shield, these are the default.
#define TFT_DC  9
#define TFT_CS  10

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Teensy_OpenGL tft = Teensy_OpenGL(TFT_CS, TFT_DC, 8);
uint8_t use_fb = 1;

#define PI_ 3.14159265358979323846
int numc = 8;
int numt = 25;


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
  tft.glPointSize(2);
    
  if(_use_FacetShader == 1){
    tft.glAttachShader(FacetShader);
  } else if(_use_SimpleShader == 1){
    tft.glAttachShader(SimpleVertexShader);
  } else if(_use_SmoothShader == 1) {
    //tft.glAttachShader(SmoothShader,"Phong");
    tft.glAttachShader(SmoothShader,"Gourand");
  }

  tft.glLight(GL_LIGHT0, GL_AMBIENT, light_ambient);
  tft.glLight(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  tft.glLight(GL_LIGHT0, GL_SPECULAR, light_specular);
  tft.glLight(GL_LIGHT0, GL_POSITION, light_position);
  
  tft.useFrameBuffer(1);

}

float angle = -0.;
float angley = -0.;

void loop() {
  tft.glClear(ILI9341_BLACK); 

  reShape();
  
  //tft.glTranslatef(0.0, 3., 0.0);
  tft.glRotatef(angle, 0., 1., 1.f);  //note to self -75 for torus
  //tft.glScalef(0.05, 0.05, 0.05);
  tft.glScalef(0.03, 0.03, 0.03);

    drawFromModel();
  
  tft.setCursor(0,0);
  tft.print(angle);
  tft.updateScreen();

  //nextAngle();
  angle -= 10;
  if(abs(angle) > 350) angle = 0;

  delay(100);
  //Serial.print("Temp: ");
  //Serial.println(tempmonGetTemp());
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
    }
   }
  
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
