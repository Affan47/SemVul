Locate_det_zero(const double** mat_b, int *N_root_add)
{
  double **a;
  int i;
  int N;
  int flag_sign;
  double lambda;
  double lambda_root, dlambda ;

  double root[5000];
  double *root_temp;

  int zero_monitor = 0;


  a=dmatrix(1,Alphsize,1,Alphsize);


  N = 2 + max(400, ((int) (Lambda_UB-0)/0.005));

  dlambda = (Lambda_UB)/(N*1.0);


  double l_here[N+1];
  double s_here[N+1];

  for (i=0; i< N ; i++){
    lambda = (i+1)*dlambda;
    s_here[i] = Check_det(mat_b, a,lambda);
    l_here[i] = lambda;
  }

  if (s_here[0] < 0.0) flag_sign = -1;
  if (s_here[0] > 0.0 ) flag_sign = 1;
  if (fabs(s_here[0])/exp(l_here[0]*(r_max_m+c_max_m)/2.0) <= Epsilon) {
    root[zero_monitor++] = l_here[0];
    flag_sign = 0;
  }

  for (i=1;i<N; i++){
    if ((flag_sign != 0)&& (fabs(s_here[i])>Epsilon)) {
      if (s_here[i-1]*s_here[i] < 0){

	lambda_root = Nail_det(mat_b, flag_sign, l_here[i-1], l_here[i]);
	root[zero_monitor++] = lambda_root;
	flag_sign = -flag_sign;

      }
    }
    else {
      if (s_here[i] < 0.0) flag_sign = -1;
      if (s_here[i] > 0.0 ) flag_sign = 1;
      if (fabs(s_here[i])/exp(l_here[i]*(r_max_m+c_max_m)/2.0) <= Epsilon) {
	root[zero_monitor++] = l_here[i];
      }
    }
  }

  root_temp = (double *)malloc(zero_monitor*sizeof(double));
  *N_root_add = zero_monitor;
  if (zero_monitor > 0) {
    if (zero_monitor >= N/4) {


      free( root_temp );
      return NULL;

    }
    for (i = 0; i < zero_monitor; i++){
      root_temp[i] = root[i];

    }
  }
  free_dmatrix( a, 1, Alphsize, 1, Alphsize );
  return root_temp;

}
