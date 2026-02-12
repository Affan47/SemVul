UnicodeString::cloneArrayIfNeeded(int32_t newCapacity,
                                  int32_t growCapacity,
                                  UBool doCopyArray,
                                  int32_t **pBufferToDelete,
                                  UBool forceClone) {


  if(newCapacity == -1) {
    newCapacity = getCapacity();
  }


  if(!isWritable()) {
    return FALSE;
  }


  if(forceClone ||
     fUnion.fFields.fLengthAndFlags & kBufferIsReadonly ||
     (fUnion.fFields.fLengthAndFlags & kRefCounted && refCount() > 1) ||
     newCapacity > getCapacity()
  ) {

    if(growCapacity < 0) {
      growCapacity = newCapacity;
    } else if(newCapacity <= US_STACKBUF_SIZE && growCapacity > US_STACKBUF_SIZE) {
      growCapacity = US_STACKBUF_SIZE;
    }


    UChar oldStackBuffer[US_STACKBUF_SIZE];
    UChar *oldArray;
    int32_t oldLength = length();
    int16_t flags = fUnion.fFields.fLengthAndFlags;

    if(flags&kUsingStackBuffer) {
      U_ASSERT(!(flags&kRefCounted));
      if(doCopyArray && growCapacity > US_STACKBUF_SIZE) {


        us_arrayCopy(fUnion.fStackFields.fBuffer, 0, oldStackBuffer, 0, oldLength);
        oldArray = oldStackBuffer;
      } else {
        oldArray = NULL;
      }
    } else {
      oldArray = fUnion.fFields.fArray;
      U_ASSERT(oldArray!=NULL);
    }


    if(allocate(growCapacity) ||
       (newCapacity < growCapacity && allocate(newCapacity))
    ) {
      if(doCopyArray) {


        int32_t minLength = oldLength;
        newCapacity = getCapacity();
        if(newCapacity < minLength) {
          minLength = newCapacity;
        }
        if(oldArray != NULL) {
          us_arrayCopy(oldArray, 0, getArrayStart(), 0, minLength);
        }
        setLength(minLength);
      } else {
        setZeroLength();
      }


      if(flags & kRefCounted) {

        u_atomic_int32_t *pRefCount = ((u_atomic_int32_t *)oldArray - 1);
        if(umtx_atomic_dec(pRefCount) == 0) {
          if(pBufferToDelete == 0) {


            uprv_free((void *)pRefCount);
          } else {

            *pBufferToDelete = (int32_t *)pRefCount;
          }
        }
      }
    } else {


      if(!(flags&kUsingStackBuffer)) {
        fUnion.fFields.fArray = oldArray;
      }
      fUnion.fFields.fLengthAndFlags = flags;
      setToBogus();
      return FALSE;
    }
  }
  return TRUE;
}
