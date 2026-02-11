init_noise(struct param p,unsigned long seed)
{
  unsigned long i,j;
  double *noi;

  rnd_init(seed);

  for (i=0;i<10000;i++) {
    rnd_long();
    gaussian(1.0);
  }

  if (p.AR_SIZE > 0) {
    check_alloc(noi=(double*)malloc(sizeof(double)*p.DIM));

    for (i=0;i<p.DIM;i++)
      for (j=0;j<p.AR_SIZE;j++)
	p.noise_hist[i][j]=gaussian(p.AR_SIGMA[i]);

    for (i=0;i<10000;i++)
      get_ar_noise(p,noi);

    free(noi);
  }
}
