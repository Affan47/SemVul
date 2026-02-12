UnicodeString::hasMoreChar32Than(int32_t start, int32_t length, int32_t number) const {
  pinIndices(start, length);

  return u_strHasMoreChar32Than(getArrayStart()+start, length, number);
}
