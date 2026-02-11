GC_register_dynamic_libraries_dl_iterate_phdr(void)
{
  int did_something;
  if (GC_register_main_static_data())
    return FALSE;

# ifdef PT_GNU_RELRO
    {
      static GC_bool excluded_segs = FALSE;
      n_load_segs = 0;
      if (!excluded_segs) {
        GC_exclude_static_roots_inner((ptr_t)load_segs,
                                      (ptr_t)load_segs + sizeof(load_segs));
        excluded_segs = TRUE;
      }
    }
# endif

  did_something = 0;
  dl_iterate_phdr(GC_register_dynlib_callback, &did_something);
  if (did_something) {
#   ifdef PT_GNU_RELRO
      int i;

      for (i = 0; i < n_load_segs; ++i) {
        if (load_segs[i].end > load_segs[i].start) {
          GC_add_roots_inner(load_segs[i].start, load_segs[i].end, TRUE);
        }
        if (load_segs[i].end2 > load_segs[i].start2) {
          GC_add_roots_inner(load_segs[i].start2, load_segs[i].end2, TRUE);
        }
      }
#   endif
  } else {
      char *datastart;
      char *dataend;
#     ifdef DATASTART_IS_FUNC
        static ptr_t datastart_cached = (ptr_t)(word)-1;


        if (datastart_cached == (ptr_t)(word)-1) {
          datastart_cached = (ptr_t)(DATASTART);
        }
        datastart = (char *)datastart_cached;
#     else
        datastart = DATASTART;
#     endif
#     ifdef DATAEND_IS_FUNC
        {
          static ptr_t dataend_cached = 0;

          if (dataend_cached == 0) {
            dataend_cached = (ptr_t)(DATAEND);
          }
          dataend = (char *)dataend_cached;
        }
#     else
        dataend = DATAEND;
#     endif


      GC_add_roots_inner(datastart, dataend, TRUE);
#     if defined(DATASTART2)
        GC_add_roots_inner(DATASTART2, (char *)(DATAEND2), TRUE);
#     endif
  }
  return TRUE;
}
