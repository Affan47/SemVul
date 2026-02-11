qos_get_used(apr_pool_t *pool, apr_table_t *rules, apr_table_t *rules_url,
                                 int from, int to) {
  apr_table_t *used = apr_table_make(pool, 1);
  int j;
  for(j = from; j < to; j++) {
    int l;
    apr_table_entry_t *linee = (apr_table_entry_t *)apr_table_elts(rules_url)->elts;
    if(m_verbose) {
      printf("[%d]", j);
      fflush(stdout);
    }
    for(l = 0; l < apr_table_elts(rules_url)->nelts; l++) {
      char *line = linee[l].key;
      int i;
      int match = 0;
      apr_table_entry_t *entry = (apr_table_entry_t *)apr_table_elts(rules)->elts;
      for(i = 0; i < apr_table_elts(rules)->nelts; i++) {
        if(i != j) {
          qs_rule_t *rs = (qs_rule_t *)entry[i].val;
          if(pcre_exec(rs->pcre, rs->extra, line, strlen(line), 0, 0, NULL, 0) >= 0) {
            match = 1;
            break;
          }
        }
      }
      if(!match) {

        apr_table_add(used, entry[j].key, "+");
      }
    }
  }
  return used;
}
