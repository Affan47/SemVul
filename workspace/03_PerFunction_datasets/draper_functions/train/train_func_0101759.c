est_crput(CURIA *curia, int zmode, int id, const char *vbuf, int vsiz, int dmode){
  char *zbuf;
  int zsiz;
  assert(curia && id > 0 && vbuf && vsiz >= 0);
  switch(zmode){
  case ESTDFZLIB:
    if(!(zbuf = est_deflate(vbuf, vsiz, &zsiz, -1))){
      dpecode = ESTEMISC;
      return FALSE;
    }
    if(!crput(curia, (char *)&id, sizeof(int), zbuf, zsiz, dmode)){
      free(zbuf);
      return FALSE;
    }
    free(zbuf);
    break;
  case ESTDFLZO:
    if(!(zbuf = est_lzoencode(vbuf, vsiz, &zsiz))){
      dpecode = ESTEMISC;
      return FALSE;
    }
    if(!crput(curia, (char *)&id, sizeof(int), zbuf, zsiz, dmode)){
      free(zbuf);
      return FALSE;
    }
    free(zbuf);
    break;
  case ESTDFBZIP:
    if(!(zbuf = est_bzencode(vbuf, vsiz, &zsiz))){
      dpecode = ESTEMISC;
      return FALSE;
    }
    if(!crput(curia, (char *)&id, sizeof(int), zbuf, zsiz, dmode)){
      free(zbuf);
      return FALSE;
    }
    free(zbuf);
    break;
  default:
    if(!crput(curia, (char *)&id, sizeof(int), vbuf, vsiz, dmode)) return FALSE;
    break;
  }
  return TRUE;
}
