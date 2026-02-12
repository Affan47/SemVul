static void rtreeNonleafConstraint(
  RtreeConstraint *p,
  int eInt,
  u8 *pCellData,
  int *peWithin
){
  sqlite3_rtree_dbl val;


  pCellData += 8 + 4*(p->iCoord&0xfe);

  assert(p->op==RTREE_LE || p->op==RTREE_LT || p->op==RTREE_GE
      || p->op==RTREE_GT || p->op==RTREE_EQ );
  assert( ((((char*)pCellData) - (char*)0)&3)==0 );
  switch( p->op ){
    case RTREE_LE:
    case RTREE_LT:
    case RTREE_EQ:
      RTREE_DECODE_COORD(eInt, pCellData, val);

      if( p->u.rValue>=val ) return;
      if( p->op!=RTREE_EQ ) break;


    default:
      pCellData += 4;
      RTREE_DECODE_COORD(eInt, pCellData, val);

      if( p->u.rValue<=val ) return;
  }
  *peWithin = NOT_WITHIN;
}
