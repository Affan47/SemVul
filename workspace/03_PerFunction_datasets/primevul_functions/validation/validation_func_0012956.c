void sqlite3VdbeMakeReady(
  Vdbe *p,
  Parse *pParse
){
  sqlite3 *db;
  int nVar;
  int nMem;
  int nCursor;
  int nArg;
  int n;
  struct ReusableSpace x;

  assert( p!=0 );
  assert( p->nOp>0 );
  assert( pParse!=0 );
  assert( p->magic==VDBE_MAGIC_INIT );
  assert( pParse==p->pParse );
  db = p->db;
  assert( db->mallocFailed==0 );
  nVar = pParse->nVar;
  nMem = pParse->nMem;
  nCursor = pParse->nTab;
  nArg = pParse->nMaxArg;


  nMem += nCursor;
  if( nCursor==0 && nMem>0 ) nMem++;


  n = ROUND8(sizeof(Op)*p->nOp);
  x.pSpace = &((u8*)p->aOp)[n];
  assert( EIGHT_BYTE_ALIGNMENT(x.pSpace) );
  x.nFree = ROUNDDOWN8(pParse->szOpAlloc - n);
  assert( x.nFree>=0 );
  assert( EIGHT_BYTE_ALIGNMENT(&x.pSpace[x.nFree]) );

  resolveP2Values(p, &nArg);
  p->usesStmtJournal = (u8)(pParse->isMultiWrite && pParse->mayAbort);
  if( pParse->explain ){
    static const char * const azColName[] = {
       "addr", "opcode", "p1", "p2", "p3", "p4", "p5", "comment",
       "id", "parent", "notused", "detail"
    };
    int iFirst, mx, i;
    if( nMem<10 ) nMem = 10;
    if( pParse->explain==2 ){
      sqlite3VdbeSetNumCols(p, 4);
      iFirst = 8;
      mx = 12;
    }else{
      sqlite3VdbeSetNumCols(p, 8);
      iFirst = 0;
      mx = 8;
    }
    for(i=iFirst; i<mx; i++){
      sqlite3VdbeSetColName(p, i-iFirst, COLNAME_NAME,
                            azColName[i], SQLITE_STATIC);
    }
  }
  p->expired = 0;


  x.nNeeded = 0;
  p->aMem = allocSpace(&x, 0, nMem*sizeof(Mem));
  p->aVar = allocSpace(&x, 0, nVar*sizeof(Mem));
  p->apArg = allocSpace(&x, 0, nArg*sizeof(Mem*));
  p->apCsr = allocSpace(&x, 0, nCursor*sizeof(VdbeCursor*));
#ifdef SQLITE_ENABLE_STMT_SCANSTATUS
  p->anExec = allocSpace(&x, 0, p->nOp*sizeof(i64));
#endif
  if( x.nNeeded ){
    x.pSpace = p->pFree = sqlite3DbMallocRawNN(db, x.nNeeded);
    x.nFree = x.nNeeded;
    if( !db->mallocFailed ){
      p->aMem = allocSpace(&x, p->aMem, nMem*sizeof(Mem));
      p->aVar = allocSpace(&x, p->aVar, nVar*sizeof(Mem));
      p->apArg = allocSpace(&x, p->apArg, nArg*sizeof(Mem*));
      p->apCsr = allocSpace(&x, p->apCsr, nCursor*sizeof(VdbeCursor*));
#ifdef SQLITE_ENABLE_STMT_SCANSTATUS
      p->anExec = allocSpace(&x, p->anExec, p->nOp*sizeof(i64));
#endif
    }
  }

  p->pVList = pParse->pVList;
  pParse->pVList =  0;
  p->explain = pParse->explain;
  if( db->mallocFailed ){
    p->nVar = 0;
    p->nCursor = 0;
    p->nMem = 0;
  }else{
    p->nCursor = nCursor;
    p->nVar = (ynVar)nVar;
    initMemArray(p->aVar, nVar, db, MEM_Null);
    p->nMem = nMem;
    initMemArray(p->aMem, nMem, db, MEM_Undefined);
    memset(p->apCsr, 0, nCursor*sizeof(VdbeCursor*));
#ifdef SQLITE_ENABLE_STMT_SCANSTATUS
    memset(p->anExec, 0, p->nOp*sizeof(i64));
#endif
  }
  sqlite3VdbeRewind(p);
}
