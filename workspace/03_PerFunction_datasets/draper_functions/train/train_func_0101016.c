c_ekkrwcs(const EKKfactinfo *fact,double *dluval, int *hcoli, int *mrstrt,
	    const int *hinrow, const EKKHlink *mwork,
	    int nfirst)
{
#if 0
  int *hcoli	= fact->xecadr;
  double *dluval	= fact->xeeadr;
  double *dvalpv = fact->kw3adr;
  int *mrstrt	= fact->xrsadr;
  int *hrowi	= fact->xeradr;
  int *mcstrt	= fact->xcsadr;
  int *hinrow	= fact->xrnadr;
  int *hincol	= fact->xcnadr;
  int *hpivro	= fact->krpadr;
  int *hpivco	= fact->kcpadr;
#endif
  int i, k, k1, k2, nz;
  int irow, iput;
  const int nrow	= fact->nrow;


  iput = 1;
  irow = nfirst;
  for (i = 1; i <= nrow; ++i) {
    nz = hinrow[irow];
    k1 = mrstrt[irow];
    if (k1 != iput) {
      mrstrt[irow] = iput;
      k2 = k1 + nz - 1;
      for (k = k1; k <= k2; ++k) {
	dluval[iput] = dluval[k];
	hcoli[iput] = hcoli[k];
	++iput;
      }
    } else {
      iput += nz;
    }
    irow = mwork[irow].suc;
  }

  return (iput);
}
