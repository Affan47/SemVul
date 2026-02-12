UnicodeString::doReplace(int32_t start,
             int32_t length,
             const UChar *srcChars,
             int32_t srcStart,
             int32_t srcLength)
{
  if(!isWritable()) {
    return *this;
  }

  int32_t oldLength = this->length();


  if((fUnion.fFields.fLengthAndFlags&kBufferIsReadonly) && srcLength == 0) {
    if(start == 0) {

      pinIndex(length);
      fUnion.fFields.fArray += length;
      fUnion.fFields.fCapacity -= length;
      setLength(oldLength - length);
      return *this;
    } else {
      pinIndex(start);
      if(length >= (oldLength - start)) {

        setLength(start);
        fUnion.fFields.fCapacity = start;
        return *this;
      }
    }
  }

  if(start == oldLength) {
    return doAppend(srcChars, srcStart, srcLength);
  }

  if(srcChars == 0) {
    srcLength = 0;
  } else {


    srcChars += srcStart;
    if (srcLength < 0) {

      srcLength = u_strlen(srcChars);
    }
  }


  pinIndices(start, length);


  int32_t newLength = oldLength - length;
  if(srcLength > (INT32_MAX - newLength)) {
    setToBogus();
    return *this;
  }
  newLength += srcLength;


  const UChar *oldArray = getArrayStart();
  if (isBufferWritable() &&
      oldArray < srcChars + srcLength &&
      srcChars < oldArray + oldLength) {

    UnicodeString copy(srcChars, srcLength);
    if (copy.isBogus()) {
      setToBogus();
      return *this;
    }
    return doReplace(start, length, copy.getArrayStart(), 0, srcLength);
  }


  UChar oldStackBuffer[US_STACKBUF_SIZE];
  if((fUnion.fFields.fLengthAndFlags&kUsingStackBuffer) && (newLength > US_STACKBUF_SIZE)) {


    u_memcpy(oldStackBuffer, oldArray, oldLength);
    oldArray = oldStackBuffer;
  }


  int32_t *bufferToDelete = 0;
  if(!cloneArrayIfNeeded(newLength, getGrowCapacity(newLength),
                         FALSE, &bufferToDelete)
  ) {
    return *this;
  }


  UChar *newArray = getArrayStart();
  if(newArray != oldArray) {

    us_arrayCopy(oldArray, 0, newArray, 0, start);
    us_arrayCopy(oldArray, start + length,
                 newArray, start + srcLength,
                 oldLength - (start + length));
  } else if(length != srcLength) {

    us_arrayCopy(oldArray, start + length,
                 newArray, start + srcLength,
                 oldLength - (start + length));
  }


  us_arrayCopy(srcChars, 0, newArray, start, srcLength);

  setLength(newLength);


  if (bufferToDelete) {
    uprv_free(bufferToDelete);
  }

  return *this;
}
