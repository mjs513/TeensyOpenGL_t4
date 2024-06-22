
uint8_t teapot;
void drawFromModel(){
  init_model();
  Model *M = &model_data;
 
  uint16_t nt    = M->NFaces;
  tft.glBegin(GL_TRIANGLES);
       if(_use_FacetShader || _use_SmoothShader) {
          tft.glColor3ub(255,255,255);
       } else {
         tft.glColor3ub(102, 178, 255);
         for(int c = 0; c < M->NVertices; c++){
           tft.glColorT(c, 255, 255, 0);
         }
       }
      // Get the vertex indicies for the triangle
      for (uint16_t i=0; i< nt; i++) {
           int16_t *p,*q,*r;
           tft.get_triangle_points(M, (int16_t *)vertices, i, &p, &q, &r);
           tft.glVertex3f((float) p[0], (float) p[1], (float) p[2]);
           tft.glVertex3f((float) q[0], (float) q[1], (float) q[2]);
           tft.glVertex3f((float) r[0], (float) r[1], (float) r[2]);
      }
    tft.glEnd();
}
