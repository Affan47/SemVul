GC_build_fl2(struct hblk *h, ptr_t ofl)
  {
    word * p = (word *)(h -> hb_body);
    word * lim = (word *)(h + 1);

    p[0] = (word)ofl;
    p[2] = (word)p;
    p += 4;
    for (; (word)p < (word)lim; p += 4) {
        p[0] = (word)(p-2);
        p[2] = (word)p;
    };
    return((ptr_t)(p-2));
  }
