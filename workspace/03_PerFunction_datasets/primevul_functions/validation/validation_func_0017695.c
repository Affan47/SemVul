UnicodeString::padLeading(int32_t targetLength,
                          UChar padChar)
{
  int32_t oldLength = length();
  if(oldLength >= targetLength || !cloneArrayIfNeeded(targetLength)) {
    return FALSE;
  } else {

    UChar *array = getArrayStart();
    int32_t start = targetLength - oldLength;
    us_arrayCopy(array, 0, array, start, oldLength);


    while(--start >= 0) {
      array[start] = padChar;
    }
    setLength(targetLength);
    return TRUE;
  }
}
