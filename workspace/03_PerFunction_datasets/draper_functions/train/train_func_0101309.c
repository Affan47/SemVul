getBuffer(int32_t minCapacity) {
  if(minCapacity>=-1 && cloneArrayIfNeeded(minCapacity)) {
    fFlags|=kOpenGetBuffer;
    fShortLength=0;
    return getArrayStart();
  } else {
    return 0;
  }
}
