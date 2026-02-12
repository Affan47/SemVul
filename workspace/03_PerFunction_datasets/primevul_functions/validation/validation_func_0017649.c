UnicodeString::doReplace( int32_t start,
              int32_t length,
              const UnicodeString& src,
              int32_t srcStart,
              int32_t srcLength)
{

  src.pinIndices(srcStart, srcLength);


  return doReplace(start, length, src.getArrayStart(), srcStart, srcLength);
}
