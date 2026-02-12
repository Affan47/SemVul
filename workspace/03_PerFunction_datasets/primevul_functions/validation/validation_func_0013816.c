static const char *poly_basis_str(ssize_t n)
{

  switch(n) {
    case  0:  return("");
    case  1:  return("*ii");
    case  2:  return("*jj");
    case  3:  return("*ii*jj");
    case  4:  return("*ii*ii");
    case  5:  return("*jj*jj");
    case  6:  return("*ii*ii*ii");
    case  7:  return("*ii*ii*jj");
    case  8:  return("*ii*jj*jj");
    case  9:  return("*jj*jj*jj");
    case 10:  return("*ii*ii*ii*ii");
    case 11:  return("*ii*ii*ii*jj");
    case 12:  return("*ii*ii*jj*jj");
    case 13:  return("*ii*jj*jj*jj");
    case 14:  return("*jj*jj*jj*jj");
    case 15:  return("*ii*ii*ii*ii*ii");
    case 16:  return("*ii*ii*ii*ii*jj");
    case 17:  return("*ii*ii*ii*jj*jj");
    case 18:  return("*ii*ii*jj*jj*jj");
    case 19:  return("*ii*jj*jj*jj*jj");
    case 20:  return("*jj*jj*jj*jj*jj");
  }
  return( "UNKNOWN" );
}
