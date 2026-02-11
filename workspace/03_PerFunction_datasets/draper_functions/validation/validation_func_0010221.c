convertMatrix(float *a, int nrl, int nrh, int ncl, int nch)
{
  int i, j, nrow=nrh-nrl+1, ncol=nch-ncl+1;
  float **m;


  m = (float **) pil_malloc((size_t) ((nrow+RANGE_END)*sizeof(float*)));

  if (!m)
    {
     abort();
    }

  m += RANGE_END;
  m -= nrl;

  m[nrl] = a - ncl;
  for(i=1,j=nrl+1; i<nrow; i++,j++) m[j] = m[j-1]+ncol;

  return m;
}
