UnicodeString::setTo(UBool isTerminated,
                     ConstChar16Ptr textPtr,
                     int32_t textLength)
{
  if(fUnion.fFields.fLengthAndFlags & kOpenGetBuffer) {

    return *this;
  }

  const UChar *text = textPtr;
  if(text == NULL) {

    releaseArray();
    setToEmpty();
    return *this;
  }

  if( textLength < -1 ||
      (textLength == -1 && !isTerminated) ||
      (textLength >= 0 && isTerminated && text[textLength] != 0)
  ) {
    setToBogus();
    return *this;
  }

  releaseArray();

  if(textLength == -1) {

    textLength = u_strlen(text);
  }
  fUnion.fFields.fLengthAndFlags = kReadonlyAlias;
  setArray((UChar *)text, textLength, isTerminated ? textLength + 1 : textLength);
  return *this;
}
