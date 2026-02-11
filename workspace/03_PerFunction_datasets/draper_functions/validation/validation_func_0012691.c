pal_rotate(Palette *p, float a, float r) {
  float s=sin(a)*r, c=cos(a)*r, x, y, z, x2, y2, k;
  int i;
  for (i=0; i<p->size; i++) {
    x = -sqrt(1.0/2)*p->cols[i].r +                    0    +sqrt(1.0/2)*p->cols[i].b;
    y = -sqrt(1.0/6)*p->cols[i].r +sqrt(2.0/3)*p->cols[i].g -sqrt(1.0/6)*p->cols[i].b;
    z = +sqrt(1.0/3)*p->cols[i].r +sqrt(1.0/3)*p->cols[i].g +sqrt(1.0/3)*p->cols[i].b;
    x2=x*c-y*s; y2=y*c+x*s;
    p->cols[i].r = -sqrt(1.0/2)*x2 -sqrt(1.0/6)*y2 +sqrt(1.0/3)*z;
    p->cols[i].g = +         0     +sqrt(2.0/3)*y2 +sqrt(1.0/3)*z;
    p->cols[i].b = +sqrt(1.0/2)*x2 -sqrt(1.0/6)*y2 +sqrt(1.0/3)*z;
  }
}
