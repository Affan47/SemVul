nConvergence(unsigned int n){
  if(n == 0) n = 1;
  float *tmp = cscore;
  cscore = new float[n];
  if(Nconv < n){
    if(nconv < Nconv){
      memcpy(cscore, tmp, (nconv+1) * sizeof(float));
    }
    else{
      memcpy(&(cscore[Nconv-(nconv%Nconv)-1]), tmp,
	     ((nconv%Nconv)+1) * sizeof(float));
      memcpy(cscore, &(tmp[(nconv%Nconv)+1]),
	     (Nconv-(nconv%Nconv)-1) * sizeof(float));
    }
  }
  else{
    if(nconv < n){
      memcpy(cscore, tmp, (nconv+1) * sizeof(float));
    }
    else{
      if((nconv % Nconv) + 1 < n){
	memcpy(&(cscore[n-(nconv%Nconv)-1]), tmp,
	       ((nconv%Nconv)+1) * sizeof(float));
	memcpy(cscore, &(tmp[Nconv-(1+n-(nconv%Nconv))]), sizeof(float));
      }
      else{
	memcpy(cscore, &(tmp[1+(nconv%Nconv)-n]), n * sizeof(float));
      }
    }
  }

  Nconv = n;
  delete [] tmp;
  return Nconv;
}
