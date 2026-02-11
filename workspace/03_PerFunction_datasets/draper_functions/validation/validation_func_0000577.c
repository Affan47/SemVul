lookup_property_in_protocol_list (tree rproto_list, tree property)
{
  tree rproto, x;
  for (rproto = rproto_list; rproto; rproto = TREE_CHAIN (rproto))
    {
      tree p = TREE_VALUE (rproto);
      if (TREE_CODE (p) == PROTOCOL_INTERFACE_TYPE)
	{
	  if ((x = lookup_property_in_list (p, property)))
	    return x;
	  if (PROTOCOL_LIST (p))
	    return lookup_property_in_protocol_list (PROTOCOL_LIST (p), property);
	}
      else
	{
	  ;
	}
    }
  return NULL_TREE;
}
