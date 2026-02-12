get_subpat_names(const pcre_cache_entry* pce) {
  char **subpat_names = pce->subpat_names.load(std::memory_order_relaxed);
  if (subpat_names) {
    return subpat_names;
  }


  pcre_extra extra;
  init_local_extra(&extra, pce->extra);

  int name_count;

  subpat_names = (char **)calloc(pce->num_subpats, sizeof(char *));
  int rc = pcre_fullinfo(pce->re, &extra, PCRE_INFO_NAMECOUNT, &name_count);
  if (rc < 0) {
    raise_warning("Internal pcre_fullinfo() error %d", rc);
    return nullptr;
  }
  if (name_count > 0) {
    int name_size, ni = 0;
    unsigned short name_idx;
    char* name_table;
    int rc1, rc2;

    rc1 = pcre_fullinfo(pce->re, &extra, PCRE_INFO_NAMETABLE, &name_table);
    rc2 = pcre_fullinfo(pce->re, &extra, PCRE_INFO_NAMEENTRYSIZE, &name_size);
    rc = rc2 ? rc2 : rc1;
    if (rc < 0) {
      raise_warning("Internal pcre_fullinfo() error %d", rc);
      return nullptr;
    }


    while (ni++ < name_count) {
      name_idx = 0x100 * (unsigned char)name_table[0] +
                 (unsigned char)name_table[1];
      subpat_names[name_idx] = name_table + 2;
      if (is_numeric_string(subpat_names[name_idx],
                            strlen(subpat_names[name_idx]),
                            nullptr, nullptr, 0) != KindOfNull) {
        raise_warning("Numeric named subpatterns are not allowed");
        return nullptr;
      }
      name_table += name_size;
    }
  }

  char **expected = nullptr;
  if (!pce->subpat_names.compare_exchange_strong(expected, subpat_names)) {


    free(subpat_names);
    return expected;
  }
  return subpat_names;
}
