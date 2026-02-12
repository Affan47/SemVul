init_lockup_state(lookup_state_t *state,
                  node_t *root,
                  const char *path)
{
  apr_size_t len = strlen(path);
  if (   (len > state->parent_path->len)
      && state->parent_path->len
      && (path[state->parent_path->len] == '/')
      && !memcmp(path, state->parent_path->data, state->parent_path->len))
    {


      state->rights = state->parent_rights;


      return path + state->parent_path->len;
    }


  state->rights = root->rights;
  state->parent_rights = root->rights;

  apr_array_clear(state->next);
  apr_array_clear(state->current);
  APR_ARRAY_PUSH(state->current, node_t *) = root;


  if (root->pattern_sub_nodes && root->pattern_sub_nodes->any_var)
   {
      node_t *node = root->pattern_sub_nodes->any_var;


      combine_access(&state->rights, &node->rights);
      combine_right_limits(&state->rights, &node->rights);
      APR_ARRAY_PUSH(state->current, node_t *) = node;
   }

  svn_stringbuf_setempty(state->parent_path);
  svn_stringbuf_setempty(state->scratch_pad);

  return path;
}
