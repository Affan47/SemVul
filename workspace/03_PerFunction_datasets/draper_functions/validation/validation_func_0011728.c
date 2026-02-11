flexible_array_type_p (type)
     tree type;
{
  tree x;
  switch (TREE_CODE (type))
    {
    case RECORD_TYPE:
      x = TYPE_FIELDS (type);
      if (x == NULL_TREE)
	return false;
      while (TREE_CHAIN (x) != NULL_TREE)
	x = TREE_CHAIN (x);
      if (TREE_CODE (TREE_TYPE (x)) == ARRAY_TYPE
	  && TYPE_SIZE (TREE_TYPE (x)) == NULL_TREE
	  && TYPE_DOMAIN (TREE_TYPE (x)) != NULL_TREE
	  && TYPE_MAX_VALUE (TYPE_DOMAIN (TREE_TYPE (x))) == NULL_TREE)
	return true;
      return false;
    case UNION_TYPE:
      for (x = TYPE_FIELDS (type); x != NULL_TREE; x = TREE_CHAIN (x))
	{
	  if (flexible_array_type_p (TREE_TYPE (x)))
	    return true;
	}
      return false;
    default:
    return false;
  }
}
