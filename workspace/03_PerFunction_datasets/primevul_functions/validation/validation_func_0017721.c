UnicodeString::copyFrom(const UnicodeString &src, UBool fastCopy) {

  if(this == &src) {
    return *this;
  }


  if(src.isBogus()) {
    setToBogus();
    return *this;
  }


  releaseArray();

  if(src.isEmpty()) {

    setToEmpty();
    return *this;
  }


  fUnion.fFields.fLengthAndFlags = src.fUnion.fFields.fLengthAndFlags;
  switch(src.fUnion.fFields.fLengthAndFlags & kAllStorageFlags) {
  case kShortString:

    uprv_memcpy(fUnion.fStackFields.fBuffer, src.fUnion.fStackFields.fBuffer,
                getShortLength() * U_SIZEOF_UCHAR);
    break;
  case kLongString:


    ((UnicodeString &)src).addRef();

    fUnion.fFields.fArray = src.fUnion.fFields.fArray;
    fUnion.fFields.fCapacity = src.fUnion.fFields.fCapacity;
    if(!hasShortLength()) {
      fUnion.fFields.fLength = src.fUnion.fFields.fLength;
    }
    break;
  case kReadonlyAlias:
    if(fastCopy) {


      fUnion.fFields.fArray = src.fUnion.fFields.fArray;
      fUnion.fFields.fCapacity = src.fUnion.fFields.fCapacity;
      if(!hasShortLength()) {
        fUnion.fFields.fLength = src.fUnion.fFields.fLength;
      }
      break;
    }


    U_FALLTHROUGH;
  case kWritableAlias: {

    int32_t srcLength = src.length();
    if(allocate(srcLength)) {
      u_memcpy(getArrayStart(), src.getArrayStart(), srcLength);
      setLength(srcLength);
      break;
    }

    U_FALLTHROUGH;
  }
  default:


    fUnion.fFields.fLengthAndFlags = kIsBogus;
    fUnion.fFields.fArray = 0;
    fUnion.fFields.fCapacity = 0;
    break;
  }

  return *this;
}
