after(FXchar c,FXint n) const {
  register FXint len=length();
  register FXint p=0;
  if(0<n){
    while(p<len){
      p++;
      if(str[p-1]==c && --n==0) break;
      }
    }
  return FXString(str+p,len-p);
  }
