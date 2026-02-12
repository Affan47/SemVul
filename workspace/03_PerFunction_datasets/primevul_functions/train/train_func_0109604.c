int sqlite3_vtab_rhs_value(
  sqlite3_index_info *pIdxInfo,
  int iCons,
  sqlite3_value **ppVal
){
  HiddenIndexInfo *pH = (HiddenIndexInfo*)&pIdxInfo[1];
  sqlite3_value *pVal = 0;
  int rc = SQLITE_OK;
  if( iCons<0 || iCons>=pIdxInfo->nConstraint ){
    rc = SQLITE_MISUSE;
  }else{
    if( pH->aRhs[iCons]==0 ){
      WhereTerm *pTerm = &pH->pWC->a[pIdxInfo->aConstraint[iCons].iTermOffset];
      rc = sqlite3ValueFromExpr(
          pH->pParse->db, pTerm->pExpr->pRight, ENC(pH->pParse->db),
          SQLITE_AFF_BLOB, &pH->aRhs[iCons]
      );
      testcase( rc!=SQLITE_OK );
    }
    pVal = pH->aRhs[iCons];
  }
  *ppVal = pVal;

  if( rc==SQLITE_OK && pVal==0 ){
    rc = SQLITE_NOTFOUND;
  }

  return rc;
}
