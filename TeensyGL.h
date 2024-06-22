/*
    ArduinoGL.h - OpenGL subset for Arduino.
    Created by Fabio de Albuquerque Dela Antonio
    fabio914 at gmail.com
	
	UPDATE:  Modified for use on a Teensy 4 and functions
	expanded for additional primitives and shading based on
	Michael Rule's Uno9341TFT library on GITHUB.  Expanded to
	use additional displays.
 */

#ifndef TeensyGL_h
#define TeensyGL_h

#include "Arduino.h"
#include "SPI.h"
#if __has_include(<RA8875.h>)
	#include "RA8875.h"
	#define ra8875 1
#elif __has_include(<ILI9488_t3.h>)
	#include "ILI9488_t3.h"
	#define ILI9488 1
#elif __has_include(<ILI9341_t3n.h>)
	#include "ILI9341_t3n.h"
	#define ILI9341 1
#elif __has_include(<ILI9341_t3.h>)
	#include "ILI9341_t3.h"
#elif __has_include(<ST7789_t3.h>) 
	#include "ST7789_t3.h"
	#define ST7789 1
#elif __has_include(<ST7735_t3.h>)
	#include "ST7735_t3.h"
	#define ST7735 1
#elif __has_include(<RA8876_t3.h>)
	#include "RA8876_t3.h"
	#define RA8876 1
#elif __has_include(<ILI948x_t4x_p.h>)
	#include "ILI948x_t4x_p.h"
	#define ILI948X 1 
#else
	error "no device selected"
#endif

#ifndef swapGL
#define swapGL(a, b) { typeof(a) t = a; a = b; b = t; }
#endif

typedef enum {
	GL_AMBIENT = 0,
	GL_DIFFUSE,
	GL_SPECULAR,
	GL_POSITION,
	GL_SPOT_CUTOFF, 
	GL_SPOT_DIRECTION, 
	GL_SPOT_EXPONENT, 
	GL_CONSTANT_ATTENUATION, 
	GL_LINEAR_ATTENUATION, 
	GL_QUADRATIC_ATTENUATION,
	GL_LIGHT0
} GLLight;


typedef enum {
    GL_NONE = 0,
    GL_POINTS,
	GL_LINES,
	GL_LINE_STRIP,
	GL_LINE_LOOP,
    GL_QUADS,
	GL_QUAD_STRIP,
	GL_POLYGON,
	GL_TRIANGLES,
    GL_TRIANGLE_STRIP
} GLDrawMode;

typedef enum {
    GL_PROJECTION = 0,
    GL_MODELVIEW
} GLMatrixMode;

typedef enum {
	NONE = 0,
    SimpleVertexShader,
	FacetShader,
	VertexAngleShader,
	SmoothShader
} GLShader;

#define PU8  const uint8_t  *
#define P8   const int8_t   * 
#define PU16 const uint16_t *
#define P16	 const int16_t *

/* Model struct. Pointers to PROGMEM stored vertex, 
   edge, triangle, and edge-map arrays. Numbers denoting
   the length of said arrays. In practice, any number of 
   these pointser may be null. At minimum, a list of vertex
   points is needed to render a model.
*/ 
typedef struct Model {
    uint16_t NVertices;
    uint16_t NEdges;
    uint16_t NFaces;
    P16    vertices;
    PU16   edges;
    PU16   faces;
    P16    vertexNormals;
    P16    faceNormals;
} Model;


/* Masks */
#define GL_COLOR_BUFFER_BIT 0x1

typedef struct {
    float x, y, z, w;   // vertex points
	float nx, ny, nz;	// vertex normals per face vertex count - 2
} GLVertex;

typedef struct {
    int min_x = 0, min_y;   // vertex points
	int max_x, max_y;
	int size_x, size_y;	// vertex normals per face vertex count - 2
} GLAttribute;

#define MAX_VERTICES 950*3
#define MAX_MATRICES 8

#define DEG2RAD (M_PI/180.0)
//#define readUnsignedByte(t)     ((uint16_t)pgm_read_byte(&(t)))

#ifdef __cplusplus

