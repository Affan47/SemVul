thNextSpace(
  Th_Interp *interp,
  const char *zInput,
  int nInput,
  int *pnSpace
){
  int i;
  for(i=0; i<nInput && th_isspace(zInput[i]); i++);
  *pnSpace = i;
  return TH_OK;
}
