/*
    ArduinoGL.h - OpenGL subset for Arduino.
    Created by Fabio de Albuquerque Dela Antonio
    fabio914 at gmail.com
 */

#include "TeensyGL.h"
#include <SPI.h>
#include <math.h>
#include <stdint.h>
#include "color_maps.h"

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
	#include "Ra8876_Lite.h"
	#include "RA8876_t3.h"
	#define RA8876 1

#endif

#if defined(ILI9488)
Teensy_OpenGL::Teensy_OpenGL(SPIClass *SPIWire, uint8_t _CS, uint8_t _DC, uint8_t _RST, uint8_t _MOSI, uint8_t _SCLK, uint8_t _MISO) : ILI9488_t3(SPIWire, _CS, _DC, _RST, _MOSI, _SCLK, _MISO) 
{
}
#elif defined(ILI9341)
Teensy_OpenGL::Teensy_OpenGL(uint8_t _CS, uint8_t _DC, uint8_t _RST, uint8_t _MOSI, uint8_t _SCLK, uint8_t _MISO) : ILI9341_t3n(  _CS, _DC, _RST, _MOSI, _SCLK, _MISO) 
{
}
#elif defined(ra8875)
Teensy_OpenGL::Teensy_OpenGL(const uint8_t CSp,const uint8_t RSTp,const uint8_t mosi_pin,const uint8_t sclk_pin,const uint8_t miso_pin) : RA8875( CSp, RSTp, mosi_pin, sclk_pin, miso_pin) 
{
}
#elif defined(ST7735)
  Teensy_OpenGL::Teensy_OpenGL(uint8_t CS, uint8_t RS, uint8_t SID, uint8_t SCLK, uint8_t RST) : ST7735_t3( CS,  RS,  SID,  SCLK,  RST)
  {
  }
  Teensy_OpenGL::Teensy_OpenGL(uint8_t CS, uint8_t RS, uint8_t RST) :   ST7735_t3( CS,  RS,  RST)
  {
  }
#elif defined(ST7789)
  Teensy_OpenGL::Teensy_OpenGL(uint8_t CS, uint8_t RS, uint8_t SID, uint8_t SCLK, uint8_t RST) : ST7789_t3( CS,  RS,  SID,  SCLK,  RST)
  {
  }
  Teensy_OpenGL::Teensy_OpenGL(uint8_t CS, uint8_t RS, uint8_t RST) : ST7789_t3( CS,  RS,  RST)
  {
  }
#elif defined(RA8876)
Teensy_OpenGL::Teensy_OpenGL(const uint8_t CSp,const uint8_t RSTp,const uint8_t mosi_pin,const uint8_t sclk_pin,const uint8_t miso_pin) : RA8876_t3( CSp, RSTp, mosi_pin, sclk_pin, miso_pin) 
{
}
#endif

/* Aux functions */
void Teensy_OpenGL::copyMatrix(float * dest, float * src) {
    
    for(int i = 0; i < 16; i++)
        dest[i] = src[i];
}

FLASHMEM
void Teensy_OpenGL::multMatrix(float * dest, float * src1, float * src2) {
    
    int i, j, k;
    float m[16];
    
    for(i = 0; i < 4; i++)
        for(j = 0; j < 4; j++) {
            
            m[i + j * 4] = 0.0;
            
            for(k = 0; k < 4; k++)
                m[i + j * 4] += src1[i + k * 4] * src2[k + j * 4];
        }
    
    for(i = 0; i < 16; i++)
        dest[i] = m[i];
}

void Teensy_OpenGL::pushMatrix(float * m) {
    
    if(glMatrixStackTop < MAX_MATRICES) {
        
        copyMatrix(glMatrixStack[glMatrixStackTop], m);
        glMatrixStackTop++;
    }
}

void Teensy_OpenGL::popMatrix(void) {
    
    if(glMatrixStackTop > 0) {
        
        glMatrixStackTop--;
    }
}

FLASHMEM
GLVertex multVertex(float * m, GLVertex v) {
    
    GLVertex ret;
    
    ret.x = m[0] * v.x + m[4] * v.y + m[8] * v.z + m[12] * v.w;
    ret.y = m[1] * v.x + m[5] * v.y + m[9] * v.z + m[13] * v.w;
    ret.z = m[2] * v.x + m[6] * v.y + m[10] * v.z + m[14] * v.w;
    ret.w = m[3] * v.x + m[7] * v.y + m[11] * v.z + m[15] * v.w;
    
    return ret;
}

FLASHMEM
void Teensy_OpenGL::normVector3(float * dest, float * src) {
    
    float norm;
    register int i;
    
    norm = sqrt(src[0] * src[0] + src[1] * src[1] + src[2] * src[2]);
    
    for(i = 0; i < 3; i++)
        dest[i] = src[i]/norm;
}

FLASHMEM
void Teensy_OpenGL::crossVector3(float * dest, float * src1, float * src2) {
    
    float ret[3];
    register int i;
    
    ret[0] = src1[1] * src2[2] - src1[2] * src2[1];
    ret[1] = src1[2] * src2[0] - src1[0] * src2[2];
    ret[2] = src1[0] * src2[1] - src1[1] * src2[0];
    
    for(i = 0; i < 3; i++)
        dest[i] = ret[i];
}

FLASHMEM
uint8_t Teensy_OpenGL::dVector3(uint16_t i, uint16_t j) {
    
	uint8_t testx = 0, testy = 0, testz = 0;
	
    if(abs(glVertices[i].x - glVertices[j].x) < 0.01) testx = 1;
    if(abs(glVertices[i].y - glVertices[j].y) < 0.01) testy = 1;
    if(abs(glVertices[i].z - glVertices[j].z) < 0.01) testz = 1;

	return testx + testy + testz;
}

/* Matrices */

void Teensy_OpenGL::glMatrixMode(GLMatrixMode mode) {
    if(mode == GL_MODELVIEW || mode == GL_PROJECTION){
        glmatrixMode = mode;
		gluLookAt(0,0,1,0,0,0,0,1,0) ;
	}
}

void Teensy_OpenGL::glMultMatrixf(float * m) {
    multMatrix(glMatrices[glmatrixMode], glMatrices[glmatrixMode], m);
}

void Teensy_OpenGL::glLoadMatrixf(float * m) {
    copyMatrix(glMatrices[glmatrixMode], m);
}

void Teensy_OpenGL::glLoadIdentity(void) {
    
    float m[16];
    int i;
    
    for(i = 0; i < 16; i++)
        if(i % 5 == 0)
            m[i] = 1.0;
        else m[i] = 0.0;
    
    Teensy_OpenGL::glLoadMatrixf(m);
}

void Teensy_OpenGL::glPushMatrix(void) {
    pushMatrix(glMatrices[glmatrixMode]);
}

void Teensy_OpenGL::glPopMatrix(void) {
    popMatrix();
}

FLASHMEM
void Teensy_OpenGL::glOrtho(float left, float right, float bottom, float top, float zNear, float zFar) {
    
    float tx = -(right + left)/(right - left);
    float ty = -(top + bottom)/(top - bottom);
    float tz = -(zFar + zNear)/(zFar - zNear);
    
    float m[16];
    int i;
    
    for(i = 0; i < 16; i++)
        m[i] = 0.0;
    
    m[0] = 2.0/(right - left);
    m[5] = 2.0/(top - bottom);
    m[10] = -2.0/(zFar - zNear);
    m[12] = tx;
    m[13] = ty;
    m[14] = tz;
    m[15] = 1.0;
    
    glMultMatrixf(m);
}

void Teensy_OpenGL::gluOrtho2D(float left, float right, float bottom, float top) {
    glOrtho(left, right, bottom, top, -1.0, 1.0);
}

FLASHMEM
void Teensy_OpenGL::glFrustum(float left, float right, float bottom, float top, float zNear, float zFar) {
    
    float A = (right + left)/(right - left);
    float B = (top + bottom)/(top - bottom);
    float C = -(zFar + zNear)/(zFar - zNear);
    float D = -(2.0 * zFar * zNear)/(zFar - zNear);
    
    float m[16];
    int i;
    
    for(i = 0; i < 16; i++)
        m[i] = 0.0;
    
    m[0] = (2.0 * zNear)/(right - left);
    m[5] = (2.0 * zNear)/(top - bottom);
    m[8] = A;
    m[9] = B;
    m[10] = C;
    m[11] = -1.0;
    m[14] = D;
    
    glMultMatrixf(m);
}

FLASHMEM
void Teensy_OpenGL::gluPerspective(float fovy, float aspect, float zNear, float zFar) {
    
    float aux = tan((fovy/2.0) * DEG2RAD);
    float top = zNear * aux;
    float bottom = -top;
    float right = zNear * aspect * aux;
    float left = -right;
    
    glFrustum(left, right, bottom, top, zNear, zFar);
}

FLASHMEM
void Teensy_OpenGL::glRotatef(float angle, float x, float y, float z) {
    
    float c = cos(DEG2RAD * angle), s = sin(DEG2RAD * angle);
    float nx, ny, nz, norm;
    
    norm = sqrt(x*x + y*y + z*z);
    
    if(norm == 0)
        return;
    
    nx = x/norm;
    ny = y/norm;
    nz = z/norm;
    
    float m[16];
    int i;
    
    for(i = 0; i < 16; i++)
        m[i] = 0.0;
    
    m[0] = nx*nx*(1.0 - c) + c;
    m[1] = ny*nx*(1.0 - c) + nz*s;
    m[2] = nx*nz*(1.0 - c) - ny*s;
    m[4] = nx*ny*(1.0 - c) - nz*s;
    m[5] = ny*ny*(1.0 - c) + c;
    m[6] = ny*nz*(1.0 - c) + nx*s;
    m[8] = nx*nz*(1.0 - c) + ny*s;
    m[9] = ny*nz*(1.0 - c) - nx*s;
    m[10] = nz*nz*(1.0 - c) + c;
    m[15] = 1.0;
    
    glMultMatrixf(m);
}

FLASHMEM
void Teensy_OpenGL::glTranslatef(float x, float y, float z) {
    
    float m[16];
    int i;
    
    for(i = 0; i < 16; i++)
        m[i] = 0.0;
    
    m[0] = 1.0;
    m[5] = 1.0;
    m[10] = 1.0;
    m[12] = x;
    m[13] = y;
    m[14] = z;
    m[15] = 1.0;
    
    glMultMatrixf(m);
}

FLASHMEM
void Teensy_OpenGL::glScalef(float x, float y, float z) {
    
    float m[16];
    int i;
    
    for(i = 0; i < 16; i++)
        m[i] = 0.0;
    
    m[0] = x;
    m[5] = y;
    m[10] = z;
    m[15] = 1.0;
    
    glMultMatrixf(m);
}

