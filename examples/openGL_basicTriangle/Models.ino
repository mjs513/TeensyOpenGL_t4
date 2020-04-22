void drawTri() {
  tft.glBegin(GL_TRIANGLES);
    tft.glColorT(0, 255, 0, 0);
    //tft.glColorT(1, 72, 125, 180);
    //tft.glColorT(2, 72, 125, 180);
    tft.glColorT(1, 0, 255, 0);
    tft.glColorT(2, 0, 0, 255);
    tft.glVertex3f(  0.0f, 1.0f, 0.0f);
    tft.glVertex3f(-1.0f, -1.0f, 1.0f);
    tft.glVertex3f(1.0f, -1.0f, 1.0f);
  tft.glEnd();
}

void drawTri0() {
  tft.glBegin(GL_TRIANGLES);
    tft.glVertex3f(  0.0f, 1.0f, 0.0f);
    tft.glVertex3f(-1.0f, -1.0f, 1.0f);
    tft.glVertex3f(1.0f, -1.0f, 1.0f);
  tft.glEnd();
}

void drawTri1() {
  tft.glBegin(GL_TRIANGLES);
    tft.glColorT(0, 255, 255, 255);
    tft.glColorT(1, 255, 255, 255);
    tft.glColorT(2, 255, 255, 255);
    tft.glVertex3f(  0.0f, 1.0f, 0.0f);
    tft.glVertex3f(-1.0f, -1.0f, 1.0f);
    tft.glVertex3f(1.0f, -1.0f, 1.0f);
  tft.glEnd();
}

void drawTri2() {
  tft.glBegin(GL_TRIANGLES);
    tft.glColor3ub(102, 178, 255);

    tft.glVertex3f(  0.0f, 1.0f, 0.0f);
    tft.glVertex3f(-1.0f, -1.0f, 1.0f);
    tft.glVertex3f(1.0f, -1.0f, 1.0f);
  tft.glEnd();
}

void drawPyramid(){
   tft.glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
      //tft.glColor3ub(102, 178, 255);
      if(_use_FacetShader || _use_SmoothShader){
        tft.glColor3ub(102, 178, 255);
      } else {
        for(int c = 0; c < 4; c++){
          tft.glColorT(c, 255, 0, 0);
        }
      }
      // Front
      tft.glVertex3f(  0.0f, 1.0f, 0.0f);
      tft.glVertex3f(-1.0f, -1.0f, 1.0f);
      tft.glVertex3f(1.0f, -1.0f, 1.0f);
 
      // Right
      tft.glVertex3f(0.0f, 1.0f, 0.0f);
      tft.glVertex3f(1.0f, -1.0f, 1.0f);
      tft.glVertex3f(1.0f, -1.0f, -1.0f);
 
      // Back
      tft.glVertex3f(0.0f, 1.0f, 0.0f);
      tft.glVertex3f(1.0f, -1.0f, -1.0f);
      tft.glVertex3f(-1.0f, -1.0f, -1.0f);
 
      // Left
      tft.glVertex3f( 0.0f, 1.0f, 0.0f);
      tft.glVertex3f(-1.0f,-1.0f,-1.0f);
      tft.glVertex3f(-1.0f,-1.0f, 1.0f);
   tft.glEnd();   // Done drawing the pyramid
}

