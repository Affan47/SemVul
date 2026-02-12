static double Kaiser(const double x,const ResizeFilter *resize_filter)
{


  return(resize_filter->coefficient[1]*I0(resize_filter->coefficient[0]*
    sqrt((double) (1.0-x*x))));
}
