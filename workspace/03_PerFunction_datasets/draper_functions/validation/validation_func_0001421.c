mark_use_interesting (tree var, gimple stmt, basic_block bb, bool insert_phi_p)
{
  basic_block def_bb = gimple_bb (stmt);

  mark_block_for_update (def_bb);
  mark_block_for_update (bb);

  if (gimple_code (stmt) == GIMPLE_PHI)
    mark_phi_for_rewrite (def_bb, stmt);
  else
    {
      set_rewrite_uses (stmt, true);

      if (is_gimple_debug (stmt))
	return;
    }


  if (insert_phi_p)
    {
      struct def_blocks_d *db_p = get_def_blocks_for (get_common_info (var));
      if (!bitmap_bit_p (db_p->def_blocks, bb->index))
	set_livein_block (var, bb);
    }
}
