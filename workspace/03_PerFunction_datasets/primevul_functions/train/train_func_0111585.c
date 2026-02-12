static inline double PerceptibleReciprocal(const double x)
{
  double
    sign;


  sign=x < 0.0 ? -1.0 : 1.0;
  if ((sign*x) >= MagickEpsilon)
    return(1.0/x);
  return(sign/MagickEpsilon);
}
