create_fmasc(int nts, double fdata, double fmin, double fmax, int *fmasc)
{
  double dimin, dimax;
  int i, imin, imax;

  dimin = nts*fmin / fdata;
  dimax = nts*fmax / fdata;

  imin = dimin<0 ? 0 : (int)floor(dimin);
  imax = ceil(dimax)>nts/2 ? nts/2 : (int) ceil(dimax);

  fmasc[imin] = 1;
  for ( i = imin+1; i <= imax; i++ )
    fmasc[i] = fmasc[nts-i] = 1;

}
