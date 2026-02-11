really_overloaded_fn (tree x)
{

  if (TREE_CODE (x) == OFFSET_REF)
    x = TREE_OPERAND (x, 1);
  if (BASELINK_P (x))
    x = BASELINK_FUNCTIONS (x);

  return ((TREE_CODE (x) == OVERLOAD && OVL_CHAIN (x))
	  || DECL_FUNCTION_TEMPLATE_P (OVL_CURRENT (x))
	  || TREE_CODE (x) == TEMPLATE_ID_EXPR);
}
