appendRows(const int numrows,
			    const CoinPackedVectorBase * const * rows)
{
  if (colOrdered_) {

    if (numrows == 0)
      return;

    int i;
    int maxDim=-1;
    for (i = numrows - 1; i >= 0; --i) {
      const int vecsize = rows[i]->getNumElements();
      const int* vecind = rows[i]->getIndices();
      for (int j = vecsize - 1; j >= 0; --j)
	maxDim = CoinMax(maxDim,vecind[j]);
    }
    maxDim++;
    if (maxDim>majorDim_) {
      setDimensions(minorDim_,maxDim);


    }
    appendMinorVectors(numrows, rows);
  } else {
    appendMajorVectors(numrows, rows);
  }
}
