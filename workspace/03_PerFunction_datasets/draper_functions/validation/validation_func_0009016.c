esl_hxp_FitGuess(double *x, int n, ESL_HYPEREXP *h)
{
  double tmu;
  double mean;
  int    i,k;
  int    imin, imax;

  h->mu = x[0];
  for (k = 0; k < h->K; k++)
    {
      if (! h->fixmix)
	h->q[k] = 1 / (double)(k+1);

      imin = (int) ((double)(k*n)/(double)h->K);
      imax = (int) ((double)((k+1)*n)/(double)h->K);
      tmu = x[imin];
      mean = 0.;
      for (i = imin; i < imax; i++)
	mean += x[i] - tmu;
      mean /= (double)(imax-imin);
      h->lambda[k] = 1 / mean;
    }
  esl_vec_DNorm(h->q, h->K);
  return eslOK;
}
