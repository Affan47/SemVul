StrNLen32(const char *z, int N){
  int n = 0;
  while( (N-- != 0) && *(z++)!=0 ){ n++; }
  return n;
}
