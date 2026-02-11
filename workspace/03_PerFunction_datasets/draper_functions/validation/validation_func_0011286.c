live_track_remove_partition (live_track_p ptr, int partition)
{
  int root;

  root = basevar_index (ptr->map, partition);
  bitmap_clear_bit (ptr->live_base_partitions[root], partition);

  if (bitmap_empty_p (ptr->live_base_partitions[root]))
    bitmap_clear_bit (ptr->live_base_var, root);
}
