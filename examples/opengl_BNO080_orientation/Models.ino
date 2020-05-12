
uint8_t teapot;
void drawFromModel(){
  init_model();
  Model *M = &model_data;
 
  uint16_t nt    = M->NFaces;
  tft.glBegin(GL_TRIANGLES);
      tft.glColor3ub(255,255,255);

      // Get the vertex indicies for the triangle
      for (uint16_t i=0; i< nt; i++) {
           int16_t *p,*q,*r;
           tft.get_triangle_points(M, vertices, i, &p, &q, &r);
           tft.glVertex3f((float) p[0], (float) p[1], (float) p[2]);
           tft.glVertex3f((float) q[0], (float) q[1], (float) q[2]);
           tft.glVertex3f((float) r[0], (float) r[1], (float) r[2]);
      }
    tft.glEnd();
}