FLASHMEM
void Teensy_OpenGL::gluLookAt(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ) {
    
    float dir[3], up[3];
    
    dir[0] = centerX - eyeX;
    dir[1] = centerY - eyeY;
    dir[2] = centerZ - eyeZ;
    
    up[0] = upX;
    up[1] = upY;
    up[2] = upZ;
    
    float n[3], u[3], v[3];
    
    normVector3(n, dir);
    
    crossVector3(u, n, up);
    normVector3(u, u);
    
    crossVector3(v, u, n);
    
    float m[16];
    int i;
    
    for(i = 0; i < 16; i++)
        m[i] = 0.0;
    
    m[0] = u[0];
    m[1] = v[0];
    m[2] = -n[0];
    
    m[4] = u[1];
    m[5] = v[1];
    m[6] = -n[1];
    
    m[8] = u[2];
    m[9] = v[2];
    m[10] = -n[2];
    
    m[15] = 1.0;
    
    glMultMatrixf(m);
    glTranslatef(-eyeX, -eyeY, -eyeZ);
	_eyeX = eyeX;  _eyeY = eyeY; _eyeZ = eyeZ;
}

/* Vertices */

void Teensy_OpenGL::glVertex4fv(float * v) {
    glVertex4f(v[0], v[1], v[2], v[3]);
}

FLASHMEM
void Teensy_OpenGL::glVertex4f(float x, float y, float z, float w) {
    
    GLVertex v;
    
    v.x = x;
    v.y = y;
    v.z = z;
    v.w = w;
	
    if(glVerticesCount < MAX_VERTICES) {
        
        glVertices[glVerticesCount] = v;
        glVerticesCount++;
    }
}

void Teensy_OpenGL::glVertex3fv(float * v) {
    glVertex3f(v[0], v[1], v[2]);
}

void Teensy_OpenGL::glVertex3f(float x, float y, float z) {
    glVertex4f(x, y, z, 1.0);
}



/* OpenGL */

//void glUseCanvas(Canvas * c) {
    //glCanvas = c;
//}

void Teensy_OpenGL::glClear(uint16_t color) {
	#if defined(ra8875)
		clearScreen(color);
	#else
		fillScreen(color);
	#endif
}

void Teensy_OpenGL::glPointSize(unsigned size) {
	if(size < 1) size = 1;
	if(size > 5) size = 5;
    glPointLength = size;
}

void Teensy_OpenGL::glAttachShader(GLShader shader, String shaderName = ""){
	glShader = shader;
	glShaderName = shaderName;
}

void Teensy_OpenGL::glBegin(GLDrawMode mode) {
    glDrawMode = mode;
    glVerticesCount = 0;
	glColor = 0xFFFF;
	for(uint8_t i=0; i<24; i++) {glColor_T[i] = 0xFFFF; }
	for(uint8_t i=0; i<4; i++) {glColor_Q[i] = 0xFFFF; }
	color_default_array = 1;
	color_default = 1;
	NFACES = 0;
	for (uint16_t i=0; i<MAX_VERTICES/3; i++) draw_order[i]=i;
}

