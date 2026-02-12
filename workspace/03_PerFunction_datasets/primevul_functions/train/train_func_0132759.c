static double Jinc(const double x,
  const ResizeFilter *magick_unused(resize_filter))
{
  magick_unreferenced(resize_filter);


  if (x == 0.0)
    return(0.5*MagickPI);
  return(BesselOrderOne(MagickPI*x)/x);
}
