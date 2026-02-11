copy_edges_for_bb (basic_block bb, gcov_type count_scale, basic_block ret_bb)
{
  basic_block new_bb = (basic_block) bb->aux;
  edge_iterator ei;
  edge old_edge;
  gimple_stmt_iterator si;
  int flags;
  bool need_debug_cleanup = false;


  FOR_EACH_EDGE (old_edge, ei, bb->succs)
    if (!(old_edge->flags & EDGE_EH))
      {
	edge new_edge;

	flags = old_edge->flags;


	if (old_edge->dest->index == EXIT_BLOCK && !old_edge->flags
	    && old_edge->dest->aux != EXIT_BLOCK_PTR)
	  flags |= EDGE_FALLTHRU;
	new_edge = make_edge (new_bb, (basic_block) old_edge->dest->aux, flags);
	new_edge->count = old_edge->count * count_scale / REG_BR_PROB_BASE;
	new_edge->probability = old_edge->probability;
      }

  if (bb->index == ENTRY_BLOCK || bb->index == EXIT_BLOCK)
    return false;

  for (si = gsi_start_bb (new_bb); !gsi_end_p (si);)
    {
      gimple copy_stmt;
      bool can_throw, nonlocal_goto;

      copy_stmt = gsi_stmt (si);
      if (!is_gimple_debug (copy_stmt))
	{
	  update_stmt (copy_stmt);
	  if (gimple_in_ssa_p (cfun))
	    mark_symbols_for_renaming (copy_stmt);
	}


      gsi_next (&si);


      can_throw = stmt_can_throw_internal (copy_stmt);
      nonlocal_goto = stmt_can_make_abnormal_goto (copy_stmt);

      if (can_throw || nonlocal_goto)
	{
	  if (!gsi_end_p (si))
	    {
	      while (!gsi_end_p (si) && is_gimple_debug (gsi_stmt (si)))
		gsi_next (&si);
	      if (gsi_end_p (si))
		need_debug_cleanup = true;
	    }
	  if (!gsi_end_p (si))


	    {
	      edge e = split_block (new_bb, copy_stmt);

	      new_bb = e->dest;
	      new_bb->aux = e->src->aux;
	      si = gsi_start_bb (new_bb);
	    }
	}

      if (gimple_code (copy_stmt) == GIMPLE_EH_DISPATCH)
	make_eh_dispatch_edges (copy_stmt);
      else if (can_throw)
	make_eh_edges (copy_stmt);

      if (nonlocal_goto)
	make_abnormal_goto_edges (gimple_bb (copy_stmt), true);

      if ((can_throw || nonlocal_goto)
	  && gimple_in_ssa_p (cfun))
	update_ssa_across_abnormal_edges (gimple_bb (copy_stmt), ret_bb,
					  can_throw, nonlocal_goto);
    }
  return need_debug_cleanup;
}
