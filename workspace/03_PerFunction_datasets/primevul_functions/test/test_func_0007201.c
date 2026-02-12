add_prefix_matches(lookup_state_t *state,
                   const svn_stringbuf_t *segment,
                   apr_array_header_t *prefixes)
{


  int i = svn_sort__bsearch_lower_bound(prefixes, segment->data,
                                        compare_node_path_segment);


  if (i < prefixes->nelts)
    add_if_prefix_matches(state,
                          &APR_ARRAY_IDX(prefixes, i, sorted_pattern_t),
                          segment);


  if (i > 0)
    {
      sorted_pattern_t *pattern;
      for (pattern = &APR_ARRAY_IDX(prefixes, i - 1, sorted_pattern_t);
           pattern;
           pattern = pattern->next)
        {
          add_if_prefix_matches(state, pattern, segment);
        }
    }
}
