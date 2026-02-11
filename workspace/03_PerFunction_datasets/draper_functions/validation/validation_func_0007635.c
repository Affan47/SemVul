SMatInvert(void *S){
  spmat* SS=(spmat*)S;
  double *x,*b,*v=SS->sinv;
  int i,n=SS->n;

  b=SS->spsym->rw;x=b+n;

  if (v){
    for (i=0;i<n;i++){
      memset((void*)b,0,n*sizeof(double));
      b[i]=1.0;
      ChlSolve(SS->spsym, b, x);
      memcpy((void*)(v+i*n),(void*)x,n*sizeof(double));
    }
  }
  return 0;
}
