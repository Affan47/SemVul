static int exprNodeIsConstant(Walker *pWalker, Expr *pExpr){


  if( pWalker->eCode==2 && ExprHasProperty(pExpr, EP_FromJoin) ){
    pWalker->eCode = 0;
    return WRC_Abort;
  }

  switch( pExpr->op ){


    case TK_FUNCTION:
      if( (pWalker->eCode>=4 || ExprHasProperty(pExpr,EP_ConstFunc))
       && !ExprHasProperty(pExpr, EP_WinFunc)
      ){
        return WRC_Continue;
      }else{
        pWalker->eCode = 0;
        return WRC_Abort;
      }
    case TK_ID:


      if( sqlite3ExprIdToTrueFalse(pExpr) ){
        return WRC_Prune;
      }

    case TK_COLUMN:
    case TK_AGG_FUNCTION:
    case TK_AGG_COLUMN:
      testcase( pExpr->op==TK_ID );
      testcase( pExpr->op==TK_COLUMN );
      testcase( pExpr->op==TK_AGG_FUNCTION );
      testcase( pExpr->op==TK_AGG_COLUMN );
      if( ExprHasProperty(pExpr, EP_FixedCol) && pWalker->eCode!=2 ){
        return WRC_Continue;
      }
      if( pWalker->eCode==3 && pExpr->iTable==pWalker->u.iCur ){
        return WRC_Continue;
      }

    case TK_IF_NULL_ROW:
    case TK_REGISTER:
      testcase( pExpr->op==TK_REGISTER );
      testcase( pExpr->op==TK_IF_NULL_ROW );
      pWalker->eCode = 0;
      return WRC_Abort;
    case TK_VARIABLE:
      if( pWalker->eCode==5 ){


        pExpr->op = TK_NULL;
      }else if( pWalker->eCode==4 ){


        pWalker->eCode = 0;
        return WRC_Abort;
      }

    default:
      testcase( pExpr->op==TK_SELECT );
      testcase( pExpr->op==TK_EXISTS );
      return WRC_Continue;
  }
}
