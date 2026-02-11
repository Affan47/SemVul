Get(integer i, integer j)
{
  doublereal returnValue = 0.0;
  integer    fortranJ = j + 1;
  integer    lower;
  integer    upper;


  if( m_MatrixInitialized != 0 )
    {

    if( m_MatrixFinalized == 0 )
      {
      this->Finalize();
      }


    lower = m_IA[i] - 1;
    upper = m_IA[i + 1] - 1;

    for( int k = lower; k < upper; k++ )
      {
      if( m_JA[k] == fortranJ )
        {
        returnValue = m_A[k];
        }
      }
    }

  return returnValue;
}
