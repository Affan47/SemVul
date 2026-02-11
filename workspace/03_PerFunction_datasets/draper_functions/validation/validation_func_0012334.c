determinant(double *m,int n)
{

  int i=0;
  double det=1;


  for(i=n-1; i>=0; i--)
  {
    det = m[n *i+i]*det;
  }

return(det);
}
