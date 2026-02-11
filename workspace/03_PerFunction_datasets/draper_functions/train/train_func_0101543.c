cache_readdata(cache_back * cache, const char *str1, const char *str2,
                   char **inbuff, int *inlen) {
#if HTS_FAST_CACHE
  if (cache->hashtable) {
    char BIGSTK buff[HTS_URLMAXSIZE * 4];
    intptr_t pos;

    strcpybuff(buff, str1);
    strcatbuff(buff, str2);
    if (inthash_read(cache->hashtable, buff, &pos)) {
      if (fseek(cache->olddat, (long) ((pos > 0) ? pos : (-pos)), SEEK_SET) ==
          0) {
        INTsys len;

        cache_rint(cache->olddat, &len);
        if (len > 0) {
          char *mem_buff = (char *) malloct(len + 4);

          if (mem_buff) {
            if (fread(mem_buff, 1, len, cache->olddat) == len) {
              *inbuff = mem_buff;
              *inlen = len;
              return 1;
            } else
              freet(mem_buff);
          }
        }
      }
    }
  }
#endif
  *inbuff = NULL;
  *inlen = 0;
  return 0;
}
