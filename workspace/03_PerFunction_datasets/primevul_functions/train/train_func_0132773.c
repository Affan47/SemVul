static double Blackman(const double x,
  const ResizeFilter *magick_unused(resize_filter))
{


  const double cosine = cos((double) (MagickPI*x));
  magick_unreferenced(resize_filter);
  return(0.34+cosine*(0.5+cosine*0.16));
}
