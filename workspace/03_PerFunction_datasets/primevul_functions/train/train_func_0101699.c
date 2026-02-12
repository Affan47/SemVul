static int fts3PrefixParameter(
  const char *zParam,
  int *pnIndex,
  struct Fts3Index **apIndex
){
  struct Fts3Index *aIndex;
  int nIndex = 1;

  if( zParam && zParam[0] ){
    const char *p;
    nIndex++;
    for(p=zParam; *p; p++){
      if( *p==',' ) nIndex++;
    }
  }

  aIndex = sqlite3_malloc(sizeof(struct Fts3Index) * nIndex);
  *apIndex = aIndex;
  *pnIndex = nIndex;
  if( !aIndex ){
    return SQLITE_NOMEM;
  }

  memset(aIndex, 0, sizeof(struct Fts3Index) * nIndex);
  if( zParam ){
    const char *p = zParam;
    int i;
    for(i=1; i<nIndex; i++){
      int nPrefix;
      if( fts3GobbleInt(&p, &nPrefix) ) return SQLITE_ERROR;
      aIndex[i].nPrefix = nPrefix;
      p++;
    }
  }

  return SQLITE_OK;
}
