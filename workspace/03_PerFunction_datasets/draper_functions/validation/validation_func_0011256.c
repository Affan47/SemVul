FXStringVal(FXulong num,FXint base){
  FXchar buf[66];
  register FXchar *p=buf+66;
  register FXulong nn=num;
  if(base<2 || base>16){ fxerror("FXStringVal: base out of range.\n"); }
  do{
    *--p=FXString::HEX[nn%base];
    nn/=base;
    }
  while(nn);
  FXASSERT(buf<=p);
  return FXString(p,buf+66-p);
  }
