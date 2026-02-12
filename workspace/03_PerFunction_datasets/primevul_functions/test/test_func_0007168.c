add_next_node(lookup_state_t *state,
              node_t *node)
{

  if (node)
    {


      combine_access(&state->rights, &node->rights);


      combine_right_limits(&state->rights, &node->rights);


      APR_ARRAY_PUSH(state->next, node_t *) = node;


      if (node->pattern_sub_nodes && node->pattern_sub_nodes->any_var)
        {
          node = node->pattern_sub_nodes->any_var;


          combine_access(&state->rights, &node->rights);
          combine_right_limits(&state->rights, &node->rights);
          APR_ARRAY_PUSH(state->next, node_t *) = node;
        }
    }
}
