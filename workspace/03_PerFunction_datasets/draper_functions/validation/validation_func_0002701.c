ZopfliMaxCachedSublen(const ZopfliLongestMatchCache* lmc,
                               size_t pos, size_t length) {
  unsigned char* cache;
#if ZOPFLI_CACHE_LENGTH == 0
  return 0;
#endif
  cache = &lmc->sublen[ZOPFLI_CACHE_LENGTH * pos * 3];
  (void)length;
  if (cache[1] == 0 && cache[2] == 0) return 0;
  return cache[(ZOPFLI_CACHE_LENGTH - 1) * 3] + 3;
}
