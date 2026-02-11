SDPConeVecCreate(int n ,SDPConeVec *V){
  int info;
  V->dim=n;
  if (n>0){
    nvecs++;
    DSDPCALLOC2(&(V->val),double,n,&info);DSDPCHKERR(info);
  } else {
    V->val=NULL;
  }
  return 0;
}
