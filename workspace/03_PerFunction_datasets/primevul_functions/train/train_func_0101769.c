int sqlite3Fts3EvalPhrasePoslist(
  Fts3Cursor *pCsr,
  Fts3Expr *pExpr,
  int iCol,
  char **ppOut
){
  Fts3Phrase *pPhrase = pExpr->pPhrase;
  Fts3Table *pTab = (Fts3Table *)pCsr->base.pVtab;
  char *pIter;
  int iThis;
  sqlite3_int64 iDocid;


  *ppOut = 0;
  assert( iCol>=0 && iCol<pTab->nColumn );
  if( (pPhrase->iColumn<pTab->nColumn && pPhrase->iColumn!=iCol) ){
    return SQLITE_OK;
  }

  iDocid = pExpr->iDocid;
  pIter = pPhrase->doclist.pList;
  if( iDocid!=pCsr->iPrevId || pExpr->bEof ){
    int rc = SQLITE_OK;
    int bDescDoclist = pTab->bDescIdx;
    int iMul;
    int bOr = 0;
    u8 bEof = 0;
    u8 bTreeEof = 0;
    Fts3Expr *p;
    Fts3Expr *pNear;


    pNear = pExpr;
    for(p=pExpr->pParent; p; p=p->pParent){
      if( p->eType==FTSQUERY_OR ) bOr = 1;
      if( p->eType==FTSQUERY_NEAR ) pNear = p;
      if( p->bEof ) bTreeEof = 1;
    }
    if( bOr==0 ) return SQLITE_OK;


    if( pPhrase->bIncr ){
      int bEofSave = pNear->bEof;
      fts3EvalRestart(pCsr, pNear, &rc);
      while( rc==SQLITE_OK && !pNear->bEof ){
        fts3EvalNextRow(pCsr, pNear, &rc);
        if( bEofSave==0 && pNear->iDocid==iDocid ) break;
      }
      assert( rc!=SQLITE_OK || pPhrase->bIncr==0 );
    }
    if( bTreeEof ){
      while( rc==SQLITE_OK && !pNear->bEof ){
        fts3EvalNextRow(pCsr, pNear, &rc);
      }
    }
    if( rc!=SQLITE_OK ) return rc;

    pIter = pPhrase->pOrPoslist;
    iDocid = pPhrase->iOrDocid;
    if( pCsr->bDesc==bDescDoclist ){
      bEof = (pIter >= (pPhrase->doclist.aAll + pPhrase->doclist.nAll));
      while( (pIter==0 || DOCID_CMP(iDocid, pCsr->iPrevId)<0 ) && bEof==0 ){
        sqlite3Fts3DoclistNext(
            bDescDoclist, pPhrase->doclist.aAll, pPhrase->doclist.nAll,
            &pIter, &iDocid, &bEof
        );
      }
    }else{
      bEof = !pPhrase->doclist.nAll || (pIter && pIter<=pPhrase->doclist.aAll);
      while( (pIter==0 || DOCID_CMP(iDocid, pCsr->iPrevId)>0 ) && bEof==0 ){
        int dummy;
        sqlite3Fts3DoclistPrev(
            bDescDoclist, pPhrase->doclist.aAll, pPhrase->doclist.nAll,
            &pIter, &iDocid, &dummy, &bEof
        );
      }
    }
    pPhrase->pOrPoslist = pIter;
    pPhrase->iOrDocid = iDocid;

    if( bEof || iDocid!=pCsr->iPrevId ) pIter = 0;
  }
  if( pIter==0 ) return SQLITE_OK;

  if( *pIter==0x01 ){
    pIter++;
    pIter += fts3GetVarint32(pIter, &iThis);
  }else{
    iThis = 0;
  }
  while( iThis<iCol ){
    fts3ColumnlistCopy(0, &pIter);
    if( *pIter==0x00 ) return SQLITE_OK;
    pIter++;
    pIter += fts3GetVarint32(pIter, &iThis);
  }
  if( *pIter==0x00 ){
    pIter = 0;
  }

  *ppOut = ((iCol==iThis)?pIter:0);
  return SQLITE_OK;
}
