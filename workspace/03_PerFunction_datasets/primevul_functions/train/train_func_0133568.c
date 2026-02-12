ByteVector &ByteVector::replace(const ByteVector &pattern, const ByteVector &with)
{
  if(pattern.size() == 0 || pattern.size() > size())
    return *this;

  const uint withSize = with.size();
  const uint patternSize = pattern.size();
  int offset = 0;

  if(withSize == patternSize) {

    detach();
    offset = find(pattern);
    while(offset >= 0) {
      ::memcpy(data() + offset, with.data(), withSize);
      offset = find(pattern, offset + withSize);
    }
    return *this;
  }


  uint newSize = 0;
  for(;;) {
    int next = find(pattern, offset);
    if(next < 0) {
      if(offset == 0)

        return *this;
      newSize += size() - offset;
      break;
    }
    newSize += (next - offset) + withSize;
    offset = next + patternSize;
  }


  ByteVectorPrivate *newData = new ByteVectorPrivate(newSize, 0);
  char *target = DATA(newData);
  const char *source = data();


  offset = 0;
  for(;;) {
    int next = find(pattern, offset);
    if(next < 0) {
      ::memcpy(target, source + offset, size() - offset);
      break;
    }
    int chunkSize = next - offset;
    ::memcpy(target, source + offset, chunkSize);
    target += chunkSize;
    ::memcpy(target, with.data(), withSize);
    target += withSize;
    offset += chunkSize + patternSize;
  }


  if(d->deref())
    delete d;

  d = newData;

  return *this;
}
