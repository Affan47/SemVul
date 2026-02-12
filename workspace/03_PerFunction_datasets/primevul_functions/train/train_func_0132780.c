static double Gaussian(const double x,const ResizeFilter *resize_filter)
{


  return(exp((double)(-resize_filter->coefficient[1]*x*x)));
}
