inline uint32_t clz(uint32_t x) {
  unsigned long r = 0;
  _BitScanReverse(&r, x);

  assert(x != 0);


# pragma warning(suppress: 6102)
  return 31 - r;
}
