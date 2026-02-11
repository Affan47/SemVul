reassign(lf)
lfit *lf;
{ INT i, nvm, ncm, vc, d, k, p, *iw;
  double *tw, *ntw;
  setvarname(lf->tw,"__lfwork");
  setvarname(lf->iw,"__lfiwork");
  nvm = lf->nvm; ncm = lf->ncm; vc = lf->vc;
  tw = (double *)vdptr(lf->tw);
  iw = (INT *)vdptr(lf->iw);
  d = lf->mi[MDIM];
  p = lf->mi[MP];
  trchck(lf,2*nvm,ncm,d,p,vc);
  ntw = vdptr(lf->tw);


  k = nvm*d;
  memcpy(vdptr(lf->xxev),tw,k*sizeof(double));
  tw += k; ntw += 2*k;
  for (i=0; i<2*p+2*d+6; i++)
  { memcpy(ntw,tw,nvm*sizeof(double));
    tw += nvm; ntw += 2*nvm;
  }
  k = ncm;       memcpy(lf->sv,tw,k*sizeof(double));   tw += k;

  k = vc*ncm;       memcpy(lf->ce,iw,k*sizeof(INT)); iw += k;
  k = MAX(ncm,nvm); memcpy(lf->s,iw,k*sizeof(INT));  iw += k;
  k = MAX(ncm,nvm); memcpy(lf->lo,iw,k*sizeof(INT)); iw += k;
  k = MAX(ncm,nvm); memcpy(lf->hi,iw,k*sizeof(INT)); iw += k;
  deletename("__lfwork");
  deletename("__lfiwork");
}
