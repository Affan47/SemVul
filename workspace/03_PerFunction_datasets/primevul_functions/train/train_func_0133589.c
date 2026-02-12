bool ByteVector::containsAt(const ByteVector &pattern, uint offset, uint patternOffset, uint patternLength) const
{
  if(pattern.size() < patternLength)
    patternLength = pattern.size();


  if(patternLength > size() || offset >= size() || patternOffset >= pattern.size() || patternLength == 0)
    return false;


  for(uint i = 0; i < patternLength - patternOffset; i++) {
    if(at(i + offset) != pattern[i + patternOffset])
      return false;
  }

  return true;
}
