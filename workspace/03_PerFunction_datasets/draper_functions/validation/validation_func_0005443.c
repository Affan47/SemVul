color_shade (double *r,
             double *g,
             double *b,
             double  k)
{
  double h, s, v;

  gtk_rgb_to_hsv (*r, *g, *b, &h, &s, &v);

  s *= k;
  if (s > 1.0)
    s = 1.0;
  else if (s < 0.0)
    s = 0.0;

  v *= k;
  if (v > 1.0)
    v = 1.0;
  else if (v < 0.0)
    v = 0.0;

  gtk_hsv_to_rgb (h, s, v, r, g, b);
}
