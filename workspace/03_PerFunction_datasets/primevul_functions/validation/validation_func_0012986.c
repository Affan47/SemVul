int sqlite3VdbeList(
  Vdbe *p
){
  int nRow;
  int nSub = 0;
  SubProgram **apSub = 0;
  Mem *pSub = 0;
  sqlite3 *db = p->db;
  int i;
  int rc = SQLITE_OK;
  Mem *pMem = &p->aMem[1];
  int bListSubprogs = (p->explain==1 || (db->flags & SQLITE_TriggerEQP)!=0);
  Op *pOp = 0;

  assert( p->explain );
  assert( p->magic==VDBE_MAGIC_RUN );
  assert( p->rc==SQLITE_OK || p->rc==SQLITE_BUSY || p->rc==SQLITE_NOMEM );


  releaseMemArray(pMem, 8);
  p->pResultSet = 0;

  if( p->rc==SQLITE_NOMEM ){


    sqlite3OomFault(db);
    return SQLITE_ERROR;
  }


  nRow = p->nOp;
  if( bListSubprogs ){


    assert( p->nMem>9 );
    pSub = &p->aMem[9];
    if( pSub->flags&MEM_Blob ){


      nSub = pSub->n/sizeof(Vdbe*);
      apSub = (SubProgram **)pSub->z;
    }
    for(i=0; i<nSub; i++){
      nRow += apSub[i]->nOp;
    }
  }

  while(1){
    i = p->pc++;
    if( i>=nRow ){
      p->rc = SQLITE_OK;
      rc = SQLITE_DONE;
      break;
    }
    if( i<p->nOp ){


      pOp = &p->aOp[i];
    }else{


      int j;
      i -= p->nOp;
      assert( apSub!=0 );
      assert( nSub>0 );
      for(j=0; i>=apSub[j]->nOp; j++){
        i -= apSub[j]->nOp;
        assert( i<apSub[j]->nOp || j+1<nSub );
      }
      pOp = &apSub[j]->aOp[i];
    }


    if( bListSubprogs && pOp->p4type==P4_SUBPROGRAM ){
      int nByte = (nSub+1)*sizeof(SubProgram*);
      int j;
      for(j=0; j<nSub; j++){
        if( apSub[j]==pOp->p4.pProgram ) break;
      }
      if( j==nSub ){
        p->rc = sqlite3VdbeMemGrow(pSub, nByte, nSub!=0);
        if( p->rc!=SQLITE_OK ){
          rc = SQLITE_ERROR;
          break;
        }
        apSub = (SubProgram **)pSub->z;
        apSub[nSub++] = pOp->p4.pProgram;
        pSub->flags |= MEM_Blob;
        pSub->n = nSub*sizeof(SubProgram*);
        nRow += pOp->p4.pProgram->nOp;
      }
    }
    if( p->explain<2 ) break;
    if( pOp->opcode==OP_Explain ) break;
    if( pOp->opcode==OP_Init && p->pc>1 ) break;
  }

  if( rc==SQLITE_OK ){
    if( db->u1.isInterrupted ){
      p->rc = SQLITE_INTERRUPT;
      rc = SQLITE_ERROR;
      sqlite3VdbeError(p, sqlite3ErrStr(p->rc));
    }else{
      char *zP4;
      if( p->explain==1 ){
        pMem->flags = MEM_Int;
        pMem->u.i = i;
        pMem++;

        pMem->flags = MEM_Static|MEM_Str|MEM_Term;
        pMem->z = (char*)sqlite3OpcodeName(pOp->opcode);
        assert( pMem->z!=0 );
        pMem->n = sqlite3Strlen30(pMem->z);
        pMem->enc = SQLITE_UTF8;
        pMem++;
      }

      pMem->flags = MEM_Int;
      pMem->u.i = pOp->p1;
      pMem++;

      pMem->flags = MEM_Int;
      pMem->u.i = pOp->p2;
      pMem++;

      pMem->flags = MEM_Int;
      pMem->u.i = pOp->p3;
      pMem++;

      if( sqlite3VdbeMemClearAndResize(pMem, 100) ){
        assert( p->db->mallocFailed );
        return SQLITE_ERROR;
      }
      pMem->flags = MEM_Str|MEM_Term;
      zP4 = displayP4(pOp, pMem->z, pMem->szMalloc);
      if( zP4!=pMem->z ){
        pMem->n = 0;
        sqlite3VdbeMemSetStr(pMem, zP4, -1, SQLITE_UTF8, 0);
      }else{
        assert( pMem->z!=0 );
        pMem->n = sqlite3Strlen30(pMem->z);
        pMem->enc = SQLITE_UTF8;
      }
      pMem++;

      if( p->explain==1 ){
        if( sqlite3VdbeMemClearAndResize(pMem, 4) ){
          assert( p->db->mallocFailed );
          return SQLITE_ERROR;
        }
        pMem->flags = MEM_Str|MEM_Term;
        pMem->n = 2;
        sqlite3_snprintf(3, pMem->z, "%.2x", pOp->p5);
        pMem->enc = SQLITE_UTF8;
        pMem++;

#ifdef SQLITE_ENABLE_EXPLAIN_COMMENTS
        if( sqlite3VdbeMemClearAndResize(pMem, 500) ){
          assert( p->db->mallocFailed );
          return SQLITE_ERROR;
        }
        pMem->flags = MEM_Str|MEM_Term;
        pMem->n = displayComment(pOp, zP4, pMem->z, 500);
        pMem->enc = SQLITE_UTF8;
#else
        pMem->flags = MEM_Null;
#endif
      }

      p->nResColumn = 8 - 4*(p->explain-1);
      p->pResultSet = &p->aMem[1];
      p->rc = SQLITE_OK;
      rc = SQLITE_ROW;
    }
  }
  return rc;
}
