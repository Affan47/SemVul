static int tableAndColumnIndex(
  SrcList *pSrc,
  int N,
  const char *zCol,
  int *piTab,
  int *piCol,
  int bIgnoreHidden
){
  int i;
  int iCol;

  assert( (piTab==0)==(piCol==0) );
  for(i=0; i<N; i++){
    iCol = columnIndex(pSrc->a[i].pTab, zCol);
    if( iCol>=0
     && (bIgnoreHidden==0 || IsHiddenColumn(&pSrc->a[i].pTab->aCol[iCol])==0)
    ){
      if( piTab ){
        *piTab = i;
        *piCol = iCol;
      }
      return 1;
    }
  }
  return 0;
}
