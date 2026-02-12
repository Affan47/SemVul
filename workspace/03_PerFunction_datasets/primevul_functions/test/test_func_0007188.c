finalize_tree(node_t *node,
              limited_rights_t *sum,
              apr_pool_t *scratch_pool)
{
  limited_rights_t *local_sum = &node->rights;


  if (!node)
    return;


  if (has_local_rule(local_sum))
    {
      local_sum->max_rights = local_sum->access.rights;
      local_sum->min_rights = local_sum->access.rights;
    }
  else
    {
      local_sum->min_rights = authz_access_write;
      local_sum->max_rights = authz_access_none;
    }


  finalize_subnode_hash(node->sub_nodes, local_sum, scratch_pool);

  if (node->pattern_sub_nodes)
    {
      finalize_tree(node->pattern_sub_nodes->any, local_sum, scratch_pool);
      finalize_tree(node->pattern_sub_nodes->any_var, local_sum, scratch_pool);

      finalize_subnode_array(node->pattern_sub_nodes->prefixes, local_sum,
                             scratch_pool);
      finalize_subnode_array(node->pattern_sub_nodes->suffixes, local_sum,
                             scratch_pool);
      finalize_subnode_array(node->pattern_sub_nodes->complex, local_sum,
                             scratch_pool);


      link_prefix_patterns(node->pattern_sub_nodes->prefixes);
      link_prefix_patterns(node->pattern_sub_nodes->suffixes);
    }


  combine_right_limits(sum, local_sum);
}
