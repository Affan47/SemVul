vect_create_new_slp_node (vec<gimple> scalar_stmts)
{
  slp_tree node;
  gimple stmt = scalar_stmts[0];
  unsigned int nops;

  if (is_gimple_call (stmt))
    nops = gimple_call_num_args (stmt);
  else if (is_gimple_assign (stmt))
    {
      nops = gimple_num_ops (stmt) - 1;
      if (gimple_assign_rhs_code (stmt) == COND_EXPR)
	nops++;
    }
  else
    return NULL;

  node = XNEW (struct _slp_tree);
  SLP_TREE_SCALAR_STMTS (node) = scalar_stmts;
  SLP_TREE_VEC_STMTS (node).create (0);
  SLP_TREE_CHILDREN (node).create (nops);

  return node;
}
