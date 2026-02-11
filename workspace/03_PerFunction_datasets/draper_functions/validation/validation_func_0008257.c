save_expr (expr)
     tree expr;
{
  tree t = fold (expr);
  tree inner;


  while (TREE_CODE (t) == NON_LVALUE_EXPR)
    t = TREE_OPERAND (t, 0);


  for (inner = t;
       (TREE_CODE_CLASS (TREE_CODE (inner)) == '1'
	|| (TREE_CODE_CLASS (TREE_CODE (inner)) == '2'
	    && TREE_CONSTANT (TREE_OPERAND (inner, 1))));
       inner = TREE_OPERAND (inner, 0))
    ;


  if (TREE_CONSTANT (inner)
      || (TREE_READONLY (inner) && ! TREE_SIDE_EFFECTS (inner))
      || TREE_CODE (inner) == SAVE_EXPR || TREE_CODE (inner) == ERROR_MARK)
    return t;


  if (contains_placeholder_p (t))
    return t;

  t = build (SAVE_EXPR, TREE_TYPE (expr), t, current_function_decl, NULL_TREE);


  TREE_SIDE_EFFECTS (t) = 1;
  TREE_READONLY (t) = 1;
  return t;
}
