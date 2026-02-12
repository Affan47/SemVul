UnicodeString::tempSubString(int32_t start, int32_t len) const {
  pinIndices(start, len);
  const UChar *array = getBuffer();
  if(array==NULL) {
    array=fUnion.fStackFields.fBuffer;
    len=-2;
  }
  return UnicodeString(FALSE, array + start, len);
}
