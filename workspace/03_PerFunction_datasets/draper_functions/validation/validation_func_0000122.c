collect_finally_tree_1 (gimple_seq seq, gimple region)
{
  gimple_stmt_iterator gsi;

  for (gsi = gsi_start (seq); !gsi_end_p (gsi); gsi_next (&gsi))
    collect_finally_tree (gsi_stmt (gsi), region);
}
