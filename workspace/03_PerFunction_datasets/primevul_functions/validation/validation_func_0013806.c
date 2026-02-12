static size_t poly_number_terms(double order)
{

  if ( order < 1 || order > 5 ||
       ( order != floor(order) && (order-1.5) > MagickEpsilon) )
    return 0;
  return((size_t) floor((order+1)*(order+2)/2));
}
