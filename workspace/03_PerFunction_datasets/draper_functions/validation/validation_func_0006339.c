appendMajorVectors(const int numvecs,
				    const CoinPackedVectorBase * const * vecs)
{
  int i;
  CoinBigIndex nz = 0;
  for (i = 0; i < numvecs; ++i)
    nz += CoinLengthWithExtra(vecs[i]->getNumElements(), extraGap_);
  reserve(majorDim_ + numvecs, getLastStart() + nz);
  for (i = 0; i < numvecs; ++i)
    appendMajorVector(*vecs[i]);
}