#if defined(ILI9488)
class Teensy_OpenGL : public ILI9488_t3 
{
public:
  Teensy_OpenGL(SPIClass *SPIWire, uint8_t _CS, uint8_t _DC, uint8_t _RST = 255, uint8_t _MOSI=11, uint8_t _SCLK=13, uint8_t _MISO=12);
#elif defined(ILI9341)
class Teensy_OpenGL : public ILI9341_t3n 
{
public:
  Teensy_OpenGL(uint8_t _CS, uint8_t _DC, uint8_t _RST = 255, 
		uint8_t _MOSI=11, uint8_t _SCLK=13, uint8_t _MISO=12);
#elif defined(ra8875)
class Teensy_OpenGL : public  RA8875
{
public:
  Teensy_OpenGL(const uint8_t CSp,const uint8_t RSTp=255,const uint8_t mosi_pin=11,const uint8_t sclk_pin=13,const uint8_t miso_pin=12);
#elif defined(ST7735)
class Teensy_OpenGL : public ST7735_t3
{
public:
  Teensy_OpenGL(uint8_t CS, uint8_t RS, uint8_t SID, uint8_t SCLK, uint8_t RST = -1);
  Teensy_OpenGL(uint8_t CS, uint8_t RS, uint8_t RST = -1);
#elif defined(ST7789)
class Teensy_OpenGL : public ST7789_t3
{
public:
  Teensy_OpenGL(uint8_t CS, uint8_t RS, uint8_t SID, uint8_t SCLK, uint8_t RST = -1);
  Teensy_OpenGL(uint8_t CS, uint8_t RS, uint8_t RST = -1);
#elif defined(RA8876)
class Teensy_OpenGL : public  RA8876_t3
{
public:
  Teensy_OpenGL(const uint8_t CSp,const uint8_t RSTp=255,const uint8_t mosi_pin=11,const uint8_t sclk_pin=13,const uint8_t miso_pin=12);
#elif defined(ILI948X)
class Teensy_OpenGL : public  ILI948x_t4x_p
{
public:
  Teensy_OpenGL(int8_t dc, int8_t cs = -1, int8_t rst = -1);
#endif

	void copyMatrix(float * dest, float * src);
	void multMatrix(float * dest, float * src1, float * src2);
	void pushMatrix(float * m);
	void popMatrix(void);
	void normVector3(float * dest, float * src);
	void crossVector3(float * dest, float * src1, float * src2);
	uint8_t dVector3(uint16_t i, uint16_t j);
	
	/* Matrices */
	void glMatrixMode(GLMatrixMode mode);
	void glMultMatrixf(float * m);
	void glLoadMatrixf(float * m);
	void glLoadIdentity(void);

	void glPushMatrix(void);
	void glPopMatrix(void);

	void glOrtho(float left, float right, float bottom, float top, float zNear, float zFar);
	void gluOrtho2D(float left, float right, float bottom, float top);
	void glFrustum(float left, float right, float bottom, float top, float zNear, float zFar);
	void gluPerspective(float fovy, float aspect, float zNear, float zFar);

	void glRotatef(float angle, float x, float y, float z);
	void glTranslatef(float x, float y, float z);
	void glScalef(float x, float y, float z);
	void gluLookAt(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ);

	/* Vertices */
	void glVertex4fv(float * v);
	void glVertex4f(float x, float y, float z, float w);
	void glVertex3fv(float * v);
	void glVertex3f(float x, float y, float z);

	/* OpenGL */
	//void glUseCanvas(Canvas * c); /* <-- Arduino only */

	void glPointSize(unsigned size);
	void glClear(uint16_t color);
	void glAttachShader(GLShader shader, String shaderName = "");
	void glBegin(GLDrawMode mode);
	void glEnd(void);

	//Arduino openGL
	GLDrawMode glDrawMode = GL_NONE;
	GLShader glShader = NONE;
	GLVertex *glVertices = (GLVertex*)malloc(sizeof(GLVertex) * MAX_VERTICES);
	//GLVertex glVertices[MAX_VERTICES];
	GLAttribute glAttribute;
	
	unsigned int glVerticesCount = 0;
	
	uint16_t draw_order[MAX_VERTICES/3];
	//uint16_t * draw_order = (unsigned int) malloc((MAX_VERTICES/3)*sizeof(unsigned int));

	GLMatrixMode glmatrixMode = GL_PROJECTION;
	float glMatrices[2][16];
	float glMatrixStack[MAX_MATRICES][16];
	unsigned glMatrixStackTop = 0;
	unsigned glPointLength = 1;
	
	void glColor3ub(uint8_t r, uint8_t g, uint8_t b );
	uint16_t glColor = 0xFFFF;


	void glColorT(uint16_t idx, uint8_t r, uint8_t g, uint8_t b );
	uint16_t glColor_T[MAX_VERTICES];
	//uint16_t * glColor_T = (unsigned int) malloc(MAX_VERTICES*sizeof(unsigned int));
	
