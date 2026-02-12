UnicodeString::~UnicodeString()
{
#ifdef UNISTR_COUNT_FINAL_STRING_LENGTHS


  if((fUnion.fFields.fLengthAndFlags&(kOpenGetBuffer|kReadonlyAlias|kWritableAlias)) == 0) {
    if(hasShortLength()) {
      umtx_atomic_inc(finalLengthCounts + getShortLength());
    } else {
      umtx_atomic_inc(&beyondCount);
    }
  }
#endif

  releaseArray();
}
