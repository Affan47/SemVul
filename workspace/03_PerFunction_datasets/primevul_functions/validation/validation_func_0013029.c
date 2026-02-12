int sqlite3VdbeRecordCompare(
  int nKey1, const void *pKey1,
  UnpackedRecord *pPKey2
){
  return sqlite3VdbeRecordCompareWithSkip(nKey1, pKey1, pPKey2, 0);
}
