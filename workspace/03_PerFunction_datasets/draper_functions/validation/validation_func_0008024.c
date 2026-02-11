DSDPRX( void *dspcone, double mu, DSDPVec y, DSDPVec dy, DSDPVec AX,double*tracxs){
  BDCone *K=(BDCone*)dspcone;
  double x,dss,ss=K->dss;
  int info;
  DSDPFunctionBegin;

  info=BComputeS(K,y,&ss);DSDPCHKERR(info);
  ss=1.0/ss;
  info=BComputeS(K,dy,&dss);DSDPCHKERR(info);
  x=mu*(ss+ss*dss*ss);
  DSDPLogInfo(0,2,"DOBJCone SS: %4.4e, RESIDUAL X: %4.4e\n",1.0/ss,x);
  if (fabs(x*ss)>1.0 && mu < 1) printf("Check Dual Min Bound\n");
  info=DSDPVecAXPY(-x,K->bb,AX);DSDPCHKERR(info);
  DSDPFunctionReturn(0);
}
