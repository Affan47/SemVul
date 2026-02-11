LPConeSetup(void *dcone,DSDPVec y){
  int m,info;
  LPCone lpcone=(LPCone)dcone;
  DSDPFunctionBegin;
  if (lpcone->n<1) return 0;
  m=lpcone->m;
  info=DSDPVecCreateSeq(m+2,&lpcone->WY);DSDPCHKERR(info);
  info=DSDPVecDuplicate(lpcone->WY,&lpcone->WY2);DSDPCHKERR(info);
  info=DSDPVecDuplicate(lpcone->WY,&lpcone->Y);DSDPCHKERR(info);
  info=DSDPVecDuplicate(lpcone->C,&lpcone->WX);DSDPCHKERR(info);
  info=DSDPVecDuplicate(lpcone->C,&lpcone->WX2);DSDPCHKERR(info);
  info=DSDPVecDuplicate(lpcone->C,&lpcone->PS);DSDPCHKERR(info);
  info=DSDPVecDuplicate(lpcone->C,&lpcone->DS);DSDPCHKERR(info);
  info=DSDPVecDuplicate(lpcone->C,&lpcone->X);DSDPCHKERR(info);
  DSDPFunctionReturn(0);
}
