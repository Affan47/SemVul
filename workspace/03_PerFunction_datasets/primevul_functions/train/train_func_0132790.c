static double Bohman(const double x,
  const ResizeFilter *magick_unused(resize_filter))
{


  const double cosine = cos((double) (MagickPI*x));
  const double sine=sqrt(1.0-cosine*cosine);
  magick_unreferenced(resize_filter);
  return((1.0-x)*cosine+(1.0/MagickPI)*sine);
}
