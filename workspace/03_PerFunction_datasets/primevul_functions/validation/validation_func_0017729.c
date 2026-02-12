UnicodeString::allocate(int32_t capacity) {
  if(capacity <= US_STACKBUF_SIZE) {
    fUnion.fFields.fLengthAndFlags = kShortString;
    return TRUE;
  }
  if(capacity <= kMaxCapacity) {
    ++capacity;


    size_t numBytes = sizeof(int32_t) + (size_t)capacity * U_SIZEOF_UCHAR;

    numBytes = (numBytes + 15) & ~15;
    int32_t *array = (int32_t *) uprv_malloc(numBytes);
    if(array != NULL) {

      *array++ = 1;
      numBytes -= sizeof(int32_t);


      fUnion.fFields.fArray = (UChar *)array;
      fUnion.fFields.fCapacity = (int32_t)(numBytes / U_SIZEOF_UCHAR);
      fUnion.fFields.fLengthAndFlags = kLongString;
      return TRUE;
    }
  }
  fUnion.fFields.fLengthAndFlags = kIsBogus;
  fUnion.fFields.fArray = 0;
  fUnion.fFields.fCapacity = 0;
  return FALSE;
}
