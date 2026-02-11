fmt_dither(GPixmap *pm, const ddjvu_format_t *fmt, int x, int y)
{
  if (fmt->ditherbits < 8)
    return;
  else if (fmt->ditherbits < 15)
    pm->ordered_666_dither(x, y);
  else if (fmt->ditherbits < 24)
    pm->ordered_32k_dither(x, y);
}
