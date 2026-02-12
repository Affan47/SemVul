static void whereIndexExprTrans(
  Index *pIdx,
  int iTabCur,
  int iIdxCur,
  WhereInfo *pWInfo
){
  int iIdxCol;
  ExprList *aColExpr;
  Table *pTab;
  Walker w;
  IdxExprTrans x;
  aColExpr = pIdx->aColExpr;
  if( aColExpr==0 && !pIdx->bHasVCol ){


    return;
  }
  pTab = pIdx->pTable;
  memset(&w, 0, sizeof(w));
  w.u.pIdxTrans = &x;
  x.iTabCur = iTabCur;
  x.iIdxCur = iIdxCur;
  for(iIdxCol=0; iIdxCol<pIdx->nColumn; iIdxCol++){
    i16 iRef = pIdx->aiColumn[iIdxCol];
    if( iRef==XN_EXPR ){
      assert( aColExpr->a[iIdxCol].pExpr!=0 );
      x.pIdxExpr = aColExpr->a[iIdxCol].pExpr;
      w.xExprCallback = whereIndexExprTransNode;
#ifndef SQLITE_OMIT_GENERATED_COLUMNS
    }else if( iRef>=0 && (pTab->aCol[iRef].colFlags & COLFLAG_VIRTUAL)!=0 ){
      x.iTabCol = iRef;
      w.xExprCallback = whereIndexExprTransColumn;
#endif
    }else{
      continue;
    }
    x.iIdxCol = iIdxCol;
    sqlite3WalkExpr(&w, pWInfo->pWhere);
    sqlite3WalkExprList(&w, pWInfo->pOrderBy);
    sqlite3WalkExprList(&w, pWInfo->pResultSet);
  }
}
