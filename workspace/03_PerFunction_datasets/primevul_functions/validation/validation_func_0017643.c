UnicodeString::getTerminatedBuffer() {
  if(!isWritable()) {
    return nullptr;
  }
  UChar *array = getArrayStart();
  int32_t len = length();
  if(len < getCapacity()) {
    if(fUnion.fFields.fLengthAndFlags & kBufferIsReadonly) {


      if(array[len] == 0) {
        return array;
      }
    } else if(((fUnion.fFields.fLengthAndFlags & kRefCounted) == 0 || refCount() == 1)) {


      array[len] = 0;
      return array;
    }
  }
  if(len<INT32_MAX && cloneArrayIfNeeded(len+1)) {
    array = getArrayStart();
    array[len] = 0;
    return array;
  } else {
    return nullptr;
  }
}
