Hcr_State_BODY_ONLY(HANDLE_FDK_BITSTREAM bs, void *ptr)
{
  H_HCR_INFO pHcr = (H_HCR_INFO)ptr;
  UINT        *pSegmentBitfield;
  UINT        *pCodewordBitfield;
  UINT         segmentOffset;
  FIXP_DBL    *pResultBase;
  UINT        *iNode;
  USHORT      *iResultPointer;
  UINT         codewordOffset;
  UINT         branchNode;
  UINT         branchValue;
  UINT         iQSC;
  UINT         treeNode;
  UCHAR        carryBit;
  USHORT      *pLeftStartOfSegment;
  USHORT      *pRightStartOfSegment;
  SCHAR       *pRemainingBitsInSegment;
  UCHAR        readDirection;
  UCHAR       *pCodebook;
  UCHAR        dimCntr;
  const UINT  *pCurrentTree;
  const UCHAR *pCbDimension;
  const SCHAR *pQuantVal;
  const SCHAR *pQuantValBase;

  pRemainingBitsInSegment = pHcr->segmentInfo.pRemainingBitsInSegment;
  pLeftStartOfSegment     = pHcr->segmentInfo.pLeftStartOfSegment;
  pRightStartOfSegment    = pHcr->segmentInfo.pRightStartOfSegment;
  readDirection           = pHcr->segmentInfo.readDirection;
  pSegmentBitfield        = pHcr->segmentInfo.pSegmentBitfield;
  pCodewordBitfield       = pHcr->segmentInfo.pCodewordBitfield;
  segmentOffset           = pHcr->segmentInfo.segmentOffset;

  pCodebook               = pHcr->nonPcwSideinfo.pCodebook;
  iNode                   = pHcr->nonPcwSideinfo.iNode;
  pResultBase             = pHcr->nonPcwSideinfo.pResultBase;
  iResultPointer          = pHcr->nonPcwSideinfo.iResultPointer;
  codewordOffset          = pHcr->nonPcwSideinfo.codewordOffset;

  pCbDimension            = pHcr->tableInfo.pCbDimension;

  treeNode                = iNode[codewordOffset];
  pCurrentTree            = aHuffTable[pCodebook[codewordOffset]];


  for ( ; pRemainingBitsInSegment[segmentOffset] > 0 ; pRemainingBitsInSegment[segmentOffset] -= 1 ) {

    carryBit = HcrGetABitFromBitstream( bs,
                                       &pLeftStartOfSegment[segmentOffset],
                                       &pRightStartOfSegment[segmentOffset],
                                        readDirection);

    CarryBitToBranchValue(carryBit,
                          treeNode,
                          &branchValue,
                          &branchNode);


    if ((branchNode & TEST_BIT_10) == TEST_BIT_10) {
      pQuantValBase = aQuantTable[pCodebook[codewordOffset]];
      pQuantVal = pQuantValBase + branchValue;

      iQSC = iResultPointer[codewordOffset];

      for ( dimCntr = pCbDimension[pCodebook[codewordOffset]]; dimCntr != 0; dimCntr-- ) {
        pResultBase[iQSC++] = (FIXP_DBL)*pQuantVal++;
      }

      ClearBitFromBitfield(&(pHcr->nonPcwSideinfo.pState),
                           segmentOffset,
                           pCodewordBitfield);
      pRemainingBitsInSegment[segmentOffset] -= 1;
      break;
    }
    else {
      treeNode = *(pCurrentTree + branchValue);
    }
  }
  iNode[codewordOffset] = treeNode;

  if ( pRemainingBitsInSegment[segmentOffset] <= 0 ) {
    ClearBitFromBitfield(&(pHcr->nonPcwSideinfo.pState),
                         segmentOffset,
                         pSegmentBitfield);

#if STATE_MACHINE_ERROR_CHECK
    if ( pRemainingBitsInSegment[segmentOffset] < 0 ) {
      pHcr->decInOut.errorLog |= STATE_ERROR_BODY_ONLY;
      return                                 BODY_ONLY;
    }
#endif
  }

  return STOP_THIS_STATE;
}
