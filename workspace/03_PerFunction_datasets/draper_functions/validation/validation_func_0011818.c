bbox (xfieldP xf)
{
  static float	fscratch[3];
  static int	iscratch;
  static float	yellow[] = {1.0, 1.0, 0.0};

  ENTRY(("bbox(0x%x)",xf));

  SENDPERFIELD(NOT_LIT);

  glColor3fv ((const GLfloat *) &yellow[0]) ;
  glBegin (GL_LINE_STRIP);
  glVertex3fv((GLfloat*)&xf->box[0]);
  glVertex3fv((GLfloat*)&xf->box[1]);
  glVertex3fv((GLfloat*)&xf->box[3]);
  glVertex3fv((GLfloat*)&xf->box[2]);
  glVertex3fv((GLfloat*)&xf->box[0]);
  glVertex3fv((GLfloat*)&xf->box[4]);
  glVertex3fv((GLfloat*)&xf->box[5]);
  glVertex3fv((GLfloat*)&xf->box[7]);
  glVertex3fv((GLfloat*)&xf->box[6]);
  glVertex3fv((GLfloat*)&xf->box[4]);
  glEnd ();

  glBegin (GL_LINES);
  glVertex3fv((GLfloat*)&xf->box[2]);
  glVertex3fv((GLfloat*)&xf->box[6]);

  glVertex3fv((GLfloat*)&xf->box[3]);
  glVertex3fv((GLfloat*)&xf->box[7]);

  glVertex3fv((GLfloat*)&xf->box[1]);
  glVertex3fv((GLfloat*)&xf->box[5]);
  glEnd ();

  EXIT(("OK"));
  return OK;
}
