gimple_duplicate_bb (basic_block bb)
{
  basic_block new_bb;
  gimple_stmt_iterator gsi, gsi_tgt;
  gimple_seq phis = phi_nodes (bb);
  gimple phi, stmt, copy;

  new_bb = create_empty_bb (EXIT_BLOCK_PTR->prev_bb);


  for (gsi = gsi_start (phis); !gsi_end_p (gsi); gsi_next (&gsi))
    {
      phi = gsi_stmt (gsi);
      copy = create_phi_node (NULL_TREE, new_bb);
      create_new_def_for (gimple_phi_result (phi), copy,
			  gimple_phi_result_ptr (copy));
    }

  gsi_tgt = gsi_start_bb (new_bb);
  for (gsi = gsi_start_bb (bb); !gsi_end_p (gsi); gsi_next (&gsi))
    {
      def_operand_p def_p;
      ssa_op_iter op_iter;
      tree lhs;

      stmt = gsi_stmt (gsi);
      if (gimple_code (stmt) == GIMPLE_LABEL)
	continue;


      if (gimple_debug_bind_p (stmt)
	  && TREE_CODE (gimple_debug_bind_get_var (stmt))
	     == LABEL_DECL)
	continue;


      copy = gimple_copy (stmt);
      gsi_insert_after (&gsi_tgt, copy, GSI_NEW_STMT);

      maybe_duplicate_eh_stmt (copy, stmt);
      gimple_duplicate_stmt_histograms (cfun, copy, cfun, stmt);


      lhs = gimple_get_lhs (stmt);
      if (lhs && TREE_CODE (lhs) != SSA_NAME)
	{
	  tree base = get_base_address (lhs);
	  if (base
	      && (TREE_CODE (base) == VAR_DECL
		  || TREE_CODE (base) == RESULT_DECL)
	      && DECL_IGNORED_P (base)
	      && !TREE_STATIC (base)
	      && !DECL_EXTERNAL (base)
	      && (TREE_CODE (base) != VAR_DECL
		  || !DECL_HAS_VALUE_EXPR_P (base)))
	    DECL_NONSHAREABLE (base) = 1;
	}


      FOR_EACH_SSA_DEF_OPERAND (def_p, copy, op_iter, SSA_OP_ALL_DEFS)
	create_new_def_for (DEF_FROM_PTR (def_p), copy, def_p);
    }

  return new_bb;
}
