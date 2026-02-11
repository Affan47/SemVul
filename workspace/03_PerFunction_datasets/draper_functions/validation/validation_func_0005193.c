hts_set_callback(t_hts_htmlcheck_callbacks * callbacks, const char *name,
                     void *function) {
  size_t offs = hts_get_callback_offs(name);

  if (offs != (size_t) - 1) {
    MEMBER_OF(callbacks, offs, void *) = function;

    return 0;
  }
  return 1;
}
