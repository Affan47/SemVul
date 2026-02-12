UnicodeString::doReverse(int32_t start, int32_t length) {
  if(length <= 1 || !cloneArrayIfNeeded()) {
    return *this;
  }


  pinIndices(start, length);
  if(length <= 1) {
    return *this;
  }

  UChar *left = getArrayStart() + start;
  UChar *right = left + length - 1;
  UChar swap;
  UBool hasSupplementary = FALSE;


  do {
    hasSupplementary |= (UBool)U16_IS_LEAD(swap = *left);
    hasSupplementary |= (UBool)U16_IS_LEAD(*left++ = *right);
    *right-- = swap;
  } while(left < right);


  hasSupplementary |= (UBool)U16_IS_LEAD(*left);


  if(hasSupplementary) {
    UChar swap2;

    left = getArrayStart() + start;
    right = left + length - 1;
    while(left < right) {
      if(U16_IS_TRAIL(swap = *left) && U16_IS_LEAD(swap2 = *(left + 1))) {
        *left++ = swap2;
        *left++ = swap;
      } else {
        ++left;
      }
    }
  }

  return *this;
}