FLASHMEM
void Teensy_OpenGL::glEnd(void) {
    
    if(glDrawMode == GL_NONE)
        return;
    
    float modelviewProjection[16];
    multMatrix(modelviewProjection, glMatrices[GL_PROJECTION], glMatrices[GL_MODELVIEW]);
    
    int frameWidth = _width;
    int frameHeight = _height;
	
    
    for(uint16_t i = 0; i < glVerticesCount; i++) {

        GLVertex aux = multVertex(modelviewProjection, glVertices[i]);
        
        aux.x = aux.x/aux.w;
        aux.y = aux.y/aux.w;
        aux.z = aux.z/aux.w;
        
        glVertices[i] = aux;
    }
    
    if(glDrawMode == GL_POINTS) {
        
        for(uint16_t i = 0; i < glVerticesCount; i++) {
            
            GLVertex * aux = &(glVertices[i]);
            
            if(!(glVertices[i].x >= -1.0 && glVertices[i].x <= 1.0))
                continue;
            
            if(!(glVertices[i].y >= -1.0 && glVertices[i].y <= 1.0))
                continue;
            
            if(!(glVertices[i].z >= -1.0 && glVertices[i].z <= 1.0))
                continue;
            
            int px = (((aux->x + 1.0)/2.0) * (frameWidth - 1));
            int py = ((1.0 - ((aux->y + 1.0)/2.0)) * (frameHeight - 1));
            
            for(int x = (px - glPointLength/2.0); x <= (px + glPointLength/2.0); x++)
                for(int y = (py - glPointLength/2.0); y <= (py + glPointLength/2.0); y++)
                    drawPixel(x, y, glColor);  //White for now
        }
		glColor3ub(255,255,255);
    }

    else if(glDrawMode == GL_LINES) {
		
        if(glVerticesCount < 2)
            return;
        
        int px[2], py[2];
            
        for(uint16_t i = 0; i < 2; i++) {
            
            if(!(glVertices[i].z >= -1.0 && glVertices[i].z <= 1.0))
                return;
            
            GLVertex * aux = &(glVertices[i]);
			
			px[i] = (((aux->x + 1.0)/2.0) * (frameWidth - 1));
            py[i] = ((1.0 - ((aux->y + 1.0)/2.0)) * (frameHeight - 1));
        }
		
		int dx = px[1] - px[0];
		int dy = py[1] - py[0];
		for(uint8_t t = 0; t < glPointLength; t++){
			thick = offset_thick[t];
			if(dx == 0){
				drawLine(px[0]+thick, py[0], px[1]+thick, py[1], glColor);
			}
			else if(dy == 0) {
				drawLine(px[0], py[0]+thick, px[1], py[1]+thick, glColor);
			}
			else {
				if(dx < 0 && dy > 0) {
					drawLine(px[0]+thick, py[0]+thick, px[1]+thick, py[1]+thick, glColor);
				} else if(dx > 0 && dy < 0){
					drawLine(px[0]-thick, py[0]-thick, px[1]-thick, py[1]-thick, glColor);
				} else {
					drawLine(px[0]-thick, py[0]+thick, px[1]-thick, py[1]+thick, glColor);
				}
			}
		}
	}
	
    else if(glDrawMode == GL_LINE_STRIP) {
		
        if(glVerticesCount < 2)
            return;
        
        int px[MAX_VERTICES], py[MAX_VERTICES];
            
        for(uint16_t i = 0; i < glVerticesCount; i++) {
            
            if(!(glVertices[i].z >= -1.0 && glVertices[i].z <= 1.0))
                return;
            
            GLVertex * aux = &(glVertices[i]);
			
			px[i] = (((aux->x + 1.0)/2.0) * (frameWidth - 1));
            py[i] = ((1.0 - ((aux->y + 1.0)/2.0)) * (frameHeight - 1));
        }

		for(uint16_t i = 0; i < glVerticesCount-1; i++) {
			int dx = px[i+1] - px[i];
			int dy = py[i+1] - py[i];
			for(uint8_t t = 0; t < glPointLength; t++){
				thick = offset_thick[t];
				if(dx == 0){
					drawLine(px[i]+thick, py[i], px[i+1]+thick, py[i+1], glColor_T[i]);
				}
				else if(dy == 0) {
					drawLine(px[i], py[i]+thick, px[i+1], py[i+1]+thick, glColor_T[i]);
				}
				else {
					if(dx < 0 && dy > 0) {
						drawLine(px[i]+thick, py[i]+thick, px[i+1]+thick, py[i+1]+thick, glColor_T[i]);
					} else if(dx > 0 && dy < 0){
						drawLine(px[i]-thick, py[i]-thick, px[i+1]-thick, py[i+1]-thick, glColor_T[i]);
					} else {
						drawLine(px[i]-thick, py[i]+thick, px[i+1]-thick, py[i+1]+thick, glColor_T[i]);
					}
				}
			}
		}
	}
	
    else if(glDrawMode == GL_LINE_LOOP) {
		
        if(glVerticesCount < 2)
            return;
        
        int px[MAX_VERTICES], py[MAX_VERTICES];
            
        for(uint16_t i = 0; i < glVerticesCount; i++) {
            
            if(!(glVertices[i].z >= -1.0 && glVertices[i].z <= 1.0))
                return;
            
            GLVertex * aux = &(glVertices[i]);
			
			px[i] = (((aux->x + 1.0)/2.0) * (frameWidth - 1));
            py[i] = ((1.0 - ((aux->y + 1.0)/2.0)) * (frameHeight - 1));
        }
		
		for(uint16_t i = 0; i < glVerticesCount-1; i++) {
			int dx = px[i+1] - px[i];
			int dy = py[i+1] - py[i];
			for(uint8_t t = 0; t < glPointLength; t++){
				thick = offset_thick[t];
				if(dx == 0){
					drawLine(px[i]+thick, py[i], px[i+1]+thick, py[i+1], glColor_T[i]);
				}
				else if(dy == 0) {
					drawLine(px[i], py[i]+thick, px[i+1], py[i+1]+thick, glColor_T[i]);
				}
				else {
					if(dx < 0 && dy > 0) {
						drawLine(px[i]+thick, py[i]+thick, px[i+1]+thick, py[i+1]+thick, glColor_T[i]);
					} else if(dx > 0 && dy < 0){
						drawLine(px[i]-thick, py[i]-thick, px[i+1]-thick, py[i+1]-thick, glColor_T[i]);
					} else {
						drawLine(px[i]-thick, py[i]+thick, px[i+1]-thick, py[i+1]+thick, glColor_T[i]);
					}
				}
			}
		}
		
		float dx = px[glVerticesCount-1] - px[0];
		float dy = py[glVerticesCount-1] - py[0];
		for(uint8_t thick = 0; thick < glPointLength; thick++){
			if(dx == 0){
				drawLine(px[glVerticesCount-1]+thick, py[glVerticesCount-1], px[0]+thick, py[0], glColor_T[glVerticesCount-1]);
			}
			else if(dy == 0) {
				drawLine(px[glVerticesCount-1], py[glVerticesCount-1]+thick, px[0], py[0]+thick, glColor_T[glVerticesCount-1]);
			}
			else {
				if(dx < 0 && dy > 0) {
					drawLine(px[glVerticesCount-1]+thick, py[glVerticesCount-1]+thick, px[0]+thick, py[0]+thick, glColor_T[glVerticesCount-1]);
				} else if(dx > 0 && dy < 0){
					drawLine(px[glVerticesCount-1]-thick, py[glVerticesCount-1]-thick, px[0]-thick, py[0]-thick, glColor_T[glVerticesCount-1]);
				} else {
					drawLine(px[glVerticesCount-1]-thick, py[glVerticesCount-1]+thick, px[0]-thick, py[0]+thick, glColor_T[glVerticesCount-1]);
				}
			}
		}
		
	}
	
    else if(glDrawMode == GL_QUADS) {
      // 0---3   4---6
      // |   |   |   |
      // 1---2   5---7

        /* TODO Improve! */
        if(glVerticesCount < 4 && (glVerticesCount % 4 == 0))
            return;
        
        int px[MAX_VERTICES], py[MAX_VERTICES];
            
        for(uint8_t i = 0; i < glVerticesCount; i++) {
            
            if(!(glVertices[i].z >= -1.0 && glVertices[i].z <= 1.0))
                return;
            
            GLVertex * aux = &(glVertices[i]);
            
            px[i] = (((aux->x + 1.0)/2.0) * (frameWidth - 1));
            py[i] = ((1.0 - ((aux->y + 1.0)/2.0)) * (frameHeight - 1));
        }
        
		NFACES = glVerticesCount/4;
		
		if(glShader == SimpleVertexShader) {
			updateDrawingOrder(NFACES, glVertices, draw_order);
			for(uint16_t quad = 0; quad < (glVerticesCount / 4); quad++){
				//uint16_t i = quad*4;
				uint16_t order = draw_order? draw_order[quad]:quad;  //face to draw
				uint16_t i = order*4;
				
				float p[3], q[3], r[3];
				// if triangle is facing the camera, draw it
				p[0] = glVertices[i].x;   p[1] = glVertices[i].y;   p[2] = glVertices[i].z;
				q[0] = glVertices[i+1].x; q[1] = glVertices[i+1].y; q[2] = glVertices[i+1].z;
				r[0] = glVertices[i+2].x; r[1] = glVertices[i+2].y; r[2] = glVertices[i+2].z;
			
				if(facing_camera(p,q,r) > 0){
					shadeTriangle(px[i], py[i], px[i+1], py[i+1], px[i+2], py[i+2], glColor_T[i], glColor_T[i+1], glColor_T[i+2]);
					shadeTriangle(px[i+2], py[i+2], px[i+1], py[i+1], px[i+3], py[i+3], glColor_T[i+2], glColor_T[i+1], glColor_T[i+3]);
				}
			}
		} 
		else if(glShader == FacetShader){
			//vertex normals and normalization
			updateDrawingOrder(NFACES, glVertices, draw_order);
			//face_normals(draw_order);
			face_normals();
			vertex_normalize();
			
			float normColor;
			for(uint16_t quad = 0; quad < glVerticesCount / 4; quad++) {
				uint16_t order = draw_order? draw_order[quad]:quad;  //face to draw
				uint16_t i = order*4;
				normColor = (glVertices[i].nz < 0?0:glVertices[i].nz);
				
				if(normColor <0.001 && glVertices[i].nz != 0 ) normColor = abs(glVertices[i].nz);
				//normColor = abs(glVertices[i].nz);
				uint16_t color = (((uint8_t)(normColor* _r) & 0xF8) << 8) | (((uint8_t)(normColor* _g) & 0xFC) << 3) | ((uint8_t)((normColor* _b)) >> 3);
				/*
				Serial.printf("Indicies %d, %d, %d\n", i, i+1, i+2);
				Serial.printf("\t %d, %d, %d, %f, %x\n", i, px[i], py[i],
					glVertices[i].nz, normColor* _r);
				Serial.printf("\t %d, %d, %d, %f, %x\n", i+1, px[i+1], py[i+1],
					glVertices[i+1].nz, normColor* _g);
				Serial.printf("\t %d, %d, %d, %f, %x\n", i+2, px[i+2], py[i+2],
					glVertices[i+2].nz, normColor* _b);
				*/
				float p[3], q[3], r[3];
				// if triangle is facing the camera, draw it
				p[0] = glVertices[i].x;   p[1] = glVertices[i].y;   p[2] = glVertices[i].z;
				q[0] = glVertices[i+1].x; q[1] = glVertices[i+1].y; q[2] = glVertices[i+1].z;
				r[0] = glVertices[i+2].x; r[1] = glVertices[i+2].y; r[2] = glVertices[i+2].z;
			
				//Serial.println(facing_camera(p,q,r));
			if(facing_camera(p,q,r) > 0)
				//if (glVertices[i].nz >= 0)
					fillTriangle ( px[i], py[i],
							  px[i + 1], py[i + 1],
							  px[i + 2], py[i + 2], color);
					fillTriangle ( px[i+2], py[i+2],
							  px[i + 1], py[i + 1],
							  px[i + 3], py[i +3], color);
			}
		}
		else if(glShader == SmoothShader) {		
			//face normals and normalization
			updateDrawingOrder(NFACES, glVertices, draw_order);
			//face_normals(draw_order);
			face_normals();
			
			if(glShaderName == "Gourand") {
				//vertex normals based on shared vertices
				findSharedVerts(glVerticesCount, NFACES, 4);
				computeVerticeNormal();
			}
			
			vertex_normalize();
			
			for(uint16_t trig = 0; trig < glVerticesCount / 4; trig++) {
				uint16_t order = draw_order? draw_order[trig]:trig;  //face to draw
				uint16_t i = order*4;

				float p[3], q[3], r[3];
				// if triangle is facing the camera, draw it
				p[0] = glVertices[i].x; p[1] = glVertices[i].y; p[2] = glVertices[i].z;
				q[0] = glVertices[i+1].x; q[1] = glVertices[i+1].y; q[2] = glVertices[i+1].z;
				r[0] = glVertices[i+2].x; r[1] = glVertices[i+2].y; r[2] = glVertices[i+2].z;

				if(facing_camera(p,q,r) > 0)		
				//if (glVertices[i].nz >= 0)
					shadeTriangleSmooth ( px[i], py[i],
						px[i + 1], py[i + 1], px[i + 2], py[i + 2], i,
						glColor, glColor, glColor);
					shadeTriangleSmooth ( px[i+2], py[i+2],
						px[i + 1], py[i + 1], px[i+3], py[i+3], i,
						glColor, glColor, glColor);
			}
		}
		else {
			//breaking the quad up into triangles allows for shading and fills
			for(uint16_t quad = 0; quad < (glVerticesCount / 4); quad++){
				uint16_t ptIdx = quad*4;
				uint16_t i = ptIdx;
				if(color_default_array == 0){
						drawLine(px[i], py[i], px[i + 1], py[i + 1], glColor_T[i]);
						drawLine(px[i + 1], py[i + 1], px[i + 2], py[i + 2], glColor_T[i+1]);drawLine(px[i+2], py[i+2], px[i], py[i], glColor_T[i+2]);

						drawLine(px[i+2], py[i+2], px[i + 1], py[i + 1], glColor_T[i+2]);
						drawLine(px[i+1], py[i+1], px[i+3], py[i+3], glColor_T[i+1]);
						drawLine(px[i+3], py[i+3], px[i + 2], py[i + 2], glColor_T[i+3]);
				} else {
						fillTriangle ( px[i], py[i],
								  px[i + 1], py[i + 1],
								  px[i + 2], py[i + 2], glColor);
						fillTriangle ( px[i+2], py[i+2],
								  px[i + 1], py[i + 1],
								  px[i + 3], py[i + 3], glColor);
				}
			}
		}		
    }
    else if(glDrawMode == GL_QUAD_STRIP) {
      // 0---2---4---6
      // |   |   |   |
      // 1---3---5---7

        /* TODO Improve! */
        if(glVerticesCount < 4 && (glVerticesCount % 4 == 0))
            return;
        
        int px[MAX_VERTICES], py[MAX_VERTICES];
            
        for(uint8_t i = 0; i < glVerticesCount; i++) {
            
            if(!(glVertices[i].z >= -1.0 && glVertices[i].z <= 1.0))
                return;
            
            GLVertex * aux = &(glVertices[i]);
            
            px[i] = (((aux->x + 1.0)/2.0) * (frameWidth - 1));
            py[i] = ((1.0 - ((aux->y + 1.0)/2.0)) * (frameHeight - 1));
        }
        
		NFACES = (glVerticesCount/2 ) - 1;
		
		if(glShader == SimpleVertexShader) {
			updateDrawingOrder(NFACES, glVertices, draw_order);
			for(uint16_t quad = 0; quad < NFACES; quad++){
				//uint16_t i = quad*4;
				uint16_t order = draw_order? draw_order[quad]:quad;  //face to draw
				uint16_t i = order*2;

				float p[3], q[3], r[3];
				// if triangle is facing the camera, draw it
				p[0] = glVertices[i].x;   p[1] = glVertices[i].y;   p[2] = glVertices[i].z;
				q[0] = glVertices[i+1].x; q[1] = glVertices[i+1].y; q[2] = glVertices[i+1].z;
				r[0] = glVertices[i+2].x; r[1] = glVertices[i+2].y; r[2] = glVertices[i+2].z;

				if(facing_camera(p,q,r) > 0){
					shadeTriangle(px[i], py[i], px[i+1], py[i+1], px[i+2], py[i+2], glColor_T[i], glColor_T[i+1], glColor_T[i+2]);
					shadeTriangle(px[i+2], py[i+2], px[i+1], py[i+1], px[i+3], py[i+3], glColor_T[i+2], glColor_T[i+1], glColor_T[i+3]);
				}
			}
		} 
		else if(glShader == FacetShader){
			//vertex normals and normalization
			updateDrawingOrder(NFACES, glVertices, draw_order);
			//face_normals(draw_order);
			face_normals();
			vertex_normalize();
			
			float normColor;
			for(uint16_t quad = 0; quad < NFACES; quad++) {
				uint16_t order = draw_order? draw_order[quad]:quad;  //face to draw
				uint16_t i = order*2;
				normColor = (glVertices[i].nz < 0?0:glVertices[i].nz);
				
				if(normColor <0.001 && glVertices[i].nz != 0 ) normColor = abs(glVertices[i].nz);
				//normColor = abs(glVertices[i].nz);
				uint16_t color = (((uint8_t)(normColor* _r) & 0xF8) << 8) | (((uint8_t)(normColor* _g) & 0xFC) << 3) | ((uint8_t)((normColor* _b)) >> 3);
				/*
				Serial.printf("Indicies %d, %d, %d\n", i, i+1, i+2);
				Serial.printf("\t %d, %d, %d, %f, %x\n", i, px[i], py[i],
					glVertices[i].nz, normColor* _r);
				Serial.printf("\t %d, %d, %d, %f, %x\n", i+1, px[i+1], py[i+1],
					glVertices[i+1].nz, normColor* _g);
				Serial.printf("\t %d, %d, %d, %f, %x\n", i+2, px[i+2], py[i+2],
					glVertices[i+2].nz, normColor* _b);
				*/
				float p[3], q[3], r[3];
				// if triangle is facing the camera, draw it
				p[0] = glVertices[i].x;   p[1] = glVertices[i].y;   p[2] = glVertices[i].z;
				q[0] = glVertices[i+1].x; q[1] = glVertices[i+1].y; q[2] = glVertices[i+1].z;
				r[0] = glVertices[i+2].x; r[1] = glVertices[i+2].y; r[2] = glVertices[i+2].z;

				if(facing_camera(p,q,r) > 0){
				//if (glVertices[i].nz >= 0)
					fillTriangle ( px[i], py[i],
							  px[i + 1], py[i + 1],
							  px[i + 2], py[i + 2], color);
					fillTriangle ( px[i+2], py[i+2],
							  px[i + 1], py[i + 1],
							  px[i + 3], py[i +3], color);
				}
			}
		}
		else if(glShader == SmoothShader) {		
			//face normals and normalization
			updateDrawingOrder(NFACES, glVertices, draw_order);
			//face_normals(draw_order);
			face_normals();
			
			if(glShaderName == "Gourand") {
				//vertex normals based on shared vertices
				findSharedVerts(glVerticesCount, NFACES, 4);
				computeVerticeNormal();
			}
			
			vertex_normalize();
			
			for(uint16_t trig = 0; trig < NFACES; trig++) {
				uint16_t order = draw_order? draw_order[trig]:trig;  //face to draw
				uint16_t i = order;
				
				float p[3], q[3], r[3];
				// if triangle is facing the camera, draw it
				// if triangle is facing the camera, draw it
				p[0] = glVertices[i].x;   p[1] = glVertices[i].y;   p[2] = glVertices[i].z;
				q[0] = glVertices[i+1].x; q[1] = glVertices[i+1].y; q[2] = glVertices[i+1].z;
				r[0] = glVertices[i+2].x; r[1] = glVertices[i+2].y; r[2] = glVertices[i+2].z;

				if(facing_camera(p,q,r) > 0){					
				//if (glVertices[i].nz >= 0)
					shadeTriangleSmooth ( px[i], py[i],
						px[i + 1], py[i + 1], px[i + 2], py[i + 2], i,
						glColor, glColor, glColor);
					shadeTriangleSmooth ( px[i+2], py[i+2],
						px[i + 1], py[i + 1], px[i+3], py[i+3], i,
						glColor, glColor, glColor);
				}
			}
		}
		else {
			//breaking the quad up into triangles allows for shading and fills
			// 0---2---4
			// |   |   |
			// 1---3---5
			for(uint16_t quad = 0; quad < (NFACES); quad++){
				uint16_t ptIdx = quad*2;
				uint16_t i = ptIdx;
				if(color_default_array == 0){
						drawLine(px[i], py[i], px[i + 1], py[i + 1], glColor_T[i]);
						drawLine(px[i + 1], py[i + 1], px[i + 2], py[i + 2], glColor_T[i+1]);drawLine(px[i+2], py[i+2], px[i], py[i], glColor_T[i+2]);

						drawLine(px[i+2], py[i+2], px[i + 1], py[i + 1], glColor_T[i+2]);
						drawLine(px[i+1], py[i+1], px[i+3], py[i+3], glColor_T[i+1]);
						drawLine(px[i+3], py[i+3], px[i + 2], py[i + 2], glColor_T[i+3]);
				} else {
						fillTriangle ( px[i], py[i],
								  px[i + 1], py[i + 1],
								  px[i + 2], py[i + 2], glColor);
						fillTriangle ( px[i+2], py[i+2],
								  px[i + 1], py[i + 1],
								  px[i + 3], py[i + 3], glColor);
				}
			}
		}		
    }
    else if(glDrawMode == GL_POLYGON) {

        /* TODO Improve! */
        if(glVerticesCount < 2)
            return;
        
        int px[MAX_VERTICES], py[MAX_VERTICES];
            
        for(uint16_t i = 0; i < glVerticesCount; i++) {
            
            if(!(glVertices[i].z >= -1.0 && glVertices[i].z <= 1.0))
                return;
            
            GLVertex * aux = &(glVertices[i]);
            
            px[i] = (((aux->x + 1.0)/2.0) * (frameWidth - 1));
            py[i] = ((1.0 - ((aux->y + 1.0)/2.0)) * (frameHeight - 1));
        }
        
		uint8_t idxQ = 0;
        for(uint16_t i = 0; i < glVerticesCount; i++) {
            uint16_t next = (i + 1 == glVerticesCount) ? 0:(i + 1);
            drawLine(px[i], py[i], px[next], py[next], glColor_Q[idxQ]);
			idxQ += 1;
			if(next == 0) idxQ = 0;
        }
	}
    
    else if(glDrawMode == GL_TRIANGLES) {

		/* TODO Improve! */
        if(glVerticesCount < 3)
            return;
        
        int px[MAX_VERTICES], py[MAX_VERTICES];
		
		NFACES = glVerticesCount/3;

        for(uint16_t i = 0; i < glVerticesCount; i++) {
            
            if(!(glVertices[i].z >= -1.0 && glVertices[i].z <= 1.0))
                return;
            
            GLVertex * aux = &(glVertices[i]);
            
            px[i] = (((aux->x + 1.0)/2.0) * (frameWidth - 1));
            py[i] = ((1.0 - ((aux->y + 1.0)/2.0)) * (frameHeight - 1));

        }
		
		  glAttribute.max_x = glAttribute.max_x = px[0];
		  glAttribute.min_y = glAttribute.max_y = py[0];
		  for (int i = 0; i < glVerticesCount; i++) {
			if (px[i] < glAttribute.min_x) glAttribute.min_x = px[i];
			if (px[i] > glAttribute.max_x) glAttribute.max_x = px[i];
			if (py[i] < glAttribute.min_y) glAttribute.min_y = py[i];
			if (py[i] > glAttribute.max_y) glAttribute.max_y = py[i];
		  }
		glAttribute.size_x = glAttribute.max_x-glAttribute.min_x;
		glAttribute.size_y = glAttribute.max_y-glAttribute.min_y;
 
		if(glShader == SimpleVertexShader) {

			for(uint16_t trig = 0; trig < NFACES; trig++) {
				uint16_t i = trig*3;
				shadeTriangle(px[i], py[i], px[i+1], py[i+1], px[i+2], py[i+2], glColor_T[i], glColor_T[i+1], glColor_T[i+2]);
			}
		} 
		else if(glShader == FacetShader){
			//face normals and normalization
			updateDrawingOrder(NFACES, glVertices, draw_order);
			//face_normals(draw_order);
			face_normals();
			vertex_normalize();
			
			float normColor, normColor1, normColor2;
			uint16_t color, color1, color2;
			for(uint16_t trig = 0; trig < glVerticesCount / 3; trig++) {
				uint16_t order = draw_order? draw_order[trig]:trig;  //face to draw
				uint16_t i = order*3;
				
				normColor = (glVertices[i].nz < 0?0:glVertices[i].nz);
					
				if(normColor <0.001 && glVertices[i].nz != 0 ) normColor = abs(glVertices[i].nz);
					color = (((uint8_t)(normColor* _r) & 0xF8) << 8) | (((uint8_t)(normColor* _g) & 0xFC) << 3) | ((uint8_t)((normColor* _b)) >> 3);		
				float p[3], q[3], r[3];
				// if triangle is facing the camera, draw it
				p[0] = glVertices[i].x; p[1] = glVertices[i].y; p[2] = glVertices[i].z;
				q[0] = glVertices[i+1].x; q[1] = glVertices[i+1].y; q[2] = glVertices[i+1].z;
				r[0] = glVertices[i+2].x; r[1] = glVertices[i+2].y; r[2] = glVertices[i+2].z;
			
				if(facing_camera(p,q,r) > 0)
					fillTriangle ( px[i], py[i],
						px[i + 1], py[i + 1],
						px[i + 2], py[i + 2], color);
			}
		} 
		else if(glShader == SmoothShader) {		
			//face normals and normalization
			updateDrawingOrder(NFACES, glVertices, draw_order);
			//face_normals(draw_order);
			face_normals();
			
			if(glShaderName == "Gourand") {
				//vertex normals based on shared vertices
				findSharedVerts(glVerticesCount, NFACES, 3);
				computeVerticeNormal();
			}
			
			vertex_normalize();
			
			for(uint16_t trig = 0; trig < glVerticesCount / 3; trig++) {
				uint16_t order = draw_order? draw_order[trig]:trig;  //face to draw
				uint16_t i = order*3;

				float p[3], q[3], r[3];
				// if triangle is facing the camera, draw it
				p[0] = glVertices[i].x; p[1] = glVertices[i].y; p[2] = glVertices[i].z;
				q[0] = glVertices[i+1].x; q[1] = glVertices[i+1].y; q[2] = glVertices[i+1].z;
				r[0] = glVertices[i+2].x; r[1] = glVertices[i+2].y; r[2] = glVertices[i+2].z;

				if(facing_camera(p,q,r) > 0)
					shadeTriangleSmooth ( px[i], py[i],
						px[i + 1], py[i + 1],
						px[i + 2], py[i + 2], i, glColor, glColor, glColor);
			}

		} else {
			for(uint16_t trig = 0; trig < ((uint8_t) (glVerticesCount / 3)); trig++){
				uint16_t i = trig*3;
				if(color_default_array == 0){
						drawLine(px[i], py[i], px[i + 1], py[i + 1], glColor_T[i]);
						drawLine(px[i], py[i], px[i + 2], py[i + 2], glColor_T[i+1]);
						drawLine(px[i + 1], py[i + 1], px[i + 2], py[i + 2], glColor_T[i+2]);
				} else {
						fillTriangle ( px[i], py[i],
								  px[i + 1], py[i + 1],
								  px[i + 2], py[i + 2], glColor);
				}
			}
		}
    }
    else if(glDrawMode == GL_TRIANGLE_STRIP) {

		/* TODO Improve! */
        if(glVerticesCount < 3)
            return;
        
        int px[MAX_VERTICES], py[MAX_VERTICES];
		
		NFACES = glVerticesCount - 2;
        
        for(uint16_t i = 0; i < glVerticesCount; i++) {
            
            if(!(glVertices[i].z >= -1.0 && glVertices[i].z <= 1.0))
                return;
            
            GLVertex * aux = &(glVertices[i]);
            
            px[i] = (((aux->x + 1.0)/2.0) * (frameWidth - 1));
            py[i] = ((1.0 - ((aux->y + 1.0)/2.0)) * (frameHeight - 1));
        }

 
		if(glShader == SimpleVertexShader) {
			for(uint16_t i = 0; i < glVerticesCount - 2; i++) {
				shadeTriangle(px[i], py[i], px[i+1], py[i+1], px[i+2], py[i+2], glColor_T[i], glColor_T[i+1], glColor_T[i+2]);
			}
		} 
		else if(glShader == FacetShader){
			//vertex normals and normalization
			updateDrawingOrder(NFACES, glVertices, draw_order);
			//face_normals(draw_order);
			face_normals();
			vertex_normalize();
			
			float normColor;
			for(uint16_t trig = 0; trig < NFACES; trig++) {
				uint16_t order = draw_order? draw_order[trig]:trig;  //face to draw
				uint16_t i = order;
				
				normColor = (glVertices[i].nz < 0?0:glVertices[i].nz);
				if(normColor <0.001 && glVertices[i].nz != 0 ) normColor = abs(glVertices[i].nz);
				uint16_t color = (((uint8_t)(normColor* _r) & 0xF8) << 8) | (((uint8_t)(normColor* _g) & 0xFC) << 3) | ((uint8_t)((normColor* _b)) >> 3);

				float p[3], q[3], r[3];
				// if triangle is facing the camera, draw it
				p[0] = glVertices[i].x; p[1] = glVertices[i].y; p[2] = glVertices[i].z;
				q[0] = glVertices[i+1].x; q[1] = glVertices[i+1].y; q[2] = glVertices[i+1].z;
				r[0] = glVertices[i+2].x; r[1] = glVertices[i+2].y; r[2] = glVertices[i+2].z;
			
				float cameraTest;
				if(i % 2) {
					cameraTest = facing_camera(p,q,r);
				} else {
					cameraTest = facing_camera(q,p,r);
				}
				if(cameraTest > 0){
					fillTriangle ( px[i], py[i],
						  px[i + 1], py[i + 1],
						  px[i + 2], py[i + 2], color);						  
				}
			}
		}
		else if(glShader == SmoothShader) {		
			//face normals and normalization
			updateDrawingOrder(NFACES, glVertices, draw_order);
			//face_normals(draw_order);
			face_normals();
			
			if(glShaderName == "Gourand") {
				//vertex normals based on shared vertices
				findSharedVerts(glVerticesCount, NFACES, 3);
				computeVerticeNormal();
			}
			
			vertex_normalize();
			
			for(uint16_t trig = 0; trig < NFACES; trig++) {
				uint16_t order = draw_order? draw_order[trig]:trig;  //face to draw
				uint16_t i = order;

				float p[3], q[3], r[3];
				// if triangle is facing the camera, draw it
				p[0] = glVertices[i].x; p[1] = glVertices[i].y; p[2] = glVertices[i].z;
				q[0] = glVertices[i+1].x; q[1] = glVertices[i+1].y; q[2] = glVertices[i+1].z;
				r[0] = glVertices[i+2].x; r[1] = glVertices[i+2].y; r[2] = glVertices[i+2].z;

				float cameraTest;
				if(i % 2) {
					cameraTest = facing_camera(p,q,r);
				} else {
					cameraTest = facing_camera(q,p,r);
				}
				if(cameraTest > 0){
					shadeTriangleSmooth ( px[i], py[i],
						px[i + 1], py[i + 1],
						px[i + 2], py[i + 2], i, glColor, glColor, glColor);
				}
			}
		}

		else {
			for(uint16_t trig = 0; trig < (glVerticesCount  - 2); trig++){
				uint16_t i = trig;
				if(color_default_array == 0){
						drawLine(px[i], py[i], px[i + 1], py[i + 1], glColor_T[i]);
						drawLine(px[i+1], py[i+1], px[i + 2], py[i + 2], glColor_T[i+1]);
						drawLine(px[i], py[i], px[i + 2], py[i + 2], glColor_T[i+2]);
				} else {
						fillTriangle ( px[i], py[i],
								  px[i + 1], py[i + 1],
								  px[i + 2], py[i + 2], glColor);
				}
			}
		}
    }
}

