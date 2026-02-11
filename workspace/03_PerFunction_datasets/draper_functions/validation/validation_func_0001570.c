live_track_process_def (live_track_p ptr, tree def, ssa_conflicts_p graph)
{
  int p, root;
  bitmap b;
  unsigned x;
  bitmap_iterator bi;

  p = var_to_partition (ptr->map, def);
  if (p == NO_PARTITION)
    return;


  live_track_remove_partition (ptr, p);


  root = basevar_index (ptr->map, p);
  if (bitmap_bit_p (ptr->live_base_var, root))
    {
      b = ptr->live_base_partitions[root];
      EXECUTE_IF_SET_IN_BITMAP (b, 0, x, bi)
        ssa_conflicts_add (graph, p, x);
    }
}
