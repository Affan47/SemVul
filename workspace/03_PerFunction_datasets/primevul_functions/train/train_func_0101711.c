static int fts3EvalNearTest(Fts3Expr *pExpr, int *pRc){
  int res = 1;


  if( *pRc==SQLITE_OK
   && pExpr->eType==FTSQUERY_NEAR
   && pExpr->bEof==0
   && (pExpr->pParent==0 || pExpr->pParent->eType!=FTSQUERY_NEAR)
  ){
    Fts3Expr *p;
    int nTmp = 0;
    char *aTmp;


    for(p=pExpr; p->pLeft; p=p->pLeft){
      nTmp += p->pRight->pPhrase->doclist.nList;
    }
    nTmp += p->pPhrase->doclist.nList;
    if( nTmp==0 ){
      res = 0;
    }else{
      aTmp = sqlite3_malloc(nTmp*2);
      if( !aTmp ){
        *pRc = SQLITE_NOMEM;
        res = 0;
      }else{
        char *aPoslist = p->pPhrase->doclist.pList;
        int nToken = p->pPhrase->nToken;

        for(p=p->pParent;res && p && p->eType==FTSQUERY_NEAR; p=p->pParent){
          Fts3Phrase *pPhrase = p->pRight->pPhrase;
          int nNear = p->nNear;
          res = fts3EvalNearTrim(nNear, aTmp, &aPoslist, &nToken, pPhrase);
        }

        aPoslist = pExpr->pRight->pPhrase->doclist.pList;
        nToken = pExpr->pRight->pPhrase->nToken;
        for(p=pExpr->pLeft; p && res; p=p->pLeft){
          int nNear;
          Fts3Phrase *pPhrase;
          assert( p->pParent && p->pParent->pLeft==p );
          nNear = p->pParent->nNear;
          pPhrase = (
              p->eType==FTSQUERY_NEAR ? p->pRight->pPhrase : p->pPhrase
              );
          res = fts3EvalNearTrim(nNear, aTmp, &aPoslist, &nToken, pPhrase);
        }
      }

      sqlite3_free(aTmp);
    }
  }

  return res;
}
