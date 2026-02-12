static double Hamming(const double x,
  const ResizeFilter *magick_unused(resize_filter))
{


  const double cosine = cos((double) (MagickPI*x));
  magick_unreferenced(resize_filter);
  return(0.54+0.46*cosine);
}
