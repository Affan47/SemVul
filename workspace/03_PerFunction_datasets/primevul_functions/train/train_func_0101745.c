static int fts3ColumnMethod(
  sqlite3_vtab_cursor *pCursor,
  sqlite3_context *pCtx,
  int iCol
){
  int rc = SQLITE_OK;
  Fts3Cursor *pCsr = (Fts3Cursor *) pCursor;
  Fts3Table *p = (Fts3Table *)pCursor->pVtab;


  assert( iCol>=0 && iCol<=p->nColumn+2 );

  if( iCol==p->nColumn+1 ){


    sqlite3_result_int64(pCtx, pCsr->iPrevId);
  }else if( iCol==p->nColumn ){


    sqlite3_result_blob(pCtx, &pCsr, sizeof(pCsr), SQLITE_TRANSIENT);
  }else if( iCol==p->nColumn+2 && pCsr->pExpr ){
    sqlite3_result_int64(pCtx, pCsr->iLangid);
  }else{


    rc = fts3CursorSeek(0, pCsr);

    if( rc==SQLITE_OK ){
      if( iCol==p->nColumn+2 ){
        int iLangid = 0;
        if( p->zLanguageid ){
          iLangid = sqlite3_column_int(pCsr->pStmt, p->nColumn+1);
        }
        sqlite3_result_int(pCtx, iLangid);
      }else if( sqlite3_data_count(pCsr->pStmt)>(iCol+1) ){
        sqlite3_result_value(pCtx, sqlite3_column_value(pCsr->pStmt, iCol+1));
      }
    }
  }

  assert( ((Fts3Table *)pCsr->base.pVtab)->pSegments==0 );
  return rc;
}
