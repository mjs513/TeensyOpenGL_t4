
void drawCube()
{
  tft.glBegin(GL_QUADS);        // Draw The Cube Using quads
      if(_use_FacetShader || _use_SmoothShader){
          tft.glColor3ub(218,165,32);
      } else {
        for(int c = 0; c < 4; c++){
          tft.glColorT(c, 255, 0, 0);
        }
        for(int c = 4; c < 8; c++){
          tft.glColorT(c, 0, 255, 0);
        }
        for(int c = 8; c < 12; c++){
          tft.glColorT(c, 0, 0, 255);
        }
        for(int c = 12; c < 16; c++){
          tft.glColorT(c, 255, 255, 0);
        }
        for(int c = 16; c < 20; c++){
          tft.glColorT(c, 0, 255, 255);
        }
        for(int c = 20; c < 24; c++){
          tft.glColorT(c, 255, 0, 255);
        }
      }
   
    tft.glVertex3f(-1.0f, 1.0f,-1.0f);    // Top Left Of The Quad (Top)
    tft.glVertex3f(-1.0f, 1.0f, 1.0f);    // Bottom Left Of The Quad (Top)
    tft.glVertex3f( 1.0f, 1.0f,-1.0f);    // Top Right Of The Quad (Top)
    tft.glVertex3f( 1.0f, 1.0f, 1.0f);    // Bottom Right Of The Quad (Top)
    
    tft.glVertex3f(-1.0f,-1.0f, 1.0f);    // Top Left Of The Quad (Bottom)
    tft.glVertex3f(-1.0f,-1.0f,-1.0f);    // Bottom Left Of The Quad (Bottom)    
    tft.glVertex3f( 1.0f,-1.0f, 1.0f);    // Top Right Of The Quad (Bottom)
    tft.glVertex3f( 1.0f,-1.0f,-1.0f);    // Bottom Right Of The Quad (Bottom)
    
    tft.glVertex3f(-1.0f, 1.0f, 1.0f);    // Top Left Of The Quad (Front)
    tft.glVertex3f(-1.0f,-1.0f, 1.0f);    // Bottom Left Of The Quad (Front)
    tft.glVertex3f( 1.0f, 1.0f, 1.0f);    // Top Right Of The Quad (Front)
    tft.glVertex3f( 1.0f,-1.0f, 1.0f);    // Bottom Right Of The Quad (Front)

    tft.glVertex3f(-1.0f,-1.0f,-1.0f);    // Top Left Of The Quad (Back)
    tft.glVertex3f(-1.0f, 1.0f,-1.0f);    // Bottom Left Of The Quad (Back)    
    tft.glVertex3f( 1.0f,-1.0f,-1.0f);    // Top Right Of The Quad (Back)
    tft.glVertex3f( 1.0f, 1.0f,-1.0f);    // Bottom Right Of The Quad (Back)
   
    tft.glVertex3f(-1.0f, 1.0f,-1.0f);    // Top Left Of The Quad (Left)
    tft.glVertex3f(-1.0f,-1.0f,-1.0f);    // Bottom Left Of The Quad (Left)
    tft.glVertex3f(-1.0f, 1.0f, 1.0f);    // Top Right Of The Quad (Left)
    tft.glVertex3f(-1.0f,-1.0f, 1.0f);    // Bottom Right Of The Quad (Left)
   

    tft.glVertex3f( 1.0f, 1.0f, 1.0f);    // Top Left Of The Quad (Right)
    tft.glVertex3f( 1.0f,-1.0f, 1.0f);    // Bottom Left Of The Quad (Right)
    tft.glVertex3f( 1.0f, 1.0f,-1.0f);    // Top Right Of The Quad (Right)
    tft.glVertex3f( 1.0f,-1.0f,-1.0f);    // Bottom Right Of The Quad (Right)
  tft.glEnd();            // End Drawing The Cube
}



void drawCube1()
{
  tft.glBegin(GL_TRIANGLES);
      if(_use_FacetShader || _use_SmoothShader){
          tft.glColor3ub(218,165,32);
      } else {
        for(int c = 0; c < 6; c++){
          tft.glColorT(c, 255, 0, 0);
        }
        for(int c = 6; c < 12; c++){
          tft.glColorT(c, 0, 255, 0);
        }
        for(int c = 12; c < 18; c++){
          tft.glColorT(c, 0, 0, 255);
        }
        
        for(int c = 18; c < 24; c++){
          tft.glColorT(c, 255, 255, 0);
        }
        for(int c = 24; c < 30; c++){
          tft.glColorT(c, 0, 255, 255);
        }
        for(int c = 30; c < 36; c++){
          tft.glColorT(c, 255, 0, 255);
        }
      }
  // Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
  // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    tft.glVertex3f(-1.0f,-1.0f,-1.0f);
    tft.glVertex3f(-1.0f,-1.0f, 1.0f);
    tft.glVertex3f(-1.0f, 1.0f, 1.0f);
    tft.glVertex3f( 1.0f, 1.0f,-1.0f);
    tft.glVertex3f(-1.0f,-1.0f,-1.0f);
    tft.glVertex3f(-1.0f, 1.0f,-1.0f);
    tft.glVertex3f( 1.0f,-1.0f, 1.0f);
    tft.glVertex3f(-1.0f,-1.0f,-1.0f);
    tft.glVertex3f( 1.0f,-1.0f,-1.0f);
    tft.glVertex3f( 1.0f, 1.0f,-1.0f);
    tft.glVertex3f( 1.0f,-1.0f,-1.0f);
    tft.glVertex3f(-1.0f,-1.0f,-1.0f);
    tft.glVertex3f(-1.0f,-1.0f,-1.0f);
    tft.glVertex3f(-1.0f, 1.0f, 1.0f);
    tft.glVertex3f(-1.0f, 1.0f,-1.0f);
    tft.glVertex3f( 1.0f,-1.0f, 1.0f);
    tft.glVertex3f(-1.0f,-1.0f, 1.0f);
    tft.glVertex3f(-1.0f,-1.0f,-1.0f);
    tft.glVertex3f(-1.0f, 1.0f, 1.0f);
    tft.glVertex3f(-1.0f,-1.0f, 1.0f);
    tft.glVertex3f( 1.0f,-1.0f, 1.0f);
    tft.glVertex3f( 1.0f, 1.0f, 1.0f);
    tft.glVertex3f( 1.0f,-1.0f,-1.0f);
    tft.glVertex3f( 1.0f, 1.0f,-1.0f);
    tft.glVertex3f( 1.0f,-1.0f,-1.0f);
    tft.glVertex3f( 1.0f, 1.0f, 1.0f);
    tft.glVertex3f( 1.0f,-1.0f, 1.0f);
    tft.glVertex3f( 1.0f, 1.0f, 1.0f);
    tft.glVertex3f( 1.0f, 1.0f,-1.0f);
    tft.glVertex3f(-1.0f, 1.0f,-1.0f);
    tft.glVertex3f( 1.0f, 1.0f, 1.0f);
    tft.glVertex3f(-1.0f, 1.0f,-1.0f);
    tft.glVertex3f(-1.0f, 1.0f, 1.0f);
    tft.glVertex3f( 1.0f, 1.0f, 1.0f);
    tft.glVertex3f(-1.0f, 1.0f, 1.0f);
    tft.glVertex3f( 1.0f,-1.0f, 1.0f);
  tft.glEnd();
}
    
