static int fts3SegReaderCursorAddZero(
  Fts3Table *p,
  int iLangid,
  const char *zTerm,
  int nTerm,
  Fts3MultiSegReader *pCsr
){
  return fts3SegReaderCursor(p,
      iLangid, 0, FTS3_SEGCURSOR_ALL, zTerm, nTerm, 0, 0,pCsr
  );
}
