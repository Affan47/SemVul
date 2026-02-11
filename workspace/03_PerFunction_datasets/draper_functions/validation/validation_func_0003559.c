doBitwiseOp (const MSBinaryVector & vect_, const unsigned char value_,
					    MSBinaryVector::BitwiseOp op_)
{
  unsigned int len = vect_.length();
  const unsigned char c = (value_ > 0) ? 1 : 0;

  MSVectorImpl *pImpl = vect_._pImpl->create (len, vect_.size());

  const unsigned char *pData1 = vect_.data();
  unsigned char *pData = ((Data *)pImpl->data())->elements();

  while (len--)
    (*op_)(*pData++, c, *pData1++);

  return MSBinaryVector (pImpl);
}
