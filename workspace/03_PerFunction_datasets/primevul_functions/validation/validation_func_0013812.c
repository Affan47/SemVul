static double poly_basis_dx(ssize_t n, double x, double y)
{

  switch(n) {
    case  0:  return( 0.0 );
    case  1:  return( 1.0 );
    case  2:  return( 0.0 );
    case  3:  return(  y  );
    case  4:  return(  x  );
    case  5:  return( 0.0 );
    case  6:  return( x*x );
    case  7:  return( x*y );
    case  8:  return( y*y );
    case  9:  return( 0.0 );
    case 10:  return( x*x*x );
    case 11:  return( x*x*y );
    case 12:  return( x*y*y );
    case 13:  return( y*y*y );
    case 14:  return( 0.0 );
    case 15:  return( x*x*x*x );
    case 16:  return( x*x*x*y );
    case 17:  return( x*x*y*y );
    case 18:  return( x*y*y*y );
    case 19:  return( y*y*y*y );
    case 20:  return( 0.0 );
  }
  return( 0.0 );
}
