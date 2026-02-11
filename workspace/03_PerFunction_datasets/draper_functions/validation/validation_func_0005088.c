can_convert_eh (tree to, tree from)
{
  to = non_reference (to);
  from = non_reference (from);

  if (TREE_CODE (to) == POINTER_TYPE && TREE_CODE (from) == POINTER_TYPE)
    {
      to = TREE_TYPE (to);
      from = TREE_TYPE (from);

      if (! at_least_as_qualified_p (to, from))
	return 0;

      if (TREE_CODE (to) == VOID_TYPE)
	return 1;


    }

  if (CLASS_TYPE_P (to) && CLASS_TYPE_P (from)
      && PUBLICLY_UNIQUELY_DERIVED_P (to, from))
    return 1;

  return 0;
}
