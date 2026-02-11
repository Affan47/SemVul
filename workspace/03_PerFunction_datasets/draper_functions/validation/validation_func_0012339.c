getSplatValue() const {
  const char *Base = getRawDataValues().data();


  unsigned EltSize = getElementByteSize();
  for (unsigned i = 1, e = getNumElements(); i != e; ++i)
    if (memcmp(Base, Base+i*EltSize, EltSize))
      return nullptr;


  return getElementAsConstant(0);
}
