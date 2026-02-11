cray_skel_UseVColor(int sel, Geom *geom, va_list *args)
{
  Skel *s = (Skel *)geom;
  int i, j, k, ic;
  ColorA *def;

  def = va_arg(*args, ColorA *);
  if (s->vc == NULL) {
    s->vc = OOGLNewNE(ColorA, s->nvert, msg);
  }


  for (i = 0; i < s->nvert; i++) s->vc[i] = *def;


  if (s->geomflags & FACET_C) {
    for (i = 0; i < s->nlines; i++) {
      if (s->l[i].nc == 0) {
	continue;
      }
      ic = s->l[i].c0;
      for (j = 0; j < s->l[i].nv; j++) {
	k = s->vi[s->l[i].v0+j];
	s->vc[k] = s->c[ic];
      }
    }
  }

  s->geomflags |= VERT_C;

  return (void *)geom;
}