void drawDiamond(){
   tft.glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
      //tft.glColor3ub(102, 178, 255);
      if(_use_FacetShader || _use_SmoothShader){
        tft.glColor3ub(102, 178, 255);
      } else {
        for(int c = 0; c < 24; c++){
          tft.glColorT(c, 255, 0, 0);
        }
      }
      // Front
      tft.glVertex3f(  0.0f, 1.0f, 0.0f);
      tft.glVertex3f(-1.0f, -1.0f, 1.0f);
      tft.glVertex3f(1.0f, -1.0f, 1.0f);
 
      // Right
      tft.glVertex3f(0.0f, 1.0f, 0.0f);
      tft.glVertex3f(1.0f, -1.0f, 1.0f);
      tft.glVertex3f(1.0f, -1.0f, -1.0f);
 
      // Back
      tft.glVertex3f(0.0f, 1.0f, 0.0f);
      tft.glVertex3f(1.0f, -1.0f, -1.0f);
      tft.glVertex3f(-1.0f, -1.0f, -1.0f);
 
      // Left
      tft.glVertex3f( 0.0f, 1.0f, 0.0f);
      tft.glVertex3f(-1.0f,-1.0f,-1.0f);
      tft.glVertex3f(-1.0f,-1.0f, 1.0f);

      // Front lower
      tft.glVertex3f(  0.0f, -3.0f, 0.0f);
      tft.glVertex3f(1.0f, -1.0f, 1.0f);      
      tft.glVertex3f(-1.0f, -1.0f, 1.0f);
 
      // Right
      tft.glVertex3f(0.0f, -3.0f, 0.0f);
      tft.glVertex3f(1.0f, -1.0f, -1.0f);      
      tft.glVertex3f(1.0f, -1.0f, 1.0f);
 
      // Back
      tft.glVertex3f(0.0f, -3.0f, 0.0f);
      tft.glVertex3f(-1.0f, -1.0f, -1.0f);
      tft.glVertex3f(1.0f, -1.0f, -1.0f);

 
      // Left
      tft.glVertex3f( 0.0f, -3.0f, 0.0f);
      tft.glVertex3f(-1.0f,-1.0f, 1.0f);
      tft.glVertex3f(-1.0f,-1.0f,-1.0f);

   tft.glEnd();   // Done drawing the pyramid
}

void drawDiamondShaded(){
   tft.glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
      //tft.glColor3ub(102, 178, 255);
      if(_use_FacetShader || _use_SmoothShader){
        tft.glColor3ub(255, 255, 255);
      } else {
        for(int c = 0; c < 24; c++){
          tft.glColorT(c, 255, 255, 255);
        }
      }
      // Front
      tft.glVertex3f(  0.0f, 1.0f, 0.0f);
      tft.glVertex3f(-1.0f, -1.0f, 1.0f);
      tft.glVertex3f(1.0f, -1.0f, 1.0f);
 
      // Right
      tft.glVertex3f(0.0f, 1.0f, 0.0f);
      tft.glVertex3f(1.0f, -1.0f, 1.0f);
      tft.glVertex3f(1.0f, -1.0f, -1.0f);
 
      // Back
      tft.glVertex3f(0.0f, 1.0f, 0.0f);
      tft.glVertex3f(1.0f, -1.0f, -1.0f);
      tft.glVertex3f(-1.0f, -1.0f, -1.0f);
 
      // Left
      tft.glVertex3f( 0.0f, 1.0f, 0.0f);
      tft.glVertex3f(-1.0f,-1.0f,-1.0f);
      tft.glVertex3f(-1.0f,-1.0f, 1.0f);

      // Front lower
      tft.glVertex3f(  0.0f, -3.0f, 0.0f);
      tft.glVertex3f(1.0f, -1.0f, 1.0f);      
      tft.glVertex3f(-1.0f, -1.0f, 1.0f);
 
      // Right
      tft.glVertex3f(0.0f, -3.0f, 0.0f);
      tft.glVertex3f(1.0f, -1.0f, -1.0f);      
      tft.glVertex3f(1.0f, -1.0f, 1.0f);
 
      // Back
      tft.glVertex3f(0.0f, -3.0f, 0.0f);
      tft.glVertex3f(-1.0f, -1.0f, -1.0f);
      tft.glVertex3f(1.0f, -1.0f, -1.0f);

 
      // Left
      tft.glVertex3f( 0.0f, -3.0f, 0.0f);
      tft.glVertex3f(-1.0f,-1.0f, 1.0f);
      tft.glVertex3f(-1.0f,-1.0f,-1.0f);

   tft.glEnd();   // Done drawing the pyramid
}
