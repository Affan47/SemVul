Nail_det(const double** mat_b, int flag_sign, double lambda_min, double lambda_max)
{
  double **a;
  double lambda;
  double value;

  a = dmatrix(1,Alphsize,1,Alphsize);

  lambda = (lambda_min+lambda_max)/2.0;
  value = Check_det(mat_b, a, lambda);
  while ((fabs(value)>E_bound)&&(lambda > 0)){
    if (flag_sign*(value)<0) lambda_max = lambda;
    else if (flag_sign*(value)> 0) lambda_min = lambda;
    lambda = (lambda_min+lambda_max)/2.0;
    value = Check_det(mat_b, a, lambda);
  }
  free_dmatrix(a,1,Alphsize,1,Alphsize);
  return lambda;
}
