BoundYConeAddX(LUBounds lucone, double mu, DSDPVec Y, DSDPVec DY, DSDPVec XLU, double *tracexs){
  int i,m,info;
  double sl,su,dsl,dsu,ux,lx;
  double dy,yy,xdots=0,xsum1=0,xsum2=0;
  double r,dr,rr,drr,cr;
  double lbound, ubound;

  DSDPFunctionBegin;
  LUConeValid(lucone);
  if (lucone->skipit==DSDP_TRUE){DSDPFunctionReturn(0);}
  info=DSDPVecGetSize(Y,&m);DSDPCHKERR(info);
  info=DSDPVecGetR(Y,&rr);DSDPCHKERR(info);
  info=DSDPVecGetC(Y,&cr);DSDPCHKERR(info);
  info=DSDPVecGetR(DY,&drr);DSDPCHKERR(info);
  r=rr*lucone->r; dr=drr*lucone->r;
  lbound=cr*lucone->lbound; ubound=cr*lucone->ubound;
  mu*=lucone->muscale;
  for (i=1;i<m-1;i++){
    info=DSDPVecGetElement(DY,i,&dy);DSDPCHKERR(info);
    info=DSDPVecGetElement(Y,i,&yy);DSDPCHKERR(info);
    sl=1.0/COMPUTELBS(lbound,yy,r);
    su=1.0/COMPUTEUBS(ubound,yy,r);
    dsl=COMPUTELBS(0,dy,dr);
    dsu=COMPUTEUBS(0,dy,dr);
    lx=mu*(sl-sl*dsl*sl);
    ux=mu*(su-su*dsu*su);
    info=DSDPVecAddElement(XLU,i,ux-lx);DSDPCHKERR(info);

    xsum1+=lx;
    xsum2+=ux;
    xdots+=lx/sl + ux/su;
  }
  info=DSDPVecAddC(XLU,ubound*xsum1-lbound*xsum2);DSDPCHKERR(info);
  info=DSDPVecAddR(XLU,xsum1+xsum2);DSDPCHKERR(info);
  *tracexs+=xdots;


  DSDPFunctionReturn(0);
}
