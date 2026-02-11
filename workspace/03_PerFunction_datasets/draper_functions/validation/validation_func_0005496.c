cxx_eval_outermost_constant_expr (tree t, bool allow_non_constant)
{
  bool non_constant_p = false;
  bool overflow_p = false;
  tree r = cxx_eval_constant_expression (NULL, t, allow_non_constant,
					 false, &non_constant_p, &overflow_p);

  verify_constant (r, allow_non_constant, &non_constant_p, &overflow_p);

  if (TREE_CODE (t) != CONSTRUCTOR
      && cp_has_mutable_p (TREE_TYPE (t)))
    {


      if (!allow_non_constant)
	error ("%qT cannot be the type of a complete constant expression "
	       "because it has mutable sub-objects", TREE_TYPE (t));
      non_constant_p = true;
    }


  if (CONVERT_EXPR_CODE_P (TREE_CODE (r))
      && ARITHMETIC_TYPE_P (TREE_TYPE (r))
      && TREE_CODE (TREE_OPERAND (r, 0)) == ADDR_EXPR)
    {
      if (!allow_non_constant)
	error ("conversion from pointer type %qT "
	       "to arithmetic type %qT in a constant-expression",
	       TREE_TYPE (TREE_OPERAND (r, 0)), TREE_TYPE (r));
      non_constant_p = true;
    }

  if (!non_constant_p && overflow_p)
    non_constant_p = true;

  if (non_constant_p && !allow_non_constant)
    return error_mark_node;
  else if (non_constant_p && TREE_CONSTANT (r))
    {

      if (EXPR_P (r))
	r = copy_node (r);
      else if (TREE_CODE (r) == CONSTRUCTOR)
	r = build1 (VIEW_CONVERT_EXPR, TREE_TYPE (r), r);
      else
	r = build_nop (TREE_TYPE (r), r);
      TREE_CONSTANT (r) = false;
    }
  else if (non_constant_p || r == t)
    return t;

  if (TREE_CODE (r) == CONSTRUCTOR && CLASS_TYPE_P (TREE_TYPE (r)))
    {
      if (TREE_CODE (t) == TARGET_EXPR
	  && TARGET_EXPR_INITIAL (t) == r)
	return t;
      else
	{
	  r = get_target_expr (r);
	  TREE_CONSTANT (r) = true;
	  return r;
	}
    }
  else
    return r;
}
