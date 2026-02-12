MagickPrivate double GetResizeFilterWeight(const ResizeFilter *resize_filter,
  const double x)
{
  double
    scale,
    weight,
    x_blur;


  assert(resize_filter != (ResizeFilter *) NULL);
  assert(resize_filter->signature == MagickCoreSignature);
  x_blur=fabs((double) x)/resize_filter->blur;
  if ((resize_filter->window_support < MagickEpsilon) ||
      (resize_filter->window == Box))
    scale=1.0;
  else
    {
      scale=resize_filter->scale;
      scale=resize_filter->window(x_blur*scale,resize_filter);
    }
  weight=scale*resize_filter->filter(x_blur,resize_filter);
  return(weight);
}
