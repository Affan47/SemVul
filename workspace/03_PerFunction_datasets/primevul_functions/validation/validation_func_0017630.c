UnicodeString::doEquals(const UnicodeString &text, int32_t len) const {


  return uprv_memcmp(getArrayStart(), text.getArrayStart(), len * U_SIZEOF_UCHAR) == 0;
}
