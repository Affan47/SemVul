tree_simplify_using_condition_1 (tree cond, tree expr)
{
  bool changed;
  tree e, te, e0, e1, e2, notcond;
  enum tree_code code = TREE_CODE (expr);

  if (code == INTEGER_CST)
    return expr;

  if (code == TRUTH_OR_EXPR
      || code == TRUTH_AND_EXPR
      || code == COND_EXPR)
    {
      changed = false;

      e0 = tree_simplify_using_condition_1 (cond, TREE_OPERAND (expr, 0));
      if (TREE_OPERAND (expr, 0) != e0)
	changed = true;

      e1 = tree_simplify_using_condition_1 (cond, TREE_OPERAND (expr, 1));
      if (TREE_OPERAND (expr, 1) != e1)
	changed = true;

      if (code == COND_EXPR)
	{
	  e2 = tree_simplify_using_condition_1 (cond, TREE_OPERAND (expr, 2));
	  if (TREE_OPERAND (expr, 2) != e2)
	    changed = true;
	}
      else
	e2 = NULL_TREE;

      if (changed)
	{
	  if (code == COND_EXPR)
	    expr = fold_build3 (code, boolean_type_node, e0, e1, e2);
	  else
	    expr = fold_build2 (code, boolean_type_node, e0, e1);
	}

      return expr;
    }


  if (TREE_CODE (cond) == EQ_EXPR)
    {
      e0 = TREE_OPERAND (cond, 0);
      e1 = TREE_OPERAND (cond, 1);


      e = simplify_replace_tree (expr, e0, e1);
      if (integer_zerop (e) || integer_nonzerop (e))
	return e;

      e = simplify_replace_tree (expr, e1, e0);
      if (integer_zerop (e) || integer_nonzerop (e))
	return e;
    }
  if (TREE_CODE (expr) == EQ_EXPR)
    {
      e0 = TREE_OPERAND (expr, 0);
      e1 = TREE_OPERAND (expr, 1);


      e = simplify_replace_tree (cond, e0, e1);
      if (integer_zerop (e))
	return e;
      e = simplify_replace_tree (cond, e1, e0);
      if (integer_zerop (e))
	return e;
    }
  if (TREE_CODE (expr) == NE_EXPR)
    {
      e0 = TREE_OPERAND (expr, 0);
      e1 = TREE_OPERAND (expr, 1);


      e = simplify_replace_tree (cond, e0, e1);
      if (integer_zerop (e))
	return boolean_true_node;
      e = simplify_replace_tree (cond, e1, e0);
      if (integer_zerop (e))
	return boolean_true_node;
    }

  te = expand_simple_operations (expr);


  notcond = invert_truthvalue (cond);
  e = fold_binary (TRUTH_OR_EXPR, boolean_type_node, notcond, te);
  if (e && integer_nonzerop (e))
    return e;


  e = fold_binary (TRUTH_AND_EXPR, boolean_type_node, cond, te);
  if (e && integer_zerop (e))
    return e;

  return expr;
}
