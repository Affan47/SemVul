create_lookup_state(apr_pool_t *result_pool)
{
  lookup_state_t *state = apr_pcalloc(result_pool, sizeof(*state));

  state->next = apr_array_make(result_pool, 4, sizeof(node_t *));
  state->current = apr_array_make(result_pool, 4, sizeof(node_t *));


  state->scratch_pad = svn_stringbuf_create_ensure(200, result_pool);


  state->parent_path = svn_stringbuf_create_ensure(200, result_pool);

  return state;
}
