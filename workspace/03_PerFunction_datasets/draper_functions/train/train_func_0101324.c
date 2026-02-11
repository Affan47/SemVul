mat_init(struct param p)
{
  unsigned int i;

  check_alloc(mat=(double**)malloc(sizeof(double*)*p.DIM));
  for (i=0;i<p.DIM;i++)
    check_alloc(mat[i]=(double*)malloc(sizeof(double)*p.DIM));
  check_alloc(av=(double*)malloc(sizeof(double)*p.DIM));
  isinitgetfields=1;
}
