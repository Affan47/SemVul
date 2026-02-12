trim_subnode_array(apr_array_header_t **array,
                   int latest_any_var,
                   apr_pool_t *scratch_pool)
{
  if (*array)
    {
      int i, dest;
      for (i = 0, dest = 0; i < (*array)->nelts; ++i)
        {
          node_t *node = APR_ARRAY_IDX(*array, i, sorted_pattern_t).node;
          if (!trim_tree(node, latest_any_var, scratch_pool))
            {
              if (i != dest)
                APR_ARRAY_IDX(*array, dest, sorted_pattern_t)
                  = APR_ARRAY_IDX(*array, i, sorted_pattern_t);
              ++dest;
            }
        }


      if (dest)
        {

          (*array)->nelts = dest;
          return FALSE;
        }


      *array = NULL;
    }

  return TRUE;
}