void Teensy_OpenGL::glColor3ub(uint8_t r, uint8_t g, uint8_t b ) {  //not really openGL format
	_r = r;
	_g = g;
	_b = b;
	glColor = color565(r, g, b);
	color_default_array = 1;
}

void Teensy_OpenGL::glColorT(uint16_t idx, uint8_t r, uint8_t g, uint8_t b ) {  //not really openGL format
	glColor_T[idx] = color565(r, g, b);
	color_default_array = 0;
}

void Teensy_OpenGL::glColorQ(uint16_t idx, uint8_t r, uint8_t g, uint8_t b ) {  //not really openGL format
	glColor_Q[idx] = color565(r, g, b);
}


/*
 * <https://computergraphics.stackexchange.com/questions/4031/programmatically-generating-vertex-normals> 
 */
FLASHMEM
//void Teensy_OpenGL::face_normals(uint16_t *draw_order) 
void Teensy_OpenGL::face_normals() 
{ 		
	 float ba[3], ca[3];
	 float vn[4];
	 uint16_t ptIdx;

	for(uint8_t j = 0; j< 4; j++) vn[j] = 0.0;

	if( glDrawMode == GL_TRIANGLES ||  glDrawMode == GL_QUADS || glDrawMode == GL_QUAD_STRIP) {	
		 for( int i=0; i < NFACES; i++ )
		 {
			//uint8_t ptIdx = i*3;
			//uint16_t order = draw_order? draw_order[i]:i;  //face to draw
			if(glDrawMode == GL_QUADS) {
				//ptIdx = order*4;
				ptIdx = i * 4;
			} else if( glDrawMode == GL_QUAD_STRIP){
				ptIdx = i * 2;
			} else {
				//ptIdx = order*3;
				ptIdx = i *3;
			}

			//Serial.printf("Face:%d %f, %f, %f\n", i, glVertices[ptIdx].x,glVertices[ptIdx].y, glVertices[ptIdx].z);
			//Serial.printf("Points:%d %f, %f, %f\n", i, glVertices[ptIdx+1].x,glVertices[ptIdx+1].y, glVertices[ptIdx+1].z);
			//Serial.printf("Points:%d %f, %f, %f\n", i, glVertices[ptIdx+2].x,glVertices[ptIdx+2].y, glVertices[ptIdx+2].z);

			ba[0] = glVertices[ptIdx+1].x - glVertices[ptIdx].x;
			ba[1] = glVertices[ptIdx+1].y - glVertices[ptIdx].y;		
			ba[2] = glVertices[ptIdx+1].z - glVertices[ptIdx].z;

			ca[0] = glVertices[ptIdx+2].x - glVertices[ptIdx].x;
			ca[1] = glVertices[ptIdx+2].y - glVertices[ptIdx].y;		
			ca[2] = glVertices[ptIdx+2].z - glVertices[ptIdx].z;
			
			//vertex normals
			crossVector3(vn, ba, ca);
			
			glVertices[ptIdx].nx = vn[0]; 
			glVertices[ptIdx].ny = vn[1];
			glVertices[ptIdx].nz = vn[2];
			glVertices[ptIdx+1].nx = vn[0]; 
			glVertices[ptIdx+1].ny = vn[1];
			glVertices[ptIdx+1].nz = vn[2];
			glVertices[ptIdx+2].nx = vn[0]; 
			glVertices[ptIdx+2].ny = vn[1];
			glVertices[ptIdx+2].nz = vn[2];
			
			if(glDrawMode == GL_QUADS || glDrawMode == GL_QUAD_STRIP) {
				glVertices[ptIdx+3].nx = vn[0]; 
				glVertices[ptIdx+3].ny = vn[1];
				glVertices[ptIdx+3].nz = vn[2];
			}
			//Serial.printf("\tVn: (%d) %f, %f, %f\n", i, glVertices[ptIdx].nx , glVertices[ptIdx].ny, glVertices[ptIdx].nz);
		 }

	} 
	
	else if( glDrawMode == GL_TRIANGLE_STRIP ) {
		 for( int i=0; i < NFACES; i++ )
		 {
			ptIdx = i;
			//Serial.printf("Points:%d %f, %f, %f\n", i, glVertices[i].x,glVertices[ptIdx].y, glVertices[ptIdx].z);
			//Serial.printf("Points:%d %f, %f, %f\n", i, glVertices[i+1].x,glVertices[ptIdx+1].y, glVertices[ptIdx+1].z);
			//Serial.printf("Points:%d %f, %f, %f\n", i, glVertices[ptIdx+2].x,glVertices[ptIdx+2].y, glVertices[ptIdx+2].z);


				ba[0] = glVertices[ptIdx+1].x - glVertices[ptIdx].x;
				ba[1] = glVertices[ptIdx+1].y - glVertices[ptIdx].y;		
				ba[2] = glVertices[ptIdx+1].z - glVertices[ptIdx].z;

				ca[0] = glVertices[ptIdx+2].x - glVertices[ptIdx].x;
				ca[1] = glVertices[ptIdx+2].y - glVertices[ptIdx].y;		
				ca[2] = glVertices[ptIdx+2].z - glVertices[ptIdx].z;
				
				//vertex normals
				crossVector3(vn, ba, ca);
				
			if(i % 2 == 0) vn[2] = -vn[2];
			
			glVertices[ptIdx].nx = vn[0]; 
			glVertices[ptIdx].ny = vn[1];
			glVertices[ptIdx].nz = vn[2];
			glVertices[ptIdx+1].nx = vn[0]; 
			glVertices[ptIdx+1].ny = vn[1];
			glVertices[ptIdx+1].nz = vn[2];
			glVertices[ptIdx+2].nx = vn[0]; 
			glVertices[ptIdx+2].ny = vn[1];
			glVertices[ptIdx+2].nz = vn[2];
			
			//Serial.printf("\t(face normal) Vn: (%d) %f, %f, %f\n", i, vn[0], vn[1], vn[2]);
		 }
	}
	
}

