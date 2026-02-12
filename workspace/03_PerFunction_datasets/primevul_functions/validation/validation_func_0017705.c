UnicodeString::doAppend(const UnicodeString& src, int32_t srcStart, int32_t srcLength) {
  if(srcLength == 0) {
    return *this;
  }


  src.pinIndices(srcStart, srcLength);
  return doAppend(src.getArrayStart(), srcStart, srcLength);
}
