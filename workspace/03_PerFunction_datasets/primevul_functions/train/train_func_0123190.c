int32 GetIntSize(int64 value) {


  const uint64 v = (value < 0) ? value ^ -1LL : value;
  return GetUIntSize(2 * v);
}
