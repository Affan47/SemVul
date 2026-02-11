may_eliminate_iv (struct ivopts_data *data,
		  struct iv_use *use, struct iv_cand *cand, tree *bound,
		  enum tree_code *comp)
{
  basic_block ex_bb;
  edge exit;
  tree period;
  struct loop *loop = data->current_loop;
  aff_tree bnd;
  struct tree_niter_desc *desc = NULL;

  if (TREE_CODE (cand->iv->step) != INTEGER_CST)
    return false;


  ex_bb = gimple_bb (use->stmt);
  if (use->stmt != last_stmt (ex_bb)
      || gimple_code (use->stmt) != GIMPLE_COND
      || !dominated_by_p (CDI_DOMINATORS, loop->latch, ex_bb))
    return false;

  exit = EDGE_SUCC (ex_bb, 0);
  if (flow_bb_inside_loop_p (loop, exit->dest))
    exit = EDGE_SUCC (ex_bb, 1);
  if (flow_bb_inside_loop_p (loop, exit->dest))
    return false;

  desc = niter_for_exit (data, exit);
  if (!desc)
    return false;


  period = iv_period (cand->iv);


  if (TREE_CODE (desc->niter) == INTEGER_CST)
    {

      if (stmt_after_increment (loop, cand, use->stmt))
        {
          if (!tree_int_cst_lt (desc->niter, period))
            return false;
        }
      else
        {
          if (tree_int_cst_lt (period, desc->niter))
            return false;
        }
    }


  else
    {
      double_int period_value, max_niter;

      max_niter = desc->max;
      if (stmt_after_increment (loop, cand, use->stmt))
        max_niter += double_int_one;
      period_value = tree_to_double_int (period);
      if (max_niter.ugt (period_value))
        {

          if (data->loop_single_exit_p)
            {
              if (!max_loop_iterations (loop, &max_niter))
                return false;

              if (max_niter.ugt (period_value))
                return false;
            }
          else
            return false;
        }
    }

  cand_value_at (loop, cand, use->stmt, desc->niter, &bnd);

  *bound = aff_combination_to_tree (&bnd);
  *comp = iv_elimination_compare (data, use);


  if (expression_expensive_p (*bound))
    return false;


  if (!integer_zerop (desc->may_be_zero))
    return iv_elimination_compare_lt (data, cand, comp, desc);

  return true;
}
