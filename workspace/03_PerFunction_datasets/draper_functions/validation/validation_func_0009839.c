DSDPGetPPObjective(DSDP dsdp,double *ppobj){
  int info;
  double scale;
  DSDPFunctionBegin;
  DSDPValid(dsdp);
  info=DSDPGetScale(dsdp,&scale);DSDPCHKERR(info);
  *ppobj=(dsdp->ppobj)/scale;
  if (dsdp->cnorm==0) *ppobj=0;
  DSDPFunctionReturn(0);
}
