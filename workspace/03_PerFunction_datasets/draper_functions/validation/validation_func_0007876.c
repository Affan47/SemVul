handle_sentinel_attribute (tree *node, tree name, tree args,
			   int ARG_UNUSED (flags), bool *no_add_attrs)
{
  tree params = TYPE_ARG_TYPES (*node);

  if (!prototype_p (*node))
    {
      warning (OPT_Wattributes,
	       "%qE attribute requires prototypes with named arguments", name);
      *no_add_attrs = true;
    }
  else
    {
      while (TREE_CHAIN (params))
	params = TREE_CHAIN (params);

      if (VOID_TYPE_P (TREE_VALUE (params)))
	{
	  warning (OPT_Wattributes,
		   "%qE attribute only applies to variadic functions", name);
	  *no_add_attrs = true;
	}
    }

  if (args)
    {
      tree position = TREE_VALUE (args);

      if (TREE_CODE (position) != INTEGER_CST)
	{
	  warning (OPT_Wattributes,
		   "requested position is not an integer constant");
	  *no_add_attrs = true;
	}
      else
	{
	  if (tree_int_cst_lt (position, integer_zero_node))
	    {
	      warning (OPT_Wattributes,
		       "requested position is less than zero");
	      *no_add_attrs = true;
	    }
	}
    }

  return NULL_TREE;
}
