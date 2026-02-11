if_convertible_loop_p_1 (struct loop *loop,
			 VEC (loop_p, heap) **loop_nest,
			 VEC (data_reference_p, heap) **refs,
			 VEC (ddr_p, heap) **ddrs)
{
  bool res;
  unsigned int i;
  basic_block exit_bb = NULL;


  res = compute_data_dependences_for_loop (loop, true, loop_nest, refs, ddrs);
  if (!res)
    return false;

  calculate_dominance_info (CDI_DOMINATORS);


  ifc_bbs = get_loop_body_in_if_conv_order (loop);
  if (!ifc_bbs)
    {
      if (dump_file && (dump_flags & TDF_DETAILS))
	fprintf (dump_file, "Irreducible loop\n");
      return false;
    }

  for (i = 0; i < loop->num_nodes; i++)
    {
      basic_block bb = ifc_bbs[i];

      if (!if_convertible_bb_p (loop, bb, exit_bb))
	return false;

      if (bb_with_exit_edge_p (loop, bb))
	exit_bb = bb;
    }

  res = predicate_bbs (loop);
  if (!res)
    return false;

  if (flag_tree_loop_if_convert_stores)
    {
      data_reference_p dr;

      for (i = 0; VEC_iterate (data_reference_p, *refs, i, dr); i++)
	{
	  dr->aux = XNEW (struct ifc_dr);
	  DR_WRITTEN_AT_LEAST_ONCE (dr) = -1;
	  DR_RW_UNCONDITIONALLY (dr) = -1;
	}
    }

  for (i = 0; i < loop->num_nodes; i++)
    {
      basic_block bb = ifc_bbs[i];
      gimple_stmt_iterator itr;

      for (itr = gsi_start_phis (bb); !gsi_end_p (itr); gsi_next (&itr))
	if (!if_convertible_phi_p (loop, bb, gsi_stmt (itr)))
	  return false;


      if (is_predicated (bb))
	for (itr = gsi_start_bb (bb); !gsi_end_p (itr); gsi_next (&itr))
	  if (!if_convertible_stmt_p (gsi_stmt (itr), *refs))
	    return false;
    }

  if (dump_file)
    fprintf (dump_file, "Applying if-conversion\n");

  return true;
}
