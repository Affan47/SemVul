static int fts3FilterMethod(
  sqlite3_vtab_cursor *pCursor,
  int idxNum,
  const char *idxStr,
  int nVal,
  sqlite3_value **apVal
){
  int rc = SQLITE_OK;
  char *zSql;
  int eSearch;
  Fts3Table *p = (Fts3Table *)pCursor->pVtab;
  Fts3Cursor *pCsr = (Fts3Cursor *)pCursor;

  sqlite3_value *pCons = 0;
  sqlite3_value *pLangid = 0;
  sqlite3_value *pDocidGe = 0;
  sqlite3_value *pDocidLe = 0;
  int iIdx;

  UNUSED_PARAMETER(idxStr);
  UNUSED_PARAMETER(nVal);

  eSearch = (idxNum & 0x0000FFFF);
  assert( eSearch>=0 && eSearch<=(FTS3_FULLTEXT_SEARCH+p->nColumn) );
  assert( p->pSegments==0 );


  iIdx = 0;
  if( eSearch!=FTS3_FULLSCAN_SEARCH ) pCons = apVal[iIdx++];
  if( idxNum & FTS3_HAVE_LANGID ) pLangid = apVal[iIdx++];
  if( idxNum & FTS3_HAVE_DOCID_GE ) pDocidGe = apVal[iIdx++];
  if( idxNum & FTS3_HAVE_DOCID_LE ) pDocidLe = apVal[iIdx++];
  assert( iIdx==nVal );


  sqlite3_finalize(pCsr->pStmt);
  sqlite3_free(pCsr->aDoclist);
  sqlite3_free(pCsr->aMatchinfo);
  sqlite3Fts3ExprFree(pCsr->pExpr);
  memset(&pCursor[1], 0, sizeof(Fts3Cursor)-sizeof(sqlite3_vtab_cursor));


  pCsr->iMinDocid = fts3DocidRange(pDocidGe, SMALLEST_INT64);
  pCsr->iMaxDocid = fts3DocidRange(pDocidLe, LARGEST_INT64);

  if( idxStr ){
    pCsr->bDesc = (idxStr[0]=='D');
  }else{
    pCsr->bDesc = p->bDescIdx;
  }
  pCsr->eSearch = (i16)eSearch;

  if( eSearch!=FTS3_DOCID_SEARCH && eSearch!=FTS3_FULLSCAN_SEARCH ){
    int iCol = eSearch-FTS3_FULLTEXT_SEARCH;
    const char *zQuery = (const char *)sqlite3_value_text(pCons);

    if( zQuery==0 && sqlite3_value_type(pCons)!=SQLITE_NULL ){
      return SQLITE_NOMEM;
    }

    pCsr->iLangid = 0;
    if( pLangid ) pCsr->iLangid = sqlite3_value_int(pLangid);

    assert( p->base.zErrMsg==0 );
    rc = sqlite3Fts3ExprParse(p->pTokenizer, pCsr->iLangid,
        p->azColumn, p->bFts4, p->nColumn, iCol, zQuery, -1, &pCsr->pExpr,
        &p->base.zErrMsg
    );
    if( rc!=SQLITE_OK ){
      return rc;
    }

    rc = fts3EvalStart(pCsr);
    sqlite3Fts3SegmentsClose(p);
    if( rc!=SQLITE_OK ) return rc;
    pCsr->pNextId = pCsr->aDoclist;
    pCsr->iPrevId = 0;
  }


  if( eSearch==FTS3_FULLSCAN_SEARCH ){
    zSql = sqlite3_mprintf(
        "SELECT %s ORDER BY rowid %s",
        p->zReadExprlist, (pCsr->bDesc ? "DESC" : "ASC")
    );
    if( zSql ){
      rc = sqlite3_prepare_v2(p->db, zSql, -1, &pCsr->pStmt, 0);
      sqlite3_free(zSql);
    }else{
      rc = SQLITE_NOMEM;
    }
  }else if( eSearch==FTS3_DOCID_SEARCH ){
    rc = fts3CursorSeekStmt(pCsr, &pCsr->pStmt);
    if( rc==SQLITE_OK ){
      rc = sqlite3_bind_value(pCsr->pStmt, 1, pCons);
    }
  }
  if( rc!=SQLITE_OK ) return rc;

  return fts3NextMethod(pCursor);
}
