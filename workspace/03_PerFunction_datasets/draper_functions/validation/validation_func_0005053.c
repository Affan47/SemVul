DSDPCreate(int m,DSDP* dsdpnew){

  DSDP dsdp;
  int info;

  DSDPFunctionBegin;

  DSDPCALLOC1(&dsdp,PD_DSDP,&info);DSDPCHKERR(info);
  *dsdpnew=dsdp;
  dsdp->keyid=DSDPKEY;


  DSDPEventLogInitialize();
  dsdp->m=m;
  dsdp->maxcones=0;
  dsdp->ncones=0;
  dsdp->K=0;
  dsdp->setupcalled=DSDP_FALSE;
  dsdp->ybcone=0;
  dsdp->ndroutines=0;

  info = DSDPVecCreateSeq(m+2,&dsdp->b);DSDPCHKERR(info);
  info = DSDPVecZero(dsdp->b);DSDPCHKERR(info);
  info = DSDPVecDuplicate(dsdp->b,&dsdp->y);DSDPCHKERR(info);
  info = DSDPVecDuplicate(dsdp->b,&dsdp->ytemp);DSDPCHKERR(info);
  info = DSDPVecZero(dsdp->y);DSDPCHKERR(info);
  info = DSDPVecSetC(dsdp->y,-1.0);DSDPCHKERR(info);

  info = DSDPAddRCone(dsdp,&dsdp->rcone);DSDPCHKERR(info);
  info = DSDPCreateLUBoundsCone(dsdp,&dsdp->ybcone);DSDPCHKERR(info);

  info=DSDPSetDefaultStatistics(dsdp);DSDPCHKERR(info);
  info=DSDPSetDefaultParameters(dsdp);DSDPCHKERR(info);
  info=DSDPSetDefaultMonitors(dsdp);DSDPCHKERR(info);


  info = DSDPSchurMatInitialize(&dsdp->M);DSDPCHKERR(info);
  info = DSDPSetDefaultSchurMatrixStructure(dsdp); DSDPCHKERR(info);
  info = DSDPCGInitialize(&dsdp->sles); DSDPCHKERR(info);


  DSDPFunctionReturn(0);
}
