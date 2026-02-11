end_of_class (tree t, int include_virtuals_p)
{
  tree result = size_zero_node;
  tree binfo;
  tree offset;
  int i;

  for (i = 0; i < CLASSTYPE_N_BASECLASSES (t); ++i)
    {
      binfo = BINFO_BASETYPE (TYPE_BINFO (t), i);

      if (!include_virtuals_p
	  && TREE_VIA_VIRTUAL (binfo)
	  && BINFO_PRIMARY_BASE_OF (binfo) != TYPE_BINFO (t))
	continue;

      offset = end_of_base (binfo);
      if (INT_CST_LT_UNSIGNED (result, offset))
	result = offset;
    }


  if (abi_version_at_least (2) && include_virtuals_p)
    for (binfo = CLASSTYPE_VBASECLASSES (t);
	 binfo;
	 binfo = TREE_CHAIN (binfo))
      {
	offset = end_of_base (TREE_VALUE (binfo));
	if (INT_CST_LT_UNSIGNED (result, offset))
	  result = offset;
      }

  return result;
}