FLASHMEM
void Teensy_OpenGL::computeVerticeNormal()
{

	for( uint16_t i=0; i < glVerticesCount; i++ )
	{
		//Serial.printf("%d(i), %f, %f, %f\n",i, glVertices[i].nx,glVertices[i].ny,glVertices[i].nz);
		for(uint16_t vcount = 1; vcount < common[i][0]; vcount++)
		{
			uint16_t ptIdx = common[i][vcount];

			glVertices[i].nx += glVertices[ptIdx].nx; 
			glVertices[i].ny += glVertices[ptIdx].ny;
			glVertices[i].nz += glVertices[ptIdx].nz;
			//Serial.printf("%d(i), %d(vcount), %d(idx), %f, %f, %f\n",i, vcount, ptIdx, glVertices[i].nx,glVertices[i].ny,glVertices[i].nz);
		
		}
		//Serial.printf("\n");
		glVertices[i].nx /= (common[i][0]);
		glVertices[i].ny /= (common[i][0]);
		glVertices[i].nz /= (common[i][0]);
	}
	
	//for( uint16_t i=0; i < glVerticesCount; i++ ) Serial.printf("%d, %f, %f, %f\n",i, glVertices[i].nx,glVertices[i].ny,glVertices[i].nz);

}



FLASHMEM
void Teensy_OpenGL::vertex_normalize()
{
	for( int i=0; i < glVerticesCount; i++ )
	 {
		//vector normalization
		//normVector3(vnn, vn);
		float norm;
		//Serial.printf("%d, %f, %f, %f\n", i, glVertices[i].nx, glVertices[i].ny, glVertices[i].nz);
		norm = sqrt(glVertices[i].nx * glVertices[i].nx  +  glVertices[i].ny * glVertices[i].ny + glVertices[i].nz * glVertices[i].nz);
 		
		glVertices[i].nx /= norm; 
		glVertices[i].ny /= norm;
		glVertices[i].nz /= norm;
		//Serial.printf("\t(normalize) %f, %f, %f, (%f)\n\n", glVertices[i].nx, glVertices[i].ny, glVertices[i].nz, norm);
	 } 
	 
}
 


///////////////////////////////////////////////////////////////////////////////
// compute cofactor of 3x3 minor matrix without sign
// input params are 9 elements of the minor matrix
// NOTE: The caller must know its sign.
///////////////////////////////////////////////////////////////////////////////
float Teensy_OpenGL::getCofactor(float m0, float m1, float m2,
                           float m3, float m4, float m5,
                           float m6, float m7, float m8)
{
    return m0 * (m4 * m8 - m5 * m7) -
           m1 * (m3 * m8 - m5 * m6) +
           m2 * (m3 * m7 - m4 * m6);
}

////////////////////////////////////////////////////////////////////////
//  3D drawing commands ported from from Michael Rule's Uno9341TFT library
////////////////////////////////////////////////////////////////////////
#define readUnsignedByte(t)     ((uint16_t)pgm_read_word(&(t)))
void Teensy_OpenGL::get_triangle_points(Model *M, int16_t *vertices, int16_t i, int16_t **p, int16_t **q, int16_t **r) {
    // Get the vertex indecies for the triangle
    PU16 t = &M->faces[i*3];
    uint16_t pi = readUnsignedByte(t[0]);
    uint16_t qi = readUnsignedByte(t[1]);
    uint16_t ri = readUnsignedByte(t[2]);
    // get the  X and Y coordinates for the triangle
    *p = &vertices[pi*3];
    *q = &vertices[qi*3];
    *r = &vertices[ri*3];
} 

float Teensy_OpenGL::facing_camera(float *p, float *q, float *r) {
    return (r[0]-p[0])*(q[1]-p[1])<((q[0]-p[0])*(r[1]-p[1]));
}
 

////////////////////////////////////////////////////////////////////////
// Triangle shaders
////////////////////////////////////////////////////////////////////////


/*  Computes convex combination of color1 and color2 with weight
 *  Weight is normalizes s.t. [0,1] maps to [0,256]
 */
uint16_t Teensy_OpenGL::interpolate(uint16_t color1, uint16_t color2, uint16_t alpha) {
  // The clean way: break out the RGB components and reassemble
  return color1 * alpha + color2 * (32-alpha) >> 5;
  
  //if(color1 == color2) return color2;
  
  uint8_t r10, r20, g10, g20, b10, b20, rn, gn, bn;
  
  color565toRGB(color1, r10, g10, b10);
  color565toRGB(color2, r20, g20, b20);
    Serial.printf("\t\t(rgb10) %d, %d, %d\n", r10, g10, b10);
    Serial.printf("\t\t(rgb20) %d, %d, %d\n", r20, g20, b20);
 
  r10 *= alpha; g10 *= alpha; b10 *= alpha;
  r20 *= (_div1-alpha) >>5; g20 *= (_div1-alpha )>>5; b20 *= (_div1-alpha)>>5;
  
    Serial.printf("\t\t\t(rgb1) %d, %d, %d\n", r10, g10, b10);
    Serial.printf("\t\t\t(rgb2) %d, %d, %d\n", r20, g20, b20);
  
  rn = (r10 + r20); if(rn > 255) rn = 255;
  gn = (g10 + g20); if(gn > 255) gn = 255;
  bn = (b10 + b20); if(bn > 255) bn = 255;
    Serial.printf("\t\t(rgbn) %d, %d, %d, %d\n", rn, gn, bn, color565(rn, gn, bn));

  return color565(rn, gn, bn);
}


// Horizontal fill of a segment with color interpolation
void Teensy_OpenGL::interpolateFlood(int16_t x, int16_t y, int16_t i, int16_t stop, int16_t length, uint16_t color1, uint16_t color2)
{
    uint16_t alpha = 0xff;
	_div1 = 32;
    while (i< stop) {
        uint8_t weight = i*_div1/length;
        //if (weight != alpha) {
            alpha = weight;
            uint16_t c = interpolate(color1, color2, alpha);
			Serial.printf("\t\t%d (i), %d\n", i, c);
			drawPixel(i+x, y , c);
        //}
        i++;
    }
}

// Fast horizontal line supporting overdraw and interpolation
// Does not support masking
void Teensy_OpenGL::interpolateFastHLine(int16_t x, int16_t y, uint16_t length, uint16_t color1, uint16_t color2) {
    if (length < 1) return;
    interpolateFlood(x, y, 0, length, length,color1,color2);
	return;

}

// Shade a triangle with three colors
// based on triangle Barycentric coordinates
// https://codeplea.com/triangular-interpolation
//
FLASHMEM
void Teensy_OpenGL::shadeTriangle ( 
          int16_t x0, int16_t y0,
		  int16_t x1, int16_t y1,
		  int16_t x2, int16_t y2, 
          uint16_t color0, 
          uint16_t color1, 
          uint16_t color2) 
{
    int16_t a, b, y, last;
	
    if (y0 > y1) { swapGL(y0, y1); swapGL(x0, x1); swapGL(color0,color1);}
    if (y1 > y2) { swapGL(y2, y1); swapGL(x2, x1); swapGL(color2,color1);}
    if (y0 > y1) { swapGL(y0, y1); swapGL(x0, x1); swapGL(color0,color1);}
	
	if(y0 == y2) { // Handle awkward all-on-same-line case as its own thing
		a = b = x0;
		if(x1 < a)      a = x1;
		else if(x1 > b) b = x1;
		if(x2 < a)      a = x2;
		else if(x2 > b) b = x2;
		drawFastHLine(a, y0, b-a+1, color0);
		return;
	  }
	
    int16_t
		dx01 = x1 - x0,
		dy01 = y1 - y0,
		dx02 = x2 - x0,
		dy02 = y2 - y0,
		dx12 = x2 - x1,
		dy12 = y2 - y1;
    int32_t
		sa   = 0,
		sb   = 0;
	
  // For upper part of triangle, find scanline crossings for segments
  // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
  // is included here (and second loop will be skipped, avoiding a /0
  // error there), otherwise scanline y1 is skipped here and handled
  // in the second loop...which also avoids a /0 error here if y0=y1
  // (flat-topped triangle).
	
    if(y1 == y2) last = y1;   // Include y1 scanline
    else         last = y1-1; // Skip the y1 scanline

    // Skip the first line to avoid triangle overlap in meshes
    sa += dx01;
    sb += dx02;
	//barycenteric deltas
	int16_t
		cdy12 = (y1-y2),
		cdx21 = (x2-x1),
		cdx02 = (x0-x2),
		cdy02 = (y0-y2),
		cdy21 = y2-y1,
		cdy10 = y1-y0,
		cdy20 = y2-y0;
	float barydenom = (float)(x0*cdy21+x1*cdy02+x2*cdy10);
	
	uint8_t r0, r1, r2, g0, g1, g2, b0, b1, b2, rp, gp, bp;
	color565toRGB(color0, r0, g0, b0);
	color565toRGB(color1, r1, g1, b1);
	color565toRGB(color2, r2, g2, b2);
	
    for(y=y0+1; y<=last; y++) {
        a   = x0 + sa / dy01;
        b   = x0 + sb / dy02;
        if(a > b) {
            swapGL(a,b);
        }
        sa += dx01;
        sb += dx02;

        //interpolateFastHLine(a, y, b-a+1, colorA, colorB);
		uint16_t ic = 0;
		while (ic< b-a+1) {
			float w1 = (float)((ic+a)*cdy21+x1*(y-y2)+x2*(y1-y))/barydenom;
			float w2 = -(float)((ic+a)*cdy20+x0*(y-y2)+x2*(y0-y))/barydenom;
			float w3 = 1.0 - w1 - w2;

			rp = r0*w1 + r1*w2 + r2*w3;
			bp = b0*w1 + b1*w2 + b2*w3;
			gp = g0*w1 + g1*w2 + g2*w3;
			uint16_t colorp = color565(rp, gp, bp);
			drawPixel(ic+a, y, colorp);
			ic++;
		}
    }
	
    sa = dx12 * (y - y1);
    sb = dx02 * (y - y0);
    for(; y<y2; y++) {
        a   = x1 + sa / dy12;
        b   = x0 + sb / dy02;
		if(a > b) swapGL(a,b);
        sa += dx12;
        sb += dx02;
        if(a > b) {
            swapGL(a,b);
        }
        //interpolateFastHLine(a, y, b-a+1, colorA, colorB);
		uint16_t ic = 0;
		while (ic< b-a+1) {
			float w1 = (float)((ic+a)*cdy21+x1*(y-y2)+x2*(y1-y))/barydenom;
			float w2 = -(float)((ic+a)*cdy20+x0*(y-y2)+x2*(y0-y))/barydenom;
			float w3 = 1.0 - w1 - w2;

			rp = r0*w1 + r1*w2 + r2*w3;
			bp = b0*w1 + b1*w2 + b2*w3;
			gp = g0*w1 + g1*w2 + g2*w3;
			uint16_t colorp = color565(rp, gp, bp);
			drawPixel(ic+a, y, colorp);
			ic++;
		}
    }
	//Serial.println("finished");
}

FLASHMEM
void Teensy_OpenGL::shadeTriangleSmooth ( 
          int16_t x0, int16_t y0,
		  int16_t x1, int16_t y1,
		  int16_t x2, int16_t y2,
		  uint16_t idx,
          uint16_t color0, 
          uint16_t color1, 
          uint16_t color2) 
{
    int16_t a, b, y, last;

	uint16_t idx0 = idx;
	uint16_t idx1 = idx+1;
	uint16_t idx2 = idx+2;
	
    if (y0 > y1) { swapGL(y0, y1); swapGL(x0, x1); swapGL(color0,color1); swapGL(idx0, idx1);}
    if (y1 > y2) { swapGL(y2, y1); swapGL(x2, x1); swapGL(color2,color1); swapGL(idx2, idx1);}
    if (y0 > y1) { swapGL(y0, y1); swapGL(x0, x1); swapGL(color0,color1); swapGL(idx0, idx1);}


	if(y0 == y2) { // Handle awkward all-on-same-line case as its own thing
		a = b = x0;
		if(x1 < a)      a = x1;
		else if(x1 > b) b = x1;
		if(x2 < a)      a = x2;
		else if(x2 > b) b = x2;
		drawFastHLine(a, y0, b-a+1, color0);
		return;
	  }
/*
float ambientR = 1;
float ambientG = 1;
float ambientB = 1;
float ambientIntensity = 0.7;

float diffuseR = 1;
float diffuseG = 1;
float diffuseB = 1;
float diffuseIntensity = 0.2;

float diffuseX = 1;   // direction of the diffuse light
float diffuseY = 0;   // (this vector should have length 1)
float diffuseZ = 0;
*/	  
    int16_t
		dx01 = x1 - x0,
		dy01 = y1 - y0,
		dx02 = x2 - x0,
		dy02 = y2 - y0,
		dx12 = x2 - x1,
		dy12 = y2 - y1;
    int32_t
		sa   = 0,
		sb   = 0;
	
  // For upper part of triangle, find scanline crossings for segments
  // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
  // is included here (and second loop will be skipped, avoiding a /0
  // error there), otherwise scanline y1 is skipped here and handled
  // in the second loop...which also avoids a /0 error here if y0=y1
  // (flat-topped triangle).
	
    if(y1 == y2) last = y1;   // Include y1 scanline
    else         last = y1-1; // Skip the y1 scanline

    // Skip the first line to avoid triangle overlap in meshes
    sa += dx01;
    sb += dx02;
	
	//barycenteric deltas
	int16_t
		cdy12 = (y1-y2),
		cdx21 = (x2-x1),
		cdx02 = (x0-x2),
		cdy02 = (y0-y2),
		cdy21 = y2-y1,
		cdy10 = y1-y0,
		cdy20 = y2-y0;
	float barydenom = (float)(x0*cdy21+x1*cdy02+x2*cdy10);
	
	uint8_t r0, r1, r2, g0, g1, g2, b0, b1, b2, rp, gp, bp;
	color565toRGB(color0, r0, g0, b0);
	color565toRGB(color1, r1, g1, b1);
	color565toRGB(color2, r2, g2, b2);
	
	//for calculating specular light
	float L[3],
		  E[3],
		  R[3],
		  N[3];
	//float N[3];
	//		 
	E[0] = -_eyeX; E[1] = -_eyeY; E[2] = -_eyeZ;
	L[0] = diffuseX - _eyeX; L[0] = diffuseY - _eyeY; L[0] = diffuseZ - _eyeZ;
	normVector3(L, L);		// normalize light direction
	normVector3(E, E);	// normalize eye direction
	
	
    for(y=y0+1; y<=last; y++) {
        a   = x0 + sa / dy01;
        b   = x0 + sb / dy02;
        if(a > b) {
            swapGL(a,b);
        }
        sa += dx01;
        sb += dx02;
		
        //interpolateFastHLine(a, y, b-a+1, colorA, colorB);
		uint16_t ic = 0;
		while (ic < b-a+1) {
			//Color interpolation
			float w1 = (float)((ic+a)*cdy21+x1*(y-y2)+x2*(y1-y))/barydenom;
			float w2 = -(float)((ic+a)*cdy20+x0*(y-y2)+x2*(y0-y))/barydenom;
			float w3 = 1.0 - w1 - w2;
			rp = r0*w1 + r1*w2 + r2*w3;
			bp = b0*w1 + b1*w2 + b2*w3;
			gp = g0*w1 + g1*w2 + g2*w3;
			//uint16_t colorp1 = color565(rp, bp, gp);
			//drawPixel(ic+a, y, colorp1);	
			
			if(_use_lighting){
				//Normal interpolation
				N[0] = glVertices[idx0].nx*w1 + glVertices[idx1].nx*w2 + glVertices[idx2].nx*w3;
				N[1] = glVertices[idx0].ny*w1 + glVertices[idx1].ny*w2 + glVertices[idx2].ny*w3;
				N[2] = glVertices[idx0].nz*w1 + glVertices[idx1].nz*w2 + glVertices[idx2].nz*w3;
				
				//Serial.printf("%f, %f, %f\n", nx, ny, nz);
				float factor = min(max(0, -1*(N[0]*diffuseX + N[1]*diffuseY + N[2]*diffuseZ)), 1);
				
				//lets try adding specular ligthing
				//2*dot product of N, I  (reflect I, N)
				float dot = N[0]*L[0] + N[1]*L[1] +N[2]*L[2];
				for(uint8_t i = 0; i < 3; i++)
					R[i] = L[i] - 2.0f*dot*N[i];
				R[0] = -R[0]; R[1] = -R[1]; R[2] = -R[2];
				normVector3(R, R);		// normalized reflected light direction
				
				float factor_spec = pow(max(R[0]*E[0]+R[1]*E[1]+R[2]*E[2], 0.0), 0.3*glShiniess);
				
				rp *= (ambientR*ambientIntensity + factor*diffuseR*diffuseIntensity + factor_spec*specularR*specularIntensity);
				gp *= (ambientG*ambientIntensity + factor*diffuseG*diffuseIntensity + factor_spec*specularG*specularIntensity);
				bp *= (ambientB*ambientIntensity + factor*diffuseB*diffuseIntensity + factor_spec*specularB*specularIntensity);
			}
			
			rp = max(min(rp, 255), 0);   // clamp the colors
			gp = max(min(gp, 255), 0);   // so they don't
			bp = max(min(bp, 255), 0);   // become too bright

			
			uint16_t colorp = color565(rp, gp, bp);
			drawPixel(ic+a, y, colorp);
			ic++;
		}
    }
	
    sa = dx12 * (y - y1);
    sb = dx02 * (y - y0);
    for(; y<y2; y++) {
        a   = x1 + sa / dy12;
        b   = x0 + sb / dy02;
        if(a > b) {
            swapGL(a,b);
        }
        sa += dx12;
        sb += dx02;
		
		uint16_t ic = 0;
		while (ic< b-a+1) {
			float w1 = (float)((ic+a)*cdy21+x1*(y-y2)+x2*(y1-y))/barydenom;
			float w2 = -(float)((ic+a)*cdy20+x0*(y-y2)+x2*(y0-y))/barydenom;
			float w3 = 1.0 - w1 - w2;

			rp = r0*w1 + r1*w2 + r2*w3;
			bp = b0*w1 + b1*w2 + b2*w3;
			gp = g0*w1 + g1*w2 + g2*w3;
			
			//Normal interpolation
			N[0] = glVertices[idx0].nx*w1 + glVertices[idx1].nx*w2 + glVertices[idx2].nx*w3;
			N[1] = glVertices[idx0].ny*w1 + glVertices[idx1].ny*w2 + glVertices[idx2].ny*w3;
			N[2] = glVertices[idx0].nz*w1 + glVertices[idx1].nz*w2 + glVertices[idx2].nz*w3;
			
			if(_use_lighting){
				float factor = min(max(0, -1*(N[0]*diffuseX + N[1]*diffuseY + N[2]*diffuseZ)), 1);
				
				//lets try adding specular ligthing
				//2*dot product of N, I  (reflect I, N)
				float dot = N[0]*L[0] + N[1]*L[1] +N[2]*L[2];
				for(uint8_t i = 0; i < 3; i++)
					R[i] = L[i] - 2.0f*dot*N[i];
				R[0] = -R[0]; R[1] = -R[1]; R[2] = -R[2];
				normVector3(R, R);		// normalized reflected light direction
				
				float factor_spec = pow(max(R[0]*E[0]+R[1]*E[1]+R[2]*E[2], 0.0), 0.3*glShiniess);
				
				rp *= (ambientR*ambientIntensity + factor*diffuseR*diffuseIntensity + factor_spec*specularR*specularIntensity);
				gp *= (ambientG*ambientIntensity + factor*diffuseG*diffuseIntensity + factor_spec*specularG*specularIntensity);
				bp *= (ambientB*ambientIntensity + factor*diffuseB*diffuseIntensity + factor_spec*specularB*specularIntensity);
			}
			
            rp = max(min(rp, 255), 0);   // clamp the colors
            gp = max(min(gp, 255), 0);   // so they don't
            bp = max(min(bp, 255), 0);   // become too bright
			
			uint16_t colorp = color565(rp, gp, bp);
			drawPixel(ic+a, y, colorp);
			ic++;
		}
    }
}

////////////////////////////////////////////////////////////////////////
// Either face_colors or vertex_colors may be NULL, to use the model-
// specified colors, or the current foreground color if those are not
// available.
// Draw order may be NUL, but if it is provided triangles are sorted
// from front to back and overdraw avoidance is used. 
////////////////////////////////////////////////////////////////////////
/*  To do correct flat shading to do depths.
void Arduino_3D::fillFaces(Model *M, int16_t *vertices, uint16_t *face_colors, uint16_t *draw_order) {
    updateDrawingOrder(M,vertices,draw_order);
    uint16_t color = foreground_color;
    uint16_t nt    = M->NFaces;
    for (int j=0; j<nt; j++) {
        int i = draw_order? draw_order[j] : j;
        int16_t *p,*q,*r;
        get_triangle_points(M,vertices,i,&p,&q,&r);
        if (facing_camera(p,q,r)) {
            if (face_colors  !=NULL) color = color_map[face_colors[i]]*0x0101;
            uint16_t  x1 = p[0]+X0;
            uint16_t  x2 = q[0]+X0;
            uint16_t  x3 = r[0]+X0;
            fillTriangle(x1,p[1]+Y0,x2,q[1]+Y0,x3,r[1]+Y0,color);
        }
    }
}
*/

void Teensy_OpenGL::shadeFaces(GLVertex *vertices, uint16_t *vertex_colors, uint16_t *draw_order) {
    uint16_t nt    = NFACES;
    updateDrawingOrder(nt, vertices, draw_order);
	float p[3], q[3], r[3];
	uint8_t idx;
    for (int j=0; j<nt; j++) {
		idx = j*3;
        int i = draw_order? draw_order[j]:j;
		//aux is the transformed vertices that were read in 
		//previously using get_triangle
		// if triangle is facing the camera, draw it
		p[0] = vertices[j].x; p[1] = vertices[j].y; p[2] = vertices[j].z;
		q[0] = vertices[j+1].x; q[1] = vertices[j+1].y; q[2] = vertices[j+1].z;
		r[0] = vertices[j+2].x; r[1] = vertices[j+2].y; r[2] = vertices[j+2].z;
		
        if (facing_camera(p,q,r)) {
            //uint16_t color1 = vertex_colors[pi];
            //uint16_t color2 = vertex_colors[qi];
            //uint16_t color3 = vertex_colors[ri];
            uint16_t  x1 = p[0];
            uint16_t  x2 = q[0];
            uint16_t  x3 = r[0];
            //shadeTriangle(x1,p[1],x2,q[1],x3,r[1],color1,color2,color3);
        }
    }
}


////////////////////////////////////////////////////////////////////////
// Non-convex 3D surfaces can overlap themselvs. Sorting triangles from
// front to back and checking to make sure we don't draw on top of areas
// that have already been drawn can avoid Arduino_3D::overlap artefacts. To 
// maintain sorted lists of polygons across frames, theses functions
// accept a permutation list for the triangle drawing order. The 
// permutation is updated to reflect the current z-order. 
////////////////////////////////////////////////////////////////////////

// Helper routine for sorting triangles
// Faces may remain partially ordered after rotating the object
// To take advantage of this, we store and use a fixed permutation 
// array "draw_order"

void Teensy_OpenGL::computeTriangleDepths(uint16_t nt, GLVertex *vertices, uint16_t *draw_order, float *depths) {
    //uint16_t nt = NFACES;
    float p,q,r,s;
	uint16_t idx;

	if(glDrawMode == GL_QUADS || glDrawMode == GL_QUAD_STRIP){
		for (int j=0; j < nt; j++) {
			int i = draw_order!=NULL? draw_order[j]:j;
			if(glDrawMode == GL_QUADS) idx = j*4;
			if(glDrawMode == GL_QUAD_STRIP) idx = j*2;
			p = vertices[idx].z;
			q = vertices[idx+1].z;
			r = vertices[idx+2].z;
			s = vertices[idx+3].z;
			
			// get the rotated vertex Z coordinates for the triangle
			float z = (p+q+r+s)/4;
			depths[j] = z;
		}
	} else if(glDrawMode == GL_TRIANGLES || glDrawMode == GL_TRIANGLE_STRIP){
		for (int j=0; j < nt; j++) {
			int i = draw_order!=NULL? draw_order[j]:j;
			if(glDrawMode == GL_TRIANGLES) idx = j*3;
			if(glDrawMode == GL_TRIANGLE_STRIP) idx = j;
			p = vertices[idx].z;
			q = vertices[idx+1].z;
			r = vertices[idx+2].z;
			
			// get the rotated vertex Z coordinates for the triangle
			float z = (p+q+r)/3;
			depths[j] = z;
		}
	}
}

// Sorts triangles from front to back to properly handle occlusions
// Bubble sort is in fact the efficient solution here. 
// It is O(N) for sorted data, and requires no additional memory to sort. 
// Triangles remain mostly sorted as object rotates.
void Teensy_OpenGL::updateDrawingOrder(uint16_t nt, GLVertex *vertices, uint16_t *draw_order) {
    if (draw_order==NULL) return;
    //uint16_t nt = NFACES;
    float depths[nt];
    computeTriangleDepths(nt, vertices, draw_order, depths);
    // Bubble sort the triangles by depth keeping track of the permutation
    uint8_t sorted = 0;
    while (!sorted) {
        sorted = 1;
        for (int i=1;i<nt;i++) {
            float d1 = depths[i-1];
            float d2 = depths[i];
            if (d2>d1) {
                depths[i-1] = d2;
                depths[i]   = d1;
                uint16_t temp    = draw_order[i];
                draw_order[i]   = draw_order[i-1];
                draw_order[i-1] = temp;
                sorted = 0;
            }
        }
    }
}

FLASHMEM
void Teensy_OpenGL::findSharedVerts(uint16_t nvert, uint16_t nface, uint16_t nvertP)
{
  //uint16_t common[1024*3][50];
    uint16_t iCounter = 0;

	if(nvertP == 4) {
		#define _useQuad 1;
	}
  
  for(uint16_t trig = 0; trig < nvert; trig++){ //vertex count
    uint16_t i = trig/nvertP;
    iCounter = iCounter + 1;
    for(uint16_t trig1 = 0; trig1 < nface; trig1++){ //NFaces
        uint16_t j = trig1*nvertP;
        uint8_t test0 = 0, test1 = 0, test2 = 0, test3 = 0;
        test0 = dVector3(trig, j);
        test1 = dVector3(trig, j+1);
        test2 = dVector3(trig, j+2);
        if(nvertP == 4)
            test3 = dVector3(trig, j+3);
		#if defined(_useQuad)
		if(trig != j && trig != j+1 && trig != j+2 && trig != j+3){
		#else
        if(trig != j && trig != j+1 && trig != j+2){
		#endif
          if((test0) == 3) {
            common[trig][iCounter] = j;				//vert for adjenct triangle
            iCounter = iCounter + 1;
          }
          if((test1) == 3) {
            common[trig][iCounter] = j+1;
            iCounter = iCounter + 1;
          }
          if((test2) == 3) {
            common[trig][iCounter] = j+2;
            iCounter = iCounter + 1;
          }
          if(nvertP == 4) {
            if((test3) == 3) {
              common[trig][iCounter] = j+3;
              iCounter = iCounter + 1;
            }
          }
        }
     }
      common[trig][0] = iCounter;		//number of elements in row
      iCounter = 0;
  }
/*
   for(uint16_t i = 0; i< nvert; i++){
    for(uint16_t j = 0; j < common[i][0]; j++){
      Serial.printf("%d, ", common[i][j]);
    } Serial.println();
   }
*/
}


//========================================
uint16_t * Teensy_OpenGL::dups(uint16_t arr[], int n){
    int v, icount;
    icount = 1;
    static uint16_t sortedArr[50];
    
    //cout << "\nDuplicate Elements :";
    for (int i = 1; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] == arr[j]) {
                if (v == 1 ) {
                    sortedArr[icount] = arr[i];
                    icount = icount + 1;
                }
                v++;
            }
        }
        v = 1;
    }
    sortedArr[0] = icount;
    return sortedArr;
}

void Teensy_OpenGL::findAdjacentFaces(uint16_t nvert, uint16_t nface, uint16_t nvertP)
{
  uint16_t common[1024*3][50];
    uint16_t iCounter = 0;
  
  for(uint16_t trig = 0; trig < nvert; trig++){ //vertex count
    uint16_t i = trig/nvertP;
    iCounter = iCounter + 3;
    for(uint16_t trig1 = 0; trig1 < nface; trig1++){ //NFaces
        uint16_t j = trig1*nvertP;
        uint8_t test0 = 0, test1 = 0, test2 = 0, test3 = 0;
        test0 = dVector3(trig, j);
        test1 = dVector3(trig, j+1);
        test2 = dVector3(trig, j+2);
        if(nvertP == 4)
            test3 = dVector3(trig, j+3);
        if(trig != j && trig != j+1 && trig != j+2){
          if((test0) == 3) {
            common[trig][iCounter] = j;				//vert for adjenct triangle
            common[trig][iCounter + 1] = trig1;		//face for adject triangle
            iCounter = iCounter + 2;
          }
          if((test1) == 3) {
            common[trig][iCounter] = j+1;
            common[trig][iCounter + 1] = trig1;
            iCounter = iCounter + 2;
          }
          if((test2) == 3) {
            common[trig][iCounter] = j+2;
            common[trig][iCounter + 1] = trig1;
            iCounter = iCounter + 2;
          }
          if(nvertP == 4) {
            if((test3) == 3) {
              common[trig][iCounter] = j+3;
              common[trig][iCounter + 1] = trig1;
              iCounter = iCounter + 2;
            }
          }
        }
     }
      common[trig][2] = i;				//face
      common[trig][1] = trig;			//vert for face
      common[trig][0] = iCounter;		//number of elements in row
      iCounter = 0;
  }
   
   for(uint16_t i = 0; i< nvert; i++){
    //Serial.printf("(%d) %d, %d, %d:\n\t", i, common[i][0], common[i][1], common[i][2]);
    for(uint16_t j = 0; j < common[i][0]; j++){
      Serial.printf("%d, ", common[i][j]);
    } Serial.println();
   }
   
   
   uint16_t iCount = 0;
   uint16_t rowCount = 0, colCount = 1;
   uint16_t tempFaces[nface][50];
   for(uint16_t i = 0; i< nvert; i++){
      //[vert][vert/face]
      //[i][0] = # of elements in row
      //[i][1] = vert for face [i][2]
      //[i][3] = vert for adjenct triangle
      //[i][4] = face for adject triangle
      //3,4 repeated [0]-3 times
      //face every other one after that
      if(iCount % nvertP == 0) {
        colCount = 1;
      }
      uint16_t rowElements = common[i][0];
      for(uint8_t k = 0; k < ((rowElements-3)/2); k++){
          tempFaces[rowCount][colCount] = common[i][3+k*2+1];
          colCount = colCount + 1; 
      }
      iCount = iCount + 1;
      if(iCount % nvertP == 0){
        tempFaces[common[i][2]][0] = colCount;
        iCount = 0;
        rowCount = rowCount + 1;
      }
   }

   uint16_t * p;
   for(uint8_t i = 0; i < nface; i++){
      p = dups(tempFaces[i], tempFaces[i][0]);
      for(uint8_t j = 0; j < *(p); j++){
        adjFaces[i][j] = *(p+j);
      }
   }
   
   for(uint8_t i = 0; i < nface; i++){
      for(uint8_t j = 0; j < adjFaces[i][0]; j++){
        Serial.printf("%d, ", adjFaces[i][j]);
      }
      Serial.println();
   }

}

//Lighting
void  Teensy_OpenGL::glLight(GLLight lightNo, GLLight var, float *array)
{
	if(var == GL_AMBIENT) {
		ambientR = array[0];
		ambientG = array[1];
		ambientB = array[2];
		ambientIntensity = array[3];
	} else if(var == GL_DIFFUSE) {
		diffuseR = array[0];
		diffuseG = array[1];
		diffuseB = array[2];
		diffuseIntensity = array[3];
	} else if(var == GL_SPECULAR) {
		specularR = array[0];
		specularG = array[1];
		specularB = array[2];
		specularIntensity = array[3];
	} else if(var == GL_POSITION) {
		diffuseX = array[0];   // direction of the diffuse light
		diffuseY = array[1];   // (this vector should have length 1)
		diffuseZ = array[2];
		float tempNorm = sqrt(diffuseX*diffuseX + diffuseY*diffuseY + diffuseZ*diffuseZ);
		diffuseX /= tempNorm;
		diffuseY /= tempNorm;
		diffuseZ /= tempNorm;
	}
	
	 _use_lighting = true;
}

float * Teensy_OpenGL::reflect(float * I, float * N)
{
	float temp[3];
	
	//2*dot product of N, I
	float dot = N[0]*I[0] + N[1]*I[1] +N[2]*I[2];

	for(uint8_t i = 0; i < 3; i++)
		temp[i] = I[i] - 2.0f*dot*N[i];

	return temp;
}
	
	