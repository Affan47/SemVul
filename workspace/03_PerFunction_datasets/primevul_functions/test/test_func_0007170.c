link_prefix_patterns(apr_array_header_t *array)
{
  int i;
  if (!array)
    return;

  for (i = 1; i < array->nelts; ++i)
    {
      sorted_pattern_t *prev
        = &APR_ARRAY_IDX(array, i - 1, sorted_pattern_t);
      sorted_pattern_t *pattern
        = &APR_ARRAY_IDX(array, i, sorted_pattern_t);


      if (prev->node->segment.data[0] != pattern->node->segment.data[0])
        continue;


      for ( ; prev; prev = prev->next)
        if (   prev->node->segment.len < pattern->node->segment.len
            && !memcmp(prev->node->segment.data,
                       pattern->node->segment.data,
                       prev->node->segment.len))
          {
            pattern->next = prev;
            break;
          }
    }
}
