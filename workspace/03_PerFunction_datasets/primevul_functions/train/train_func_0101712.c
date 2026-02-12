static int fts3DoclistCountDocids(char *aList, int nList){
  int nDoc = 0;
  if( aList ){
    char *aEnd = &aList[nList];
    char *p = aList;
    while( p<aEnd ){
      nDoc++;
      while( (*p++)&0x80 );
      fts3PoslistCopy(0, &p);
    }
  }

  return nDoc;
}
