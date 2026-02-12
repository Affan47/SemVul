static double Lagrange(const double x,const ResizeFilter *resize_filter)
{
  double
    value;

  register ssize_t
    i;

  ssize_t
    n,
    order;


  if (x > resize_filter->support)
    return(0.0);
  order=(ssize_t) (2.0*resize_filter->window_support);
  n=(ssize_t) (resize_filter->window_support+x);
  value=1.0f;
  for (i=0; i < order; i++)
    if (i != n)
      value*=(n-i-x)/(n-i);
  return(value);
}
