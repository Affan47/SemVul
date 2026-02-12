static inline int skip(struct SISTREAM *s, uint32_t size) {
  long seekto;
  cli_dbgmsg("SIS: skipping %x\n", size);
  if (s->sleft>=size) s->sleft-=size;
  else {
    seekto = size - s->sleft;
    if (seekto<0)
      return 1;
    fseek(s->f, seekto, SEEK_CUR);

    s->sleft = s->smax = 0;
  }
  return 0;
}
