local_def (tree val)
{
  gimple stmt, def_stmt;
  basic_block bb, def_bb;
  imm_use_iterator iter;
  bool res;

  if (TREE_CODE (val) != SSA_NAME)
    return false;
  def_stmt = SSA_NAME_DEF_STMT (val);
  def_bb = gimple_bb (def_stmt);

  res = true;
  FOR_EACH_IMM_USE_STMT (stmt, iter, val)
    {
      if (is_gimple_debug (stmt))
	continue;
      bb = gimple_bb (stmt);
      if (bb == def_bb)
	continue;
      if (gimple_code (stmt) == GIMPLE_PHI
	  && find_edge (def_bb, bb))
	continue;
      res = false;
      BREAK_FROM_IMM_USE_STMT (iter);
    }
  return res;
}
