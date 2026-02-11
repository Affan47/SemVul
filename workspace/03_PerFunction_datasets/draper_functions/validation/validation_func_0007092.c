build_accesses_from_assign (gimple stmt)
{
  tree lhs, rhs;
  struct access *lacc, *racc;

  if (!gimple_assign_single_p (stmt)

      || gimple_clobber_p (stmt))
    return false;

  lhs = gimple_assign_lhs (stmt);
  rhs = gimple_assign_rhs1 (stmt);

  if (disqualify_ops_if_throwing_stmt (stmt, lhs, rhs))
    return false;

  racc = build_access_from_expr_1 (rhs, stmt, false);
  lacc = build_access_from_expr_1 (lhs, stmt, true);

  if (lacc)
    lacc->grp_assignment_write = 1;

  if (racc)
    {
      racc->grp_assignment_read = 1;
      if (should_scalarize_away_bitmap && !gimple_has_volatile_ops (stmt)
	  && !is_gimple_reg_type (racc->type))
	bitmap_set_bit (should_scalarize_away_bitmap, DECL_UID (racc->base));
    }

  if (lacc && racc
      && (sra_mode == SRA_MODE_EARLY_INTRA || sra_mode == SRA_MODE_INTRA)
      && !lacc->grp_unscalarizable_region
      && !racc->grp_unscalarizable_region
      && AGGREGATE_TYPE_P (TREE_TYPE (lhs))
      && lacc->size == racc->size
      && useless_type_conversion_p (lacc->type, racc->type))
    {
      struct assign_link *link;

      link = (struct assign_link *) pool_alloc (link_pool);
      memset (link, 0, sizeof (struct assign_link));

      link->lacc = lacc;
      link->racc = racc;

      add_link_to_rhs (racc, link);
    }

  return lacc || racc;
}
