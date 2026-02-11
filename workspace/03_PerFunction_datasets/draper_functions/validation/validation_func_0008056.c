DSDPCGSetup(DSDPCG *sles,DSDPVec X){
  int info;
  DSDPFunctionBegin;
  info=DSDPVecGetSize(X,&sles->m);DSDPCHKERR(info);
  if (sles->setup2==0){
    info = DSDPVecDuplicate(X,&sles->R); DSDPCHKERR(info);
    info = DSDPVecDuplicate(X,&sles->P); DSDPCHKERR(info);
    info = DSDPVecDuplicate(X,&sles->BP); DSDPCHKERR(info);
    info = DSDPVecDuplicate(X,&sles->BR); DSDPCHKERR(info);
    info = DSDPVecDuplicate(X,&sles->Diag); DSDPCHKERR(info);
    info = DSDPVecDuplicate(X,&sles->TTT); DSDPCHKERR(info);
  }
  sles->setup2=1;
  DSDPFunctionReturn(0);
}
