static int zipfileReadData(
  FILE *pFile,
  u8 *aRead,
  int nRead,
  i64 iOff,
  char **pzErrmsg
){
  size_t n;
  fseek(pFile, (long)iOff, SEEK_SET);
  n = fread(aRead, 1, nRead, pFile);
  if( (int)n!=nRead ){
    *pzErrmsg = sqlite3_mprintf("error in fread()");
    return SQLITE_ERROR;
  }
  return SQLITE_OK;
}
