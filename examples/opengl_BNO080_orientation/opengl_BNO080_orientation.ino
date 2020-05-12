#include "SPI.h"
#include "ILI9488_t3.h"
#include <TeensyGL.h> 
#include "T4_PowerButton.h"

#include <Wire.h>
#include "SparkFun_BNO080_Arduino_Library.h"
BNO080 myIMU;
#define QP14                        0.0000610352f
#define rad2deg                    57.2958f        // constant 180/PI 

// For the Adafruit shield, these are the default.
#define TFT_DC  9
#define TFT_CS  10
#define TFT_RST 8

  //Teensy_OpenGL tft = Teensy_OpenGL(&SPI, TFT_CS, TFT_DC, 8);

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
  Teensy_OpenGL tft = Teensy_OpenGL(&SPI, TFT_CS, TFT_DC, TFT_RST);
uint8_t use_fb = 1;

#include "Steampunk.h"

//UNCOMMENT THE LIGHT COLOR (NOTE USING LIGHT COLOR TO 
//SIMULATE MATERIAL COLORING.  ONLY 1 LIGHT SOURCE FOR NOW
  //copper - taken from
  float light_ambient[] = {.19125, .0735, .0225, 1.0}; //  {r, g, b, Intensity}
  float light_diffuse[] = {.7038, .27048, .0828, 1.0}; // {r, g, b, Intensity}
  float light_specular[] = {.256771, .137622, .137622, 1.0}; // {r, g, b, Intensity}
  //Bronze - taken from
  //float light_ambient[] = {.2125, .1275, .054, 1.0}; //  {r, g, b, Intensity}
  //float light_diffuse[] = {.714, .4284, .1814, 1.0}; // {r, g, b, Intensity}
  //float light_specular[] = {.393548, .271906, .166721, 1.0}; // {r, g, b, Intensity}
  //Brass - taken from
  //float light_ambient[] = {.329412, .223529, .023451, 0.7}; //  {r, g, b, Intensity}
  //float light_diffuse[] = {.780392, .568627, .113725, 0.4}; // {r, g, b, Intensity}  //float light_specular[] = {1., 1., 1., 0.8};

  //SET LIGHT POSITION
  float light_position[] =  {-1., 1., -1};    // direction of the diffuse light
                                              // (this vector should have length 1)

#define PI_ 3.14159265358979323846
int numc = 8;
int numt = 25;

void setup() {
  
  Serial.begin(9600);
  while (!Serial) ; // wait for Arduino Serial Monitor
  Serial.println("OpenGL Test!"); 
  flexRamInfo();

  Serial.begin(9600);
  Serial.println();
  Serial.println("BNO080 Read Example");

  Wire.begin();
  Wire.setClock(400000); //Increase I2C data rate to 400kHz
  myIMU.begin();
  myIMU.enableRotationVector(50); //Send data update every 50ms
  Serial.println(F("Rotation vector enabled"));
  Serial.println(F("Output in form i, j, k, real, accuracy"));

  tft.begin();
  tft.fillScreen(ILI9488_BLACK);
  tft.setTextColor(ILI9488_YELLOW);
  tft.setTextSize(2);
  tft.setRotation(1);
  tft.println("Waiting for Arduino Serial Monitor...");


  delay(1000);

  /* Pass the canvas to the OpenGL environment */
  tft.glClear(ILI9488_BLACK);
  tft.glPointSize(2);

    tft.glAttachShader(FacetShader);

  tft.glLight(GL_LIGHT0, GL_AMBIENT, light_ambient);
  tft.glLight(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  tft.glLight(GL_LIGHT0, GL_SPECULAR, light_specular);
  tft.glLight(GL_LIGHT0, GL_POSITION, light_position);
  
  tft.useFrameBuffer(1);
}

void loop() {
  tft.glClear(ILI9488_BLACK); 

  reShape();
  
  //tft.glTranslatef(0.0, 3., 0.0);

  if (myIMU.dataAvailable() == true)
  {
    float q1 = myIMU.getQuatI();
    float q2 = myIMU.getQuatJ();
    float q3 = myIMU.getQuatK();
    float q0 = myIMU.getQuatReal();
    //q0 *= QP14; q1 *= QP14; q2 *= QP14; q3 *= QP14;  // apply Q point (quats are already unity vector)

   // Euler angles from quaternions (radians)   
   float yaw   =  rad2deg*atan2((q1 * q2 + q0 * q3), ((q0 * q0 + q1 * q1) - 0.5f));   
   float pitch = -rad2deg*asin(2.0f * (q1 * q3 - q0 * q2));
   float roll  =  rad2deg*atan2((q0 * q1 + q2 * q3), ((q0 * q0 + q3 * q3) - 0.5f));
   Serial.printf("%f, %f, %f\n", yaw, pitch, roll);
    
    tft.glRotatef(pitch,  1., .0, 0.f);
    tft.glRotatef(roll, 0., .1, 0.f);
    tft.glRotatef(yaw,  0., 0., 1.f);
    
    drawFromModel();  
    tft.updateScreen();
  }
}

void reShape(){
  tft.glMatrixMode(GL_PROJECTION);
  tft.glLoadIdentity();
    float ar = (float)tft.width() / (float) tft.height();
    if(tft.width() >  tft.height()) {
      tft.glOrtho(-6.0, 6.0, -5.0, 5.0, -5, 5);
    } else {
      tft.glOrtho(-5.0, 5.0, -6.0, 6.0, -5, 5);
    }

  tft.glMatrixMode(GL_MODELVIEW);
  tft.glLoadIdentity();
  tft.glScalef(0.03, 0.03, 0.03);
  tft.glRotatef(180., 0., .0, 1.f);
  tft.glRotatef(90., 1., .0, 0.f);
  tft.glRotatef(-90., 0., 0., 1.f);
}

void nextAngle()
{
  Serial.println("Press anykey to continue");
  while (Serial.read() == -1) ;
  while (Serial.read() != -1) ;
}
