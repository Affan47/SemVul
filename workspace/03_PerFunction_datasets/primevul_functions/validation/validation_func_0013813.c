static double poly_basis_dy(ssize_t n, double x, double y)
{

  switch(n) {
    case  0:  return( 0.0 );
    case  1:  return( 0.0 );
    case  2:  return( 1.0 );
    case  3:  return(  x  );
    case  4:  return( 0.0 );
    case  5:  return(  y  );
    default:  return( poly_basis_dx(n-1,x,y) );
  }


}
