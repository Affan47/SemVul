UnicodeString::doLastIndexOf(UChar32 c,
                             int32_t start,
                             int32_t length) const {

  pinIndices(start, length);


  const UChar *array = getArrayStart();
  const UChar *match = u_memrchr32(array + start, c, length);
  if(match == NULL) {
    return -1;
  } else {
    return (int32_t)(match - array);
  }
}
