Normalize()
{
  double *x = Values;
  double den;
  if ( (den = Norm(x)) != 0.0 )
    {
    for (int i=0; i < 3; i++)
      {
      x[i] /= den;
      }
    }
  x = Values+3;
  if ( (den = Norm(x)) != 0.0 )
    {
    for (int i=0; i < 3; i++)
      {
      x[i] /= den;
      }
    }
}
