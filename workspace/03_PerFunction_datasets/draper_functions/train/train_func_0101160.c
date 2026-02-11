cst_and_fits_in_hwi (const_tree x)
{
  if (TREE_CODE (x) != INTEGER_CST)
    return false;

  if (TYPE_PRECISION (TREE_TYPE (x)) > HOST_BITS_PER_WIDE_INT)
    return false;

  return (TREE_INT_CST_HIGH (x) == 0
	  || TREE_INT_CST_HIGH (x) == -1);
}
