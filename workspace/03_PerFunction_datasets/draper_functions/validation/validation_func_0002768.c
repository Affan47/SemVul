analyzeDatabase(Parse *pParse, int iDb){
  sqlite3 *db = pParse->db;
  Schema *pSchema = db->aDb[iDb].pSchema;
  HashElem *k;
  int iStatCur;
  int iMem;

  sqlite3BeginWriteOperation(pParse, 0, iDb);
  iStatCur = pParse->nTab++;
  openStatTable(pParse, iDb, iStatCur, 0);
  iMem = pParse->nMem;
  for(k=sqliteHashFirst(&pSchema->tblHash); k; k=sqliteHashNext(k)){
    Table *pTab = (Table*)sqliteHashData(k);
    analyzeOneTable(pParse, pTab, iStatCur, iMem);
  }
  loadAnalysis(pParse, iDb);
}
