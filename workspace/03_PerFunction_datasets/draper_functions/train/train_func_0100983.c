purge(long n, long ll, double *r, double *q, double *ra,
	   double *qa, double *wrk, double *eta, double *oldeta, long step,
           double *rnmp, double tol) {
  double t, tq, tr, reps1, rnm = *rnmp;
  long k, iteration, flag, i;

  if (step < ll+2) return;

  k = svd_idamax(step - (ll+1), &eta[ll], 1) + ll;
  if (fabs(eta[k]) > reps) {
    reps1 = eps1 / reps;
    iteration = 0;
    flag = TRUE;
    while (iteration < 2 && flag) {
      if (rnm > tol) {


        tq = 0.0;
        tr = 0.0;
        for (i = ll; i < step; i++) {
          store(n,  RETRQ,  i,  wrk);
          t   = -svd_ddot(n, qa, 1, wrk, 1);
          tq += fabs(t);
          svd_daxpy(n,  t,  wrk,  1,  q,  1);
          t   = -svd_ddot(n, ra, 1, wrk, 1);
          tr += fabs(t);
          svd_daxpy(n, t, wrk, 1, r, 1);
        }
        svd_dcopy(n, q, 1, qa, 1);
        t   = -svd_ddot(n, r, 1, qa, 1);
        tr += fabs(t);
        svd_daxpy(n, t, q, 1, r, 1);
        svd_dcopy(n, r, 1, ra, 1);
        rnm = sqrt(svd_ddot(n, ra, 1, r, 1));
        if (tq <= reps1 && tr <= reps1 * rnm) flag = FALSE;
      }
      iteration++;
    }
    for (i = ll; i <= step; i++) {
      eta[i] = eps1;
      oldeta[i] = eps1;
    }
  }
  *rnmp = rnm;
  return;
}
