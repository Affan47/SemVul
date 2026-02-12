static void windowCodeRangeTest(
  WindowCodeArg *p,
  int op,
  int csr1,
  int regVal,
  int csr2,
  int lbl
){
  Parse *pParse = p->pParse;
  Vdbe *v = sqlite3GetVdbe(pParse);
  ExprList *pOrderBy = p->pMWin->pOrderBy;
  int reg1 = sqlite3GetTempReg(pParse);
  int reg2 = sqlite3GetTempReg(pParse);
  int regString = ++pParse->nMem;
  int arith = OP_Add;
  int addrGe;

  assert( op==OP_Ge || op==OP_Gt || op==OP_Le );
  assert( pOrderBy && pOrderBy->nExpr==1 );
  if( pOrderBy->a[0].sortFlags & KEYINFO_ORDER_DESC ){
    switch( op ){
      case OP_Ge: op = OP_Le; break;
      case OP_Gt: op = OP_Lt; break;
      default: assert( op==OP_Le ); op = OP_Ge; break;
    }
    arith = OP_Subtract;
  }


  windowReadPeerValues(p, csr1, reg1);
  windowReadPeerValues(p, csr2, reg2);

  VdbeModuleComment((v, "CodeRangeTest: if( R%d %s R%d %s R%d ) goto lbl",
      reg1, (arith==OP_Add ? "+" : "-"), regVal,
      ((op==OP_Ge) ? ">=" : (op==OP_Le) ? "<=" : (op==OP_Gt) ? ">" : "<"), reg2
  ));


  sqlite3VdbeAddOp4(v, OP_String8, 0, regString, 0, "", P4_STATIC);
  addrGe = sqlite3VdbeAddOp3(v, OP_Ge, regString, 0, reg1);
  VdbeCoverage(v);
  sqlite3VdbeAddOp3(v, arith, regVal, reg1, reg1);
  sqlite3VdbeJumpHere(v, addrGe);


  if( pOrderBy->a[0].sortFlags & KEYINFO_ORDER_BIGNULL ){

    int addr = sqlite3VdbeAddOp1(v, OP_NotNull, reg1); VdbeCoverage(v);
    switch( op ){
      case OP_Ge:
        sqlite3VdbeAddOp2(v, OP_Goto, 0, lbl);
        break;
      case OP_Gt:
        sqlite3VdbeAddOp2(v, OP_NotNull, reg2, lbl);
        VdbeCoverage(v);
        break;
      case OP_Le:
        sqlite3VdbeAddOp2(v, OP_IsNull, reg2, lbl);
        VdbeCoverage(v);
        break;
      default: assert( op==OP_Lt );  break;
    }
    sqlite3VdbeAddOp2(v, OP_Goto, 0, sqlite3VdbeCurrentAddr(v)+3);


    sqlite3VdbeJumpHere(v, addr);
    sqlite3VdbeAddOp2(v, OP_IsNull, reg2, lbl); VdbeCoverage(v);
    if( op==OP_Gt || op==OP_Ge ){
      sqlite3VdbeChangeP2(v, -1, sqlite3VdbeCurrentAddr(v)+1);
    }
  }


  sqlite3VdbeAddOp3(v, op, reg2, lbl, reg1); VdbeCoverage(v);
  sqlite3VdbeChangeP5(v, SQLITE_NULLEQ);

  assert( op==OP_Ge || op==OP_Gt || op==OP_Lt || op==OP_Le );
  testcase(op==OP_Ge); VdbeCoverageIf(v, op==OP_Ge);
  testcase(op==OP_Lt); VdbeCoverageIf(v, op==OP_Lt);
  testcase(op==OP_Le); VdbeCoverageIf(v, op==OP_Le);
  testcase(op==OP_Gt); VdbeCoverageIf(v, op==OP_Gt);
  sqlite3ReleaseTempReg(pParse, reg1);
  sqlite3ReleaseTempReg(pParse, reg2);

  VdbeModuleComment((v, "CodeRangeTest: end"));
}
