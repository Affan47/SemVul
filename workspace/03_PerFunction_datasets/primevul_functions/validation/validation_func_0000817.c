static int multiSelect(
  Parse *pParse,
  Select *p,
  SelectDest *pDest
){
  int rc = SQLITE_OK;
  Select *pPrior;
  Vdbe *v;
  SelectDest dest;
  Select *pDelete = 0;
  sqlite3 *db;


  assert( p && p->pPrior );
  assert( (p->selFlags & SF_Recursive)==0 || p->op==TK_ALL || p->op==TK_UNION );
  assert( p->selFlags & SF_Compound );
  db = pParse->db;
  pPrior = p->pPrior;
  dest = *pDest;
  if( pPrior->pOrderBy || pPrior->pLimit ){
    sqlite3ErrorMsg(pParse,"%s clause should come after %s not before",
      pPrior->pOrderBy!=0 ? "ORDER BY" : "LIMIT", selectOpName(p->op));
    rc = 1;
    goto multi_select_end;
  }

  v = sqlite3GetVdbe(pParse);
  assert( v!=0 );


  if( dest.eDest==SRT_EphemTab ){
    assert( p->pEList );
    sqlite3VdbeAddOp2(v, OP_OpenEphemeral, dest.iSDParm, p->pEList->nExpr);
    dest.eDest = SRT_Table;
  }


  if( p->selFlags & SF_MultiValue ){
    rc = multiSelectValues(pParse, p, &dest);
    if( rc>=0 ) goto multi_select_end;
    rc = SQLITE_OK;
  }


  assert( p->pEList && pPrior->pEList );
  assert( p->pEList->nExpr==pPrior->pEList->nExpr );

#ifndef SQLITE_OMIT_CTE
  if( p->selFlags & SF_Recursive ){
    generateWithRecursiveQuery(pParse, p, &dest);
  }else
#endif


  if( p->pOrderBy ){
    return multiSelectOrderBy(pParse, p, pDest);
  }else{

#ifndef SQLITE_OMIT_EXPLAIN
    if( pPrior->pPrior==0 ){
      ExplainQueryPlan((pParse, 1, "COMPOUND QUERY"));
      ExplainQueryPlan((pParse, 1, "LEFT-MOST SUBQUERY"));
    }
#endif


    switch( p->op ){
      case TK_ALL: {
        int addr = 0;
        int nLimit;
        assert( !pPrior->pLimit );
        pPrior->iLimit = p->iLimit;
        pPrior->iOffset = p->iOffset;
        pPrior->pLimit = p->pLimit;
        rc = sqlite3Select(pParse, pPrior, &dest);
        p->pLimit = 0;
        if( rc ){
          goto multi_select_end;
        }
        p->pPrior = 0;
        p->iLimit = pPrior->iLimit;
        p->iOffset = pPrior->iOffset;
        if( p->iLimit ){
          addr = sqlite3VdbeAddOp1(v, OP_IfNot, p->iLimit); VdbeCoverage(v);
          VdbeComment((v, "Jump ahead if LIMIT reached"));
          if( p->iOffset ){
            sqlite3VdbeAddOp3(v, OP_OffsetLimit,
                              p->iLimit, p->iOffset+1, p->iOffset);
          }
        }
        ExplainQueryPlan((pParse, 1, "UNION ALL"));
        rc = sqlite3Select(pParse, p, &dest);
        testcase( rc!=SQLITE_OK );
        pDelete = p->pPrior;
        p->pPrior = pPrior;
        p->nSelectRow = sqlite3LogEstAdd(p->nSelectRow, pPrior->nSelectRow);
        if( pPrior->pLimit
         && sqlite3ExprIsInteger(pPrior->pLimit->pLeft, &nLimit)
         && nLimit>0 && p->nSelectRow > sqlite3LogEst((u64)nLimit)
        ){
          p->nSelectRow = sqlite3LogEst((u64)nLimit);
        }
        if( addr ){
          sqlite3VdbeJumpHere(v, addr);
        }
        break;
      }
      case TK_EXCEPT:
      case TK_UNION: {
        int unionTab;
        u8 op = 0;
        int priorOp;
        Expr *pLimit;
        int addr;
        SelectDest uniondest;

        testcase( p->op==TK_EXCEPT );
        testcase( p->op==TK_UNION );
        priorOp = SRT_Union;
        if( dest.eDest==priorOp ){


          assert( p->pLimit==0 );
          unionTab = dest.iSDParm;
        }else{


          unionTab = pParse->nTab++;
          assert( p->pOrderBy==0 );
          addr = sqlite3VdbeAddOp2(v, OP_OpenEphemeral, unionTab, 0);
          assert( p->addrOpenEphm[0] == -1 );
          p->addrOpenEphm[0] = addr;
          findRightmost(p)->selFlags |= SF_UsesEphemeral;
          assert( p->pEList );
        }


        assert( !pPrior->pOrderBy );
        sqlite3SelectDestInit(&uniondest, priorOp, unionTab);
        rc = sqlite3Select(pParse, pPrior, &uniondest);
        if( rc ){
          goto multi_select_end;
        }


        if( p->op==TK_EXCEPT ){
          op = SRT_Except;
        }else{
          assert( p->op==TK_UNION );
          op = SRT_Union;
        }
        p->pPrior = 0;
        pLimit = p->pLimit;
        p->pLimit = 0;
        uniondest.eDest = op;
        ExplainQueryPlan((pParse, 1, "%s USING TEMP B-TREE",
                          selectOpName(p->op)));
        rc = sqlite3Select(pParse, p, &uniondest);
        testcase( rc!=SQLITE_OK );


        sqlite3ExprListDelete(db, p->pOrderBy);
        pDelete = p->pPrior;
        p->pPrior = pPrior;
        p->pOrderBy = 0;
        if( p->op==TK_UNION ){
          p->nSelectRow = sqlite3LogEstAdd(p->nSelectRow, pPrior->nSelectRow);
        }
        sqlite3ExprDelete(db, p->pLimit);
        p->pLimit = pLimit;
        p->iLimit = 0;
        p->iOffset = 0;


        assert( unionTab==dest.iSDParm || dest.eDest!=priorOp );
        if( dest.eDest!=priorOp ){
          int iCont, iBreak, iStart;
          assert( p->pEList );
          iBreak = sqlite3VdbeMakeLabel(pParse);
          iCont = sqlite3VdbeMakeLabel(pParse);
          computeLimitRegisters(pParse, p, iBreak);
          sqlite3VdbeAddOp2(v, OP_Rewind, unionTab, iBreak); VdbeCoverage(v);
          iStart = sqlite3VdbeCurrentAddr(v);
          selectInnerLoop(pParse, p, unionTab,
                          0, 0, &dest, iCont, iBreak);
          sqlite3VdbeResolveLabel(v, iCont);
          sqlite3VdbeAddOp2(v, OP_Next, unionTab, iStart); VdbeCoverage(v);
          sqlite3VdbeResolveLabel(v, iBreak);
          sqlite3VdbeAddOp2(v, OP_Close, unionTab, 0);
        }
        break;
      }
      default: assert( p->op==TK_INTERSECT ); {
        int tab1, tab2;
        int iCont, iBreak, iStart;
        Expr *pLimit;
        int addr;
        SelectDest intersectdest;
        int r1;


        tab1 = pParse->nTab++;
        tab2 = pParse->nTab++;
        assert( p->pOrderBy==0 );

        addr = sqlite3VdbeAddOp2(v, OP_OpenEphemeral, tab1, 0);
        assert( p->addrOpenEphm[0] == -1 );
        p->addrOpenEphm[0] = addr;
        findRightmost(p)->selFlags |= SF_UsesEphemeral;
        assert( p->pEList );


        sqlite3SelectDestInit(&intersectdest, SRT_Union, tab1);
        rc = sqlite3Select(pParse, pPrior, &intersectdest);
        if( rc ){
          goto multi_select_end;
        }


        addr = sqlite3VdbeAddOp2(v, OP_OpenEphemeral, tab2, 0);
        assert( p->addrOpenEphm[1] == -1 );
        p->addrOpenEphm[1] = addr;
        p->pPrior = 0;
        pLimit = p->pLimit;
        p->pLimit = 0;
        intersectdest.iSDParm = tab2;
        ExplainQueryPlan((pParse, 1, "%s USING TEMP B-TREE",
                          selectOpName(p->op)));
        rc = sqlite3Select(pParse, p, &intersectdest);
        testcase( rc!=SQLITE_OK );
        pDelete = p->pPrior;
        p->pPrior = pPrior;
        if( p->nSelectRow>pPrior->nSelectRow ){
          p->nSelectRow = pPrior->nSelectRow;
        }
        sqlite3ExprDelete(db, p->pLimit);
        p->pLimit = pLimit;


        assert( p->pEList );
        iBreak = sqlite3VdbeMakeLabel(pParse);
        iCont = sqlite3VdbeMakeLabel(pParse);
        computeLimitRegisters(pParse, p, iBreak);
        sqlite3VdbeAddOp2(v, OP_Rewind, tab1, iBreak); VdbeCoverage(v);
        r1 = sqlite3GetTempReg(pParse);
        iStart = sqlite3VdbeAddOp2(v, OP_RowData, tab1, r1);
        sqlite3VdbeAddOp4Int(v, OP_NotFound, tab2, iCont, r1, 0);
        VdbeCoverage(v);
        sqlite3ReleaseTempReg(pParse, r1);
        selectInnerLoop(pParse, p, tab1,
                        0, 0, &dest, iCont, iBreak);
        sqlite3VdbeResolveLabel(v, iCont);
        sqlite3VdbeAddOp2(v, OP_Next, tab1, iStart); VdbeCoverage(v);
        sqlite3VdbeResolveLabel(v, iBreak);
        sqlite3VdbeAddOp2(v, OP_Close, tab2, 0);
        sqlite3VdbeAddOp2(v, OP_Close, tab1, 0);
        break;
      }
    }

  #ifndef SQLITE_OMIT_EXPLAIN
    if( p->pNext==0 ){
      ExplainQueryPlanPop(pParse);
    }
  #endif
  }


  if( p->selFlags & SF_UsesEphemeral ){
    int i;
    KeyInfo *pKeyInfo;
    Select *pLoop;
    CollSeq **apColl;
    int nCol;

    assert( p->pNext==0 );
    nCol = p->pEList->nExpr;
    pKeyInfo = sqlite3KeyInfoAlloc(db, nCol, 1);
    if( !pKeyInfo ){
      rc = SQLITE_NOMEM_BKPT;
      goto multi_select_end;
    }
    for(i=0, apColl=pKeyInfo->aColl; i<nCol; i++, apColl++){
      *apColl = multiSelectCollSeq(pParse, p, i);
      if( 0==*apColl ){
        *apColl = db->pDfltColl;
      }
    }

    for(pLoop=p; pLoop; pLoop=pLoop->pPrior){
      for(i=0; i<2; i++){
        int addr = pLoop->addrOpenEphm[i];
        if( addr<0 ){


          assert( pLoop->addrOpenEphm[1]<0 );
          break;
        }
        sqlite3VdbeChangeP2(v, addr, nCol);
        sqlite3VdbeChangeP4(v, addr, (char*)sqlite3KeyInfoRef(pKeyInfo),
                            P4_KEYINFO);
        pLoop->addrOpenEphm[i] = -1;
      }
    }
    sqlite3KeyInfoUnref(pKeyInfo);
  }

multi_select_end:
  pDest->iSdst = dest.iSdst;
  pDest->nSdst = dest.nSdst;
  sqlite3SelectDelete(db, pDelete);
  return rc;
}
