dirserv_cache_measured_bw(const measured_bw_line_t *parsed_line,
                          time_t as_of)
{
  mbw_cache_entry_t *e = NULL;

  tor_assert(parsed_line);


  if (!mbw_cache) mbw_cache = digestmap_new();


  e = digestmap_get(mbw_cache, parsed_line->node_id);

  if (e) {

    if (as_of > e->as_of) {
      e->mbw_kb = parsed_line->bw_kb;
      e->as_of = as_of;
    }
  } else {

    e = tor_malloc(sizeof(*e));
    e->mbw_kb = parsed_line->bw_kb;
    e->as_of = as_of;
    digestmap_set(mbw_cache, parsed_line->node_id, e);
  }
}
