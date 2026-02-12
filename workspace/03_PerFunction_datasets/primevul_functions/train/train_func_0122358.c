static Expr *exprDup(sqlite3 *db, Expr *p, int dupFlags, u8 **pzBuffer){
  Expr *pNew;
  u8 *zAlloc;
  u32 staticFlag;

  assert( db!=0 );
  assert( p );
  assert( dupFlags==0 || dupFlags==EXPRDUP_REDUCE );
  assert( pzBuffer==0 || dupFlags==EXPRDUP_REDUCE );


  if( pzBuffer ){
    zAlloc = *pzBuffer;
    staticFlag = EP_Static;
  }else{
    zAlloc = sqlite3DbMallocRawNN(db, dupedExprSize(p, dupFlags));
    staticFlag = 0;
  }
  pNew = (Expr *)zAlloc;

  if( pNew ){


    const unsigned nStructSize = dupedExprStructSize(p, dupFlags);
    const int nNewSize = nStructSize & 0xfff;
    int nToken;
    if( !ExprHasProperty(p, EP_IntValue) && p->u.zToken ){
      nToken = sqlite3Strlen30(p->u.zToken) + 1;
    }else{
      nToken = 0;
    }
    if( dupFlags ){
      assert( ExprHasProperty(p, EP_Reduced)==0 );
      memcpy(zAlloc, p, nNewSize);
    }else{
      u32 nSize = (u32)exprStructSize(p);
      memcpy(zAlloc, p, nSize);
      if( nSize<EXPR_FULLSIZE ){
        memset(&zAlloc[nSize], 0, EXPR_FULLSIZE-nSize);
      }
    }


    pNew->flags &= ~(EP_Reduced|EP_TokenOnly|EP_Static|EP_MemToken);
    pNew->flags |= nStructSize & (EP_Reduced|EP_TokenOnly);
    pNew->flags |= staticFlag;


    if( nToken ){
      char *zToken = pNew->u.zToken = (char*)&zAlloc[nNewSize];
      memcpy(zToken, p->u.zToken, nToken);
    }

    if( 0==((p->flags|pNew->flags) & (EP_TokenOnly|EP_Leaf)) ){

      if( ExprHasProperty(p, EP_xIsSelect) ){
        pNew->x.pSelect = sqlite3SelectDup(db, p->x.pSelect, dupFlags);
      }else{
        pNew->x.pList = sqlite3ExprListDup(db, p->x.pList, dupFlags);
      }
    }


    if( ExprHasProperty(pNew, EP_Reduced|EP_TokenOnly|EP_WinFunc) ){
      zAlloc += dupedExprNodeSize(p, dupFlags);
      if( !ExprHasProperty(pNew, EP_TokenOnly|EP_Leaf) ){
        pNew->pLeft = p->pLeft ?
                      exprDup(db, p->pLeft, EXPRDUP_REDUCE, &zAlloc) : 0;
        pNew->pRight = p->pRight ?
                       exprDup(db, p->pRight, EXPRDUP_REDUCE, &zAlloc) : 0;
      }
#ifndef SQLITE_OMIT_WINDOWFUNC
      if( ExprHasProperty(p, EP_WinFunc) ){
        pNew->y.pWin = sqlite3WindowDup(db, pNew, p->y.pWin);
        assert( ExprHasProperty(pNew, EP_WinFunc) );
      }
#endif
      if( pzBuffer ){
        *pzBuffer = zAlloc;
      }
    }else{
      if( !ExprHasProperty(p, EP_TokenOnly|EP_Leaf) ){
        if( pNew->op==TK_SELECT_COLUMN ){
          pNew->pLeft = p->pLeft;
          assert( p->iColumn==0 || p->pRight==0 );
          assert( p->pRight==0  || p->pRight==p->pLeft );
        }else{
          pNew->pLeft = sqlite3ExprDup(db, p->pLeft, 0);
        }
        pNew->pRight = sqlite3ExprDup(db, p->pRight, 0);
      }
    }
  }
  return pNew;
}
