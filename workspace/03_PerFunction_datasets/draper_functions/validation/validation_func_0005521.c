cond_if_else_store_replacement_1 (basic_block then_bb, basic_block else_bb,
				  basic_block join_bb, gimple then_assign,
				  gimple else_assign)
{
  tree lhs_base, lhs, then_rhs, else_rhs;
  source_location then_locus, else_locus;
  gimple_stmt_iterator gsi;
  gimple newphi, new_stmt;

  if (then_assign == NULL
      || !gimple_assign_single_p (then_assign)
      || gimple_clobber_p (then_assign)
      || gimple_has_volatile_ops (then_assign)
      || else_assign == NULL
      || !gimple_assign_single_p (else_assign)
      || gimple_clobber_p (else_assign)
      || gimple_has_volatile_ops (else_assign))
    return false;

  lhs = gimple_assign_lhs (then_assign);
  if (!is_gimple_reg_type (TREE_TYPE (lhs))
      || !operand_equal_p (lhs, gimple_assign_lhs (else_assign), 0))
    return false;

  lhs_base = get_base_address (lhs);
  if (lhs_base == NULL_TREE
      || (!DECL_P (lhs_base) && TREE_CODE (lhs_base) != MEM_REF))
    return false;

  then_rhs = gimple_assign_rhs1 (then_assign);
  else_rhs = gimple_assign_rhs1 (else_assign);
  then_locus = gimple_location (then_assign);
  else_locus = gimple_location (else_assign);


  gsi = gsi_for_stmt (then_assign);
  unlink_stmt_vdef (then_assign);
  gsi_remove (&gsi, true);
  release_defs (then_assign);

  gsi = gsi_for_stmt (else_assign);
  unlink_stmt_vdef (else_assign);
  gsi_remove (&gsi, true);
  release_defs (else_assign);


  if (!condstoretemp || TREE_TYPE (lhs) != TREE_TYPE (condstoretemp))
    condstoretemp = create_tmp_reg (TREE_TYPE (lhs), "cstore");
  add_referenced_var (condstoretemp);


  newphi = create_phi_node (condstoretemp, join_bb);
  add_phi_arg (newphi, then_rhs, EDGE_SUCC (then_bb, 0), then_locus);
  add_phi_arg (newphi, else_rhs, EDGE_SUCC (else_bb, 0), else_locus);

  new_stmt = gimple_build_assign (lhs, PHI_RESULT (newphi));


  gsi = gsi_after_labels (join_bb);
  if (gsi_end_p (gsi))
    {
      gsi = gsi_last_bb (join_bb);
      gsi_insert_after (&gsi, new_stmt, GSI_NEW_STMT);
    }
  else
    gsi_insert_before (&gsi, new_stmt, GSI_NEW_STMT);

  return true;
}
