compute_consensus_package_lines(smartlist_t *votes)
{
  const int n_votes = smartlist_len(votes);


  strmap_t *package_status = strmap_new();

  SMARTLIST_FOREACH_BEGIN(votes, networkstatus_t *, v) {
    if (! v->package_lines)
      continue;
    SMARTLIST_FOREACH_BEGIN(v->package_lines, const char *, line) {
      if (! validate_recommended_package_line(line))
        continue;


      const char *cp = strchr(line, ' ');
      if (!cp) continue;
      ++cp;
      cp = strchr(cp, ' ');
      if (!cp) continue;

      char *key = tor_strndup(line, cp - line);

      const char **status = strmap_get(package_status, key);
      if (!status) {
        status = tor_calloc(n_votes, sizeof(const char *));
        strmap_set(package_status, key, status);
      }
      status[v_sl_idx] = line;
      tor_free(key);
    } SMARTLIST_FOREACH_END(line);
  } SMARTLIST_FOREACH_END(v);

  smartlist_t *entries = smartlist_new();
  smartlist_t *result_list = smartlist_new();
  STRMAP_FOREACH(package_status, key, const char **, values) {
    int i, count=-1;
    for (i = 0; i < n_votes; ++i) {
      if (values[i])
        smartlist_add(entries, (void*) values[i]);
    }
    smartlist_sort_strings(entries);
    int n_voting_for_entry = smartlist_len(entries);
    const char *most_frequent =
      smartlist_get_most_frequent_string_(entries, &count);

    if (n_voting_for_entry >= 3 && count > n_voting_for_entry / 2) {
      smartlist_add_asprintf(result_list, "package %s\n", most_frequent);
    }

    smartlist_clear(entries);

  } STRMAP_FOREACH_END;

  smartlist_sort_strings(result_list);

  char *result = smartlist_join_strings(result_list, "", 0, NULL);

  SMARTLIST_FOREACH(result_list, char *, cp, tor_free(cp));
  smartlist_free(result_list);
  smartlist_free(entries);
  strmap_free(package_status, tor_free_);

  return result;
}
