static int fts3IncrmergeLoad(
  Fts3Table *p,
  sqlite3_int64 iAbsLevel,
  int iIdx,
  const char *zKey,
  int nKey,
  IncrmergeWriter *pWriter
){
  int rc;
  sqlite3_stmt *pSelect = 0;

  rc = fts3SqlStmt(p, SQL_SELECT_SEGDIR, &pSelect, 0);
  if( rc==SQLITE_OK ){
    sqlite3_int64 iStart = 0;
    sqlite3_int64 iLeafEnd = 0;
    sqlite3_int64 iEnd = 0;
    const char *aRoot = 0;
    int nRoot = 0;
    int rc2;
    int bAppendable = 0;


    sqlite3_bind_int64(pSelect, 1, iAbsLevel+1);
    sqlite3_bind_int(pSelect, 2, iIdx);
    if( sqlite3_step(pSelect)==SQLITE_ROW ){
      iStart = sqlite3_column_int64(pSelect, 1);
      iLeafEnd = sqlite3_column_int64(pSelect, 2);
      fts3ReadEndBlockField(pSelect, 3, &iEnd, &pWriter->nLeafData);
      if( pWriter->nLeafData<0 ){
        pWriter->nLeafData = pWriter->nLeafData * -1;
      }
      pWriter->bNoLeafData = (pWriter->nLeafData==0);
      nRoot = sqlite3_column_bytes(pSelect, 4);
      aRoot = sqlite3_column_blob(pSelect, 4);
    }else{
      return sqlite3_reset(pSelect);
    }


    rc = fts3IsAppendable(p, iEnd, &bAppendable);


    if( rc==SQLITE_OK && bAppendable ){
      char *aLeaf = 0;
      int nLeaf = 0;

      rc = sqlite3Fts3ReadBlock(p, iLeafEnd, &aLeaf, &nLeaf, 0);
      if( rc==SQLITE_OK ){
        NodeReader reader;
        for(rc = nodeReaderInit(&reader, aLeaf, nLeaf);
            rc==SQLITE_OK && reader.aNode;
            rc = nodeReaderNext(&reader)
        ){
          assert( reader.aNode );
        }
        if( fts3TermCmp(zKey, nKey, reader.term.a, reader.term.n)<=0 ){
          bAppendable = 0;
        }
        nodeReaderRelease(&reader);
      }
      sqlite3_free(aLeaf);
    }

    if( rc==SQLITE_OK && bAppendable ){


      int i;
      int nHeight = (int)aRoot[0];
      NodeWriter *pNode;
      if( nHeight<1 || nHeight>FTS_MAX_APPENDABLE_HEIGHT ){
        sqlite3_reset(pSelect);
        return FTS_CORRUPT_VTAB;
      }

      pWriter->nLeafEst = (int)((iEnd - iStart) + 1)/FTS_MAX_APPENDABLE_HEIGHT;
      pWriter->iStart = iStart;
      pWriter->iEnd = iEnd;
      pWriter->iAbsLevel = iAbsLevel;
      pWriter->iIdx = iIdx;

      for(i=nHeight+1; i<FTS_MAX_APPENDABLE_HEIGHT; i++){
        pWriter->aNodeWriter[i].iBlock = pWriter->iStart + i*pWriter->nLeafEst;
      }

      pNode = &pWriter->aNodeWriter[nHeight];
      pNode->iBlock = pWriter->iStart + pWriter->nLeafEst*nHeight;
      blobGrowBuffer(&pNode->block,
          MAX(nRoot, p->nNodeSize)+FTS3_NODE_PADDING, &rc
      );
      if( rc==SQLITE_OK ){
        memcpy(pNode->block.a, aRoot, nRoot);
        pNode->block.n = nRoot;
        memset(&pNode->block.a[nRoot], 0, FTS3_NODE_PADDING);
      }

      for(i=nHeight; i>=0 && rc==SQLITE_OK; i--){
        NodeReader reader;
        pNode = &pWriter->aNodeWriter[i];

        if( pNode->block.a){
          rc = nodeReaderInit(&reader, pNode->block.a, pNode->block.n);
          while( reader.aNode && rc==SQLITE_OK ) rc = nodeReaderNext(&reader);
          blobGrowBuffer(&pNode->key, reader.term.n, &rc);
          if( rc==SQLITE_OK ){
            memcpy(pNode->key.a, reader.term.a, reader.term.n);
            pNode->key.n = reader.term.n;
            if( i>0 ){
              char *aBlock = 0;
              int nBlock = 0;
              pNode = &pWriter->aNodeWriter[i-1];
              pNode->iBlock = reader.iChild;
              rc = sqlite3Fts3ReadBlock(p, reader.iChild, &aBlock, &nBlock, 0);
              blobGrowBuffer(&pNode->block,
                  MAX(nBlock, p->nNodeSize)+FTS3_NODE_PADDING, &rc
              );
              if( rc==SQLITE_OK ){
                memcpy(pNode->block.a, aBlock, nBlock);
                pNode->block.n = nBlock;
                memset(&pNode->block.a[nBlock], 0, FTS3_NODE_PADDING);
              }
              sqlite3_free(aBlock);
            }
          }
        }
        nodeReaderRelease(&reader);
      }
    }

    rc2 = sqlite3_reset(pSelect);
    if( rc==SQLITE_OK ) rc = rc2;
  }

  return rc;
}
