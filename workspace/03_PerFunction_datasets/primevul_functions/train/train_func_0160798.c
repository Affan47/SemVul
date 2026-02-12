ufmt_getUChars(UFormattable *fmt, int32_t *len, UErrorCode *status) {
  Formattable *obj = Formattable::fromUFormattable(fmt);


  if( obj->getType() != Formattable::kString ) {
    if( U_SUCCESS(*status) ){
      *status = U_INVALID_FORMAT_ERROR;
    }
    return NULL;
  }


  UnicodeString &str = obj->getString(*status);
  if( U_SUCCESS(*status) && len != NULL ) {
    *len = str.length();
  }
  return str.getTerminatedBuffer();
}
