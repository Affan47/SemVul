gt_pch_nx_tree_int_map (void *x_p)
{
  struct tree_int_map * const x = (struct tree_int_map *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_12tree_int_map))
    {
      gt_pch_n_9tree_node ((*x).base.from);
    }
}
