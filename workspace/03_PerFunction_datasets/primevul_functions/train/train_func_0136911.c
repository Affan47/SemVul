static void nodeGetCoord(
  Rtree *pRtree,
  RtreeNode *pNode,
  int iCell,
  int iCoord,
  RtreeCoord *pCoord
){
  readCoord(&pNode->zData[12 + pRtree->nBytesPerCell*iCell + 4*iCoord], pCoord);
}
