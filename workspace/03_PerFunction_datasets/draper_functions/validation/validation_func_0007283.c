solve_linear_equation_system(int n,
			     const ergo_real* matrix,
			     const ergo_real* RHS,
			     ergo_real* resultVector)
{
  integer NRHS = 1;
  integer n2 = n;
  integer info;
  ergo_real* A = new ergo_real[n*n];
  integer* IPIV = new integer[n];

  memcpy(A, matrix, n*n*sizeof(ergo_real));
  memcpy(resultVector, RHS, n*sizeof(ergo_real));

  template_lapack_gesv(&n2, &NRHS, A, &n2, IPIV, resultVector, &n2, &info);
  if(info != 0)
    {
      do_output(LOG_CAT_ERROR, LOG_AREA_LOWLEVEL, "ERROR in dgesv_");
      return -1;
    }

  delete [] A;
  delete [] IPIV;

  return 0;
}
