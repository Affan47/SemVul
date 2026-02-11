tree_ssa_dse (void)
{
  struct dom_walk_data walk_data;
  struct dse_global_data dse_gd;

  need_eh_cleanup = BITMAP_ALLOC (NULL);

  renumber_gimple_stmt_uids ();


  calculate_dominance_info (CDI_POST_DOMINATORS);
  calculate_dominance_info (CDI_DOMINATORS);


  walk_data.dom_direction = CDI_POST_DOMINATORS;
  walk_data.initialize_block_local_data = dse_initialize_block_local_data;
  walk_data.before_dom_children = dse_enter_block;
  walk_data.after_dom_children = dse_leave_block;

  walk_data.block_local_data_size = sizeof (struct dse_block_local_data);


  dse_gd.stores = BITMAP_ALLOC (NULL);
  walk_data.global_data = &dse_gd;


  init_walk_dominator_tree (&walk_data);


  walk_dominator_tree (&walk_data, EXIT_BLOCK_PTR);


  fini_walk_dominator_tree (&walk_data);


  BITMAP_FREE (dse_gd.stores);


  if (!bitmap_empty_p (need_eh_cleanup))
    {
      gimple_purge_all_dead_eh_edges (need_eh_cleanup);
      cleanup_tree_cfg ();
    }

  BITMAP_FREE (need_eh_cleanup);


  free_dominance_info (CDI_POST_DOMINATORS);
  return 0;
}
