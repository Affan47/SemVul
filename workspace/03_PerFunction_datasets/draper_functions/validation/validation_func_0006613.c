dataf(des,lf)
design *des;
lfit *lf;
{ INT d, i, j, ncm, nv, vc;

  d = lf->mi[MDIM];
  guessnv(&nv,&ncm,&vc,lf->dp,lf->mi);
  trchck(lf,nv,0,d,des->p,0);

  for (i=0; i<nv; i++)
    for (j=0; j<d; j++) evptx(lf,i,j) = datum(lf,j,i);
  for (i=0; i<nv; i++)
  { des->vfun(des,lf,i);
    lf->s[i] = 0;
  }
  lf->nv = lf->nvm = nv; lf->nce = 0;
}
