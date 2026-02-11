GC_build_fl(struct hblk *h, size_t sz, GC_bool clear,
                           ptr_t list)
{
  word *p, *prev;
  word *last_object;


    PREFETCH_FOR_WRITE((ptr_t)h);
    PREFETCH_FOR_WRITE((ptr_t)h + 128);
    PREFETCH_FOR_WRITE((ptr_t)h + 256);
    PREFETCH_FOR_WRITE((ptr_t)h + 378);
# ifndef SMALL_CONFIG


    switch (sz) {
        case 2: if (clear) {
                    return GC_build_fl_clear2(h, list);
                } else {
                    return GC_build_fl2(h, list);
                }
        case 4: if (clear) {
                    return GC_build_fl_clear4(h, list);
                } else {
                    return GC_build_fl4(h, list);
                }
        default:
                break;
    }
# endif


    if (clear) BZERO(h, HBLKSIZE);


    p = (word *)(h -> hb_body) + sz;
    prev = (word *)(h -> hb_body);
    last_object = (word *)((char *)h + HBLKSIZE);
    last_object -= sz;


    while ((word)p <= (word)last_object) {

        obj_link(p) = (ptr_t)prev;
        prev = p;
        p += sz;
    }
    p -= sz;


    *(ptr_t *)h = list;
    return ((ptr_t)p);
}
