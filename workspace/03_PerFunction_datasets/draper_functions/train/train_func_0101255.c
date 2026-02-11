render_color_dots (GstBaseAudioVisualizer * base, guint32 * vdata,
    gint16 * adata, guint num_samples)
{
  GstSpaceScope *scope = (GstSpaceScope *) base;
  guint i, s;
  gint x, y, ox, oy;
  gfloat dx, dy;
  gint w = base->width, w1 = w - 2;
  gint h = base->height, h1 = h - 2;
  gdouble il, ir;
  gdouble f1l_l = scope->f1l_l, f1l_m = scope->f1l_m, f1l_h = scope->f1l_h;
  gdouble f1r_l = scope->f1r_l, f1r_m = scope->f1r_m, f1r_h = scope->f1r_h;
  gdouble f2l_l = scope->f2l_l, f2l_m = scope->f2l_m, f2l_h = scope->f2l_h;
  gdouble f2r_l = scope->f2r_l, f2r_m = scope->f2r_m, f2r_h = scope->f2r_h;


  ox = w / 2;
  oy = h / 2;
  dx = w / 65536.0;
  dy = h / 65536.0;
  s = 0;
  for (i = 0; i < num_samples; i++) {
    il = (gdouble) adata[s++];
    ir = (gdouble) adata[s++];

    filter (il, ir);

    x = (gint) (ox + f1l_l * dx);
    y = (gint) (oy + f1r_l * dy);
    x = CLAMP (x, 0, w1);
    y = CLAMP (y, 0, h1);
    draw_dot_c (vdata, x, y, w, 0x00FF0000);

    x = (gint) (ox + f2l_l * dx);
    y = (gint) (oy + f2r_l * dy);
    x = CLAMP (x, 0, w1);
    y = CLAMP (y, 0, h1);
    draw_dot_c (vdata, x, y, w, 0x0000FF00);

    x = (gint) (ox + (f2l_m + f2l_h) * dx);
    y = (gint) (oy + (f2r_m + f2r_h) * dy);
    x = CLAMP (x, 0, w1);
    y = CLAMP (y, 0, h1);
    draw_dot_c (vdata, x, y, w, 0x000000FF);
  }

  scope->f1l_l = f1l_l;
  scope->f1l_m = f1l_m;
  scope->f1l_h = f1l_h;
  scope->f1r_l = f1r_l;
  scope->f1r_m = f1r_m;
  scope->f1r_h = f1r_h;
  scope->f2l_l = f2l_l;
  scope->f2l_m = f2l_m;
  scope->f2l_h = f2l_h;
  scope->f2r_l = f2r_l;
  scope->f2r_m = f2r_m;
  scope->f2r_h = f2r_h;
}
