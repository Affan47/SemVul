ComputeElementSize() const {

  uint64_t uiBitsPerElement = 0;
  for (size_t i = 0;i<ulElementDimension;i++)
    for (size_t j = 0;j<ulElementDimensionSize[i];j++)
      uiBitsPerElement += ulElementBitSize[i][j];
  return uiBitsPerElement;
}
