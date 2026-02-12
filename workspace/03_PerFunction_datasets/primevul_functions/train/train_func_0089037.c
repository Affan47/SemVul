inline unsigned count_digits(uint64_t n) {


  int t = (64 - FMT_BUILTIN_CLZLL(n | 1)) * 1233 >> 12;
  return to_unsigned(t) - (n < Data::POWERS_OF_10_64[t]) + 1;
}
