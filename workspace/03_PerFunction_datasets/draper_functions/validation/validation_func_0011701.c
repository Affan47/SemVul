matrix(int N)
{

  int i,j;
  MatrixT m;


  m = (MatrixT)malloc((size_t)((N)*sizeof(double*)));
  if(!m) {
    perror("weighbor::matrix::matrix(1)");
    exit(1);
  }


  m[0] = (double *)malloc((size_t)((N*N)*sizeof(double)));
  if(!m[0]) {
    perror("weighbor::matrix::matrix(2)");
    exit(1);
  }

  for(i=1;i<N;++i)
    m[i] = m[i-1]+N;


  for(i=0;i<N;++i)
    for(j=0;j<N;++j)
      m[i][j] = 0.0;

  return(m);

}
