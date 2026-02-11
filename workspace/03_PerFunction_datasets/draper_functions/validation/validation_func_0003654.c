convert_nontype_argument_function (tree type, tree expr)
{
  tree fns = expr;
  tree fn, fn_no_ptr;
  linkage_kind linkage;

  fn = instantiate_type (type, fns, tf_none);
  if (fn == error_mark_node)
    return error_mark_node;

  fn_no_ptr = fn;
  if (TREE_CODE (fn_no_ptr) == ADDR_EXPR)
    fn_no_ptr = TREE_OPERAND (fn_no_ptr, 0);
  if (BASELINK_P (fn_no_ptr))
    fn_no_ptr = BASELINK_FUNCTIONS (fn_no_ptr);


  linkage = decl_linkage (fn_no_ptr);
  if (cxx_dialect >= cxx0x ? linkage == lk_none : linkage != lk_external)
    {
      if (cxx_dialect >= cxx0x)
	error ("%qE is not a valid template argument for type %qT "
	       "because %qD has no linkage",
	       expr, type, fn_no_ptr);
      else
	error ("%qE is not a valid template argument for type %qT "
	       "because %qD does not have external linkage",
	       expr, type, fn_no_ptr);
      return NULL_TREE;
    }

  return fn;
}
