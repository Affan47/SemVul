sync_resolve_size (tree function, VEC(tree,gc) *params)
{
  tree type;
  int size;

  if (VEC_empty (tree, params))
    {
      error ("too few arguments to function %qE", function);
      return 0;
    }

  type = TREE_TYPE (VEC_index (tree, params, 0));
  if (TREE_CODE (type) != POINTER_TYPE)
    goto incompatible;

  type = TREE_TYPE (type);
  if (!INTEGRAL_TYPE_P (type) && !POINTER_TYPE_P (type))
    goto incompatible;

  size = tree_low_cst (TYPE_SIZE_UNIT (type), 1);
  if (size == 1 || size == 2 || size == 4 || size == 8 || size == 16)
    return size;

 incompatible:
  error ("incompatible type for argument %d of %qE", 1, function);
  return 0;
}
