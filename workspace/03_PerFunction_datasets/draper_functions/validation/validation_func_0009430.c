bp__page_load(bp_db_t* t,
                  const uint64_t offset,
                  const uint64_t config,
                  bp__page_t** page) {
  int ret;

  bp__page_t* new_page;
  ret = bp__page_create(t, 0, offset, config, &new_page);
  if (ret != BP_OK) return ret;

  ret = bp__page_read(t, new_page);
  if (ret != BP_OK) {
    bp__page_destroy(t, new_page);
    return ret;
  }


  *page = new_page;

  return BP_OK;
}
