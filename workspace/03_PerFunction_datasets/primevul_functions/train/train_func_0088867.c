inline uint32_t clzll(uint64_t x) {
  unsigned long r = 0;
# ifdef _WIN64
  _BitScanReverse64(&r, x);
# else

  if (_BitScanReverse(&r, static_cast<uint32_t>(x >> 32)))
    return 63 - (r + 32);


  _BitScanReverse(&r, static_cast<uint32_t>(x));
# endif

  assert(x != 0);


# pragma warning(suppress: 6102)
  return 63 - r;
}
