gimple_make_forwarder_block (edge fallthru)
{
  edge e;
  edge_iterator ei;
  basic_block dummy, bb;
  tree var;
  gimple_stmt_iterator gsi;

  dummy = fallthru->src;
  bb = fallthru->dest;

  if (single_pred_p (bb))
    return;


  for (gsi = gsi_start_phis (dummy); !gsi_end_p (gsi); gsi_next (&gsi))
    {
      gimple phi, new_phi;

      phi = gsi_stmt (gsi);
      var = gimple_phi_result (phi);
      new_phi = create_phi_node (var, bb);
      SSA_NAME_DEF_STMT (var) = new_phi;
      gimple_phi_set_result (phi, make_ssa_name (SSA_NAME_VAR (var), phi));
      add_phi_arg (new_phi, gimple_phi_result (phi), fallthru,
		   UNKNOWN_LOCATION);
    }


  FOR_EACH_EDGE (e, ei, bb->preds)
    {
      if (e == fallthru)
	continue;

      flush_pending_stmts (e);
    }
}
