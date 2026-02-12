UnicodeString::countChar32(int32_t start, int32_t length) const {
  pinIndices(start, length);

  return u_countChar32(getArrayStart()+start, length);
}
