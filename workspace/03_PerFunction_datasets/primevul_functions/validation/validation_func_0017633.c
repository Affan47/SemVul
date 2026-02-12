UnicodeString::lastIndexOf(const UChar *srcChars,
               int32_t srcStart,
               int32_t srcLength,
               int32_t start,
               int32_t length) const
{
  if(isBogus() || srcChars == 0 || srcStart < 0 || srcLength == 0) {
    return -1;
  }


  if(srcLength < 0 && srcChars[srcStart] == 0) {
    return -1;
  }


  pinIndices(start, length);


  const UChar *array = getArrayStart();
  const UChar *match = u_strFindLast(array + start, length, srcChars + srcStart, srcLength);
  if(match == NULL) {
    return -1;
  } else {
    return (int32_t)(match - array);
  }
}
