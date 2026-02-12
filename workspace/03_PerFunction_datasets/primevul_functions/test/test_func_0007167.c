lookup(lookup_state_t *state,
       const char *path,
       authz_access_t required,
       svn_boolean_t recursive,
       apr_pool_t *scratch_pool)
{

  apr_size_t path_len = strlen(path);
  svn_stringbuf_ensure(state->scratch_pad, path_len);


  if (path_len && path[path_len-1] == '/')
    {
      do
      {
        --path_len;
      }
      while (path_len && path[path_len-1] == '/');
      path = apr_pstrmemdup(scratch_pool, path, path_len);
    }

  while (path[0] == '/')
    ++path;


  while (state->current->nelts && path)
    {
      apr_array_header_t *temp;
      int i;
      svn_stringbuf_t *segment = state->scratch_pad;


      if ((state->rights.max_rights & required) != required)
        return FALSE;


      if ((state->rights.min_rights & required) == required)
        return TRUE;


      path = next_segment(segment, path);


      apr_array_clear(state->next);
      state->rights.access.sequence_number = NO_SEQUENCE_NUMBER;
      state->rights.access.rights = authz_access_none;


      state->rights.min_rights = authz_access_write;
      state->rights.max_rights = authz_access_none;


      if (path)
        {
          svn_stringbuf_appendbyte(state->parent_path, '/');
          svn_stringbuf_appendbytes(state->parent_path, segment->data,
                                    segment->len);
        }


      for (i = 0; i < state->current->nelts; ++i)
        {
          node_t *node = APR_ARRAY_IDX(state->current, i, node_t *);
          if (node->sub_nodes)
            add_next_node(state, apr_hash_get(node->sub_nodes, segment->data,
                                              segment->len));


          if (node->pattern_sub_nodes)
            {
              add_next_node(state, node->pattern_sub_nodes->any);


              if (node->pattern_sub_nodes->repeat)
                add_next_node(state, node);


              if (node->pattern_sub_nodes->prefixes)
                add_prefix_matches(state, segment,
                                   node->pattern_sub_nodes->prefixes);

              if (node->pattern_sub_nodes->complex)
                add_complex_matches(state, segment,
                                    node->pattern_sub_nodes->complex);


              if (node->pattern_sub_nodes->suffixes)
                {

                  svn_authz__reverse_string(segment->data, segment->len);
                  add_prefix_matches(state, segment,
                                     node->pattern_sub_nodes->suffixes);
                }
            }
        }


      if (!has_local_rule(&state->rights))
        {
          state->rights.access = state->parent_rights.access;
          state->rights.min_rights &= state->parent_rights.access.rights;
          state->rights.max_rights |= state->parent_rights.access.rights;
        }


      if (path)
        {
          temp = state->current;
          state->current = state->next;
          state->next = temp;


          state->parent_rights = state->rights;
        }
    }


  if (recursive)
    return (state->rights.min_rights & required) == required;


  return (state->rights.access.rights & required) == required;
}