	void glColorQ(uint16_t idx, uint8_t r, uint8_t g, uint8_t b );
	uint16_t glColor_Q[4] = {0xFFFF,0xFFFF,0xFFFF,0xFFFF};
	
	int16_t thick = 1;
	int16_t offset_thick[11] = {0, 1, -1, 2, -2, 3, -3, 4, -4, 5, -5};
	int NFACES = 0;
	
  /* Basic triangle shader functions. 
   * Extracted and slightly modified from Michael Rule's
   * Uno9341TFT library, Optomized graphics drivers and demos for 
   * Arduino Uno for the 320x240 TFT LCD screens 
   * with the ILI9341 driver, https://github.com/michaelerule/Uno9341TFT
   *   
   * Interpolated color triangles are drawn similarly to regular triangles
   * In that they are broken into horizontal scanlines. For this we need
   * a fast horizontal interpolated line function. Additionally, we 
   * optionally support overdraw, which prevents pixels from the current
   * frame from being over-drawn. This requires skipping some segments
   * of the triangle.
   */
  uint8_t color_map[16];
  	float _div = 256.;
	uint16_t _div1;
	
  void get_triangle_points(Model *M, int16_t *vertices, int16_t i, int16_t **p, int16_t **q, int16_t **r);

  void     interpolateFlood(int16_t x, int16_t y, int16_t i, int16_t stop, int16_t length, uint16_t color1, uint16_t color2);
  void     interpolateFastHLine(int16_t x, int16_t y0, uint16_t w, uint16_t color1, uint16_t color2);
  void     shadeTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color0, uint16_t color1, uint16_t color2);
  void shadeTriangleSmooth(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t idx, uint16_t color0, uint16_t color1, uint16_t color2);
  uint16_t interpolate(uint16_t color1, uint16_t color2, uint16_t alpha);
  void     setColorMap(uint8_t cmap);
  
  float facing_camera(float *p, float *q, float *r);   
  void shadeFaces(GLVertex *vertices, uint16_t *vertex_colors, uint16_t *draw_order);
  void computeTriangleDepths(uint16_t nt, GLVertex *vertices, uint16_t *draw_order, float *depths);
  void updateDrawingOrder(uint16_t nt, GLVertex *vertices, uint16_t *draw_order);
  
  
  //Shading
  
  float getCofactor(float m0, float m1, float m2,
                    float m3, float m4, float m5,
                    float m6, float m7, float m8);
		
  uint16_t adjFaces[1][25];
  uint16_t common[950*3][25];
  
  uint16_t * dups(uint16_t arr[], int n);
  void findAdjacentFaces(uint16_t nvert, uint16_t nface, uint16_t nvertP);
  void findSharedVerts(uint16_t nvert, uint16_t nface, uint16_t nvertP);
  
  //void face_normals(uint16_t *draw_order);
  void face_normals();
  void computeVerticeNormal();
  void vertex_normalize();
  
	// Pass 8-bit (each) R,G,B, get back 16-bit packed color
	static uint16_t color565(uint8_t r, uint8_t g, uint8_t b) {
		return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
	}
	
	//color565toRGB		- converts 565 format 16 bit color to RGB
	static void color565toRGB(uint16_t color, uint8_t &r, uint8_t &g, uint8_t &b) {
		r = (color>>8)&0x00F8;
		g = (color>>3)&0x00FC;
		b = (color<<3)&0x00F8;
	}
	
	void  glLight(GLLight lightNo, GLLight var, float *array);
	float * reflect(float * I, float * N);
	
private:
	uint8_t color_default, color_default_array;
	uint8_t _r, _g, _b;
	float _eyeX, _eyeY, _eyeZ;
	
	String glShaderName;
	
	float ambientR = 1.;
	float ambientG = 1.;
	float ambientB = 1.;
	float ambientIntensity = 0.7;

	float diffuseR = 1.;
	float diffuseG = 1.;
	float diffuseB = 1.;
	float diffuseIntensity = 0.2;
	
	float specularR = 1.;
	float specularG = 1.;
	float specularB = 1.;
	float specularIntensity = 0.;

	float diffuseX = 1.;   // direction of the diffuse light
	float diffuseY = 0.;   // (this vector should have length 1)
	float diffuseZ = 0.;
	
	float glShiniess = 120.0;

	bool _use_lighting = false;
};

#endif
#endif