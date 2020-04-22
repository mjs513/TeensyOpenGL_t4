
void Torus2d( float x0, float y0, float inner, float outer, unsigned int pts )
{
//modified from:
//https://stackoverflow.com/questions/19730976/opengl-and-c-drawing-shape-using-circle-algorthim
//http://slabode.exofire.net/circle_draw.shtml

  tft.glBegin( GL_TRIANGLE_STRIP );
    for( unsigned int i = 0; i <= pts-1; ++i )
    {
        float angle = ( i / (float)pts ) * 3.14159f * 2.0f;
        float angle1 =( (i+1) / (float)pts ) * 3.14159f * 2.0f;
        tft.glVertex3f( inner * cos( angle ) + x0, inner * sin( angle ) + y0, 0 );
        tft.glVertex3f( outer * cos( angle ) + x0, outer * sin( angle ) + y0, 0 );
        tft.glVertex3f( inner * cos( angle1) + x0, inner * sin( angle1 ) + y0, 0 );
        tft.glVertex3f( outer * cos( angle1) + x0, outer * sin( angle1 ) + y0, 0 );
    }
    tft.glEnd();
}

void drawLines() {
  /* 3 triangles instead of 4 */
  tft.glBegin(GL_LINES);
    tft.glColor3ub(255,255,0);
    tft.glVertex3f(0, 1, 0);
    tft.glVertex3f(0, 0, 0);
  tft.glEnd();
}

void drawLineLoop() {
  /* 3 triangles instead of 4 */
  tft.glBegin(GL_LINE_LOOP);
    tft.glColorT(0, 255, 0, 0);
    tft.glColorT(1, 0, 255, 0);
    tft.glColorT(2, 0, 0, 255);
    tft.glVertex3f(0, 1, 0);
    tft.glVertex3f(-1, -1, 0);
    tft.glVertex3f(1, 1, 0);
  tft.glEnd();
}

void drawLineStrip() {
  /* 3 triangles instead of 4 */
  tft.glBegin(GL_LINE_STRIP);
    tft.glColorT(0, 255, 0, 0);
    tft.glColorT(1, 0, 255, 0);
    tft.glColorT(2, 0, 0, 255);
    tft.glVertex3f(0, 1, 0);
    tft.glVertex3f(0, 0, 0);
    tft.glVertex3f(1, 0, 0);
  tft.glEnd();
}

void drawPyramid() {
  /* 3 triangles instead of 4 */
  tft.glBegin(GL_TRIANGLE_STRIP);
    tft.glColor3ub(218,165,32);
    tft.glColorT(0, 255, 0, 0);
    tft.glColorT(1, 0, 255, 0);
    tft.glColorT(2, 0, 0, 255);
    tft.glColorT(3, 255, 0, 255);
    tft.glVertex3f(-1, 0, 0);
    tft.glVertex3f(-1, 1, 0);
    tft.glVertex3f(0, 0, 0);
    tft.glVertex3f(0, 1, 0);
  tft.glEnd();
}

void drawPoly(){
  tft.glBegin(GL_POLYGON);
    tft.glColor3ub(255,0,0);
    tft.glVertex3f(0.f, 0.f, 0.f);
    tft.glVertex3f(0.f, 1.f, 0.f);
    tft.glVertex3f(1.f, 1.f, 0.f);
    tft.glVertex3f(1.f, 0.f, 0.f);
  tft.glEnd();
}

//Important when drawing quads
   //Coordinate ordinate order.
      // 0---2---4
      // |   |   |
      // 1---3---5
void drawQuad1(){
  tft.glBegin(GL_QUADS);
    for(uint8_t c = 0; c < 4; c++){
      tft.glColorT(c, 255,255,255);
    }
    tft.glVertex3f(0.f, 1.f, 0.f);
    tft.glVertex3f(0.f, 0.f, 0.f);
    tft.glVertex3f(1.f, 1.f, 0.f);
    tft.glVertex3f(1.f, 0.f, 0.f);
  tft.glEnd();
}

void drawQuad2(){
  tft.glBegin(GL_QUADS);
    tft.glColor3ub(255,255,0);
    tft.glVertex3f(0.f, 1.f, 0.f);
    tft.glVertex3f(0.f, 0.f, 0.f);
    tft.glVertex3f(1.f, 1.f, 0.f);
    tft.glVertex3f(1.f, 0.f, 0.f);
  tft.glEnd();
}

void drawQuad3(){
  tft.glBegin(GL_QUADS);
    tft.glVertex3f(0.f, 1.f, 0.f);
    tft.glVertex3f(0.f, 0.f, 0.f);
    tft.glVertex3f(1.f, 1.f, 0.f);
    tft.glVertex3f(1.f, 0.f, 0.f);
  tft.glEnd();
}
