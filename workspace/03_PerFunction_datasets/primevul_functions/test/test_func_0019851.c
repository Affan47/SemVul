static inline void seeknext(struct SISTREAM *s) {
  fseek(s->f, s->fnext[s->level], SEEK_SET);

  s->sleft = s->smax = 0;
}
