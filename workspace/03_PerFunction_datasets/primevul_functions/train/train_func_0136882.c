static i64 nodeGetRowid(
  Rtree *pRtree,
  RtreeNode *pNode,
  int iCell
){
  assert( iCell<NCELL(pNode) );
  return readInt64(&pNode->zData[4 + pRtree->nBytesPerCell*iCell]);
}
