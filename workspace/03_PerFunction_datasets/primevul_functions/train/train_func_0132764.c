static double Cosine(const double x,
  const ResizeFilter *magick_unused(resize_filter))
{
  magick_unreferenced(resize_filter);


  return(cos((double) (MagickPI2*x)));
}
