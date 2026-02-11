DSDPSetX( void *dspcone, double mu, DSDPVec y, DSDPVec dy){
  RCone *K=(RCone*)dspcone;
  int info;
  double rr,dr,trxs,r;
  DSDPFunctionBegin;

  info=DSDPVecGetR(y,&rr); DSDPCHKERR(info);
  info=DSDPVecGetR(dy,&dr); DSDPCHKERR(info);
  if (rr){
    r=-1.0/rr;
    K->x=mu*(r-r*dr*r);
    trxs=K->x/r;
    DSDPLogInfo(0,2,"RESIDUAL X (Minimum Penalty Parameter): %4.4e, Trace(XS): %4.4e\n",K->x,trxs);

  } else {
    K->x=0.0;
  }
  DSDPFunctionReturn(0);
}
