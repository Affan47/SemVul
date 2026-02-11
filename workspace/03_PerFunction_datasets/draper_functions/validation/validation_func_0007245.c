boundingbox(struct mesh *m, struct behavior *b)
#else
void boundingbox(m, b)
struct mesh *m;
struct behavior *b;
#endif

{
  struct otri inftri;
  REAL width;

  if (b->verbose) {
    printf("  Creating triangular bounding box.\n");
  }

  width = m->xmax - m->xmin;
  if (m->ymax - m->ymin > width) {
    width = m->ymax - m->ymin;
  }
  if (width == 0.0) {
    width = 1.0;
  }

  m->infvertex1 = (vertex) trimalloc(m->vertices.itembytes);
  m->infvertex2 = (vertex) trimalloc(m->vertices.itembytes);
  m->infvertex3 = (vertex) trimalloc(m->vertices.itembytes);
  m->infvertex1[0] = m->xmin - 50.0 * width;
  m->infvertex1[1] = m->ymin - 40.0 * width;
  m->infvertex2[0] = m->xmax + 50.0 * width;
  m->infvertex2[1] = m->ymin - 40.0 * width;
  m->infvertex3[0] = 0.5 * (m->xmin + m->xmax);
  m->infvertex3[1] = m->ymax + 60.0 * width;


  maketriangle(m, b, &inftri);
  setorg(inftri, m->infvertex1);
  setdest(inftri, m->infvertex2);
  setapex(inftri, m->infvertex3);


  m->dummytri[0] = (triangle) inftri.tri;
  if (b->verbose > 2) {
    printf("  Creating ");
    printtriangle(m, b, &inftri);
  }
}
