int sqlite3ColumnsFromExprList(
  Parse *pParse,
  ExprList *pEList,
  i16 *pnCol,
  Column **paCol
){
  sqlite3 *db = pParse->db;
  int i, j;
  u32 cnt;
  Column *aCol, *pCol;
  int nCol;
  char *zName;
  int nName;
  Hash ht;

  sqlite3HashInit(&ht);
  if( pEList ){
    nCol = pEList->nExpr;
    aCol = sqlite3DbMallocZero(db, sizeof(aCol[0])*nCol);
    testcase( aCol==0 );
    if( nCol>32767 ) nCol = 32767;
  }else{
    nCol = 0;
    aCol = 0;
  }
  assert( nCol==(i16)nCol );
  *pnCol = nCol;
  *paCol = aCol;

  for(i=0, pCol=aCol; i<nCol && !db->mallocFailed; i++, pCol++){


    if( (zName = pEList->a[i].zEName)!=0 && pEList->a[i].eEName==ENAME_NAME ){

    }else{
      Expr *pColExpr = sqlite3ExprSkipCollateAndLikely(pEList->a[i].pExpr);
      while( pColExpr->op==TK_DOT ){
        pColExpr = pColExpr->pRight;
        assert( pColExpr!=0 );
      }
      if( pColExpr->op==TK_COLUMN ){

        int iCol = pColExpr->iColumn;
        Table *pTab = pColExpr->y.pTab;
        assert( pTab!=0 );
        if( iCol<0 ) iCol = pTab->iPKey;
        zName = iCol>=0 ? pTab->aCol[iCol].zName : "rowid";
      }else if( pColExpr->op==TK_ID ){
        assert( !ExprHasProperty(pColExpr, EP_IntValue) );
        zName = pColExpr->u.zToken;
      }else{

        zName = pEList->a[i].zEName;
      }
    }
    if( zName && !sqlite3IsTrueOrFalse(zName) ){
      zName = sqlite3DbStrDup(db, zName);
    }else{
      zName = sqlite3MPrintf(db,"column%d",i+1);
    }


    cnt = 0;
    while( zName && sqlite3HashFind(&ht, zName)!=0 ){
      nName = sqlite3Strlen30(zName);
      if( nName>0 ){
        for(j=nName-1; j>0 && sqlite3Isdigit(zName[j]); j--){}
        if( zName[j]==':' ) nName = j;
      }
      zName = sqlite3MPrintf(db, "%.*z:%u", nName, zName, ++cnt);
      if( cnt>3 ) sqlite3_randomness(sizeof(cnt), &cnt);
    }
    pCol->zName = zName;
    sqlite3ColumnPropertiesFromName(0, pCol);
    if( zName && sqlite3HashInsert(&ht, zName, pCol)==pCol ){
      sqlite3OomFault(db);
    }
  }
  sqlite3HashClear(&ht);
  if( db->mallocFailed ){
    for(j=0; j<i; j++){
      sqlite3DbFree(db, aCol[j].zName);
    }
    sqlite3DbFree(db, aCol);
    *paCol = 0;
    *pnCol = 0;
    return SQLITE_NOMEM_BKPT;
  }
  return SQLITE_OK;
}
