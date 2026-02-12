create_construction_context(apr_pool_t *result_pool)
{
  construction_context_t *result = apr_pcalloc(result_pool, sizeof(*result));


  result->path = apr_array_make(result_pool, 32, sizeof(node_segment_pair_t));

  return result;
}
