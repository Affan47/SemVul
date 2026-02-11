est_search_uvset(ESTDB *db, int *nump, CBMAP *hints, int add){
  ESTSCORE *scores;
  char *vbuf, numbuf[ESTNUMBUFSIZ];
  int snum, smax;
  assert(db && nump);
  smax = ESTALLOCUNIT;
  CB_MALLOC(scores, smax * sizeof(ESTSCORE));
  snum = 0;
  vlcurfirst(db->listdb);
  while((vbuf = vlcurval(db->listdb, NULL)) != NULL){
    if(snum >= smax){
      smax *= 2;
      CB_REALLOC(scores, smax * sizeof(ESTSCORE));
    }
    scores[snum].id = atoi(vbuf);
    scores[snum].score = 0;
    scores[snum].value = NULL;
    snum++;
    free(vbuf);
    vlcurnext(db->listdb);
  }
  *nump = snum;
  if(hints){
    sprintf(numbuf, "%d", snum * (add ? 1 : -1));
    cbmapput(hints, ESTOPUVSET, -1, numbuf, -1, TRUE);
  }
  return scores;
}
