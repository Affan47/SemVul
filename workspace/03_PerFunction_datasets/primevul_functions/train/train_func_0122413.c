static int exprSrcCount(Walker *pWalker, Expr *pExpr){


  if( pExpr->op==TK_COLUMN || NEVER(pExpr->op==TK_AGG_COLUMN) ){
    int i;
    struct SrcCount *p = pWalker->u.pSrcCount;
    SrcList *pSrc = p->pSrc;
    int nSrc = pSrc ? pSrc->nSrc : 0;
    for(i=0; i<nSrc; i++){
      if( pExpr->iTable==pSrc->a[i].iCursor ) break;
    }
    if( i<nSrc ){
      p->nThis++;
    }else if( nSrc==0 || pExpr->iTable<pSrc->a[0].iCursor ){


      p->nOther++;
    }
  }
  return WRC_Continue;
}
