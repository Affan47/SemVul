UnicodeString &UnicodeString::operator=(UnicodeString &&src) U_NOEXCEPT {


  releaseArray();
  copyFieldsFrom(src, TRUE);
  return *this;
}
