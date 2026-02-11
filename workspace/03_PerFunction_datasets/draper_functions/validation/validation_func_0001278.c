ApplyFunction(const std::vector<uint64_t>& vLOD,
                                     bool (*brickFunc)(void* pData,
                                                    const UINT64VECTOR3& vBrickSize,
                                                    const UINT64VECTOR3& vBrickOffset,
                                                    void* pUserContext),
                                     void* pUserContext,
                                     uint64_t iOverlap,
                                     AbstrDebugOut* pDebugOut) const {

#ifdef _DEBUG
  for (size_t i = 0;i<ulBrickSize.size();i++) {
    assert(iOverlap <= ulBrickOverlap[i]/2);

  }
#endif

  const vector<uint64_t> vBrickCount = GetBrickCount(vLOD);
  vector<uint64_t> vCoords(vBrickCount.size());

  std::vector<unsigned char> pData;


  vector<uint64_t> vPrefixProd;
  vPrefixProd.push_back(1);
  uint64_t iBrickCount = vBrickCount[0];
  vector<uint64_t> vLODDomSize = GetLODDomainSize(vLOD);
  for (size_t i = 1;i<vLODDomSize.size();i++) {
    vPrefixProd.push_back(*(vPrefixProd.end()-1) * vLODDomSize[i-1]);
    iBrickCount *= vBrickCount[i];
  }
  uint64_t iElementSize = ComputeElementSize();
  uint64_t iBrickCounter = 0;

  TraverseBricksToApplyFunction(iBrickCounter, iBrickCount, vLOD, vBrickCount, vCoords,
                                vBrickCount.size()-1, pData,
                                iElementSize/8, vPrefixProd, pDebugOut, brickFunc,
                                pUserContext, iOverlap );

  return true;
}
