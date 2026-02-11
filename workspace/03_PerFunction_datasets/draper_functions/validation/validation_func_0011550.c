gt_pch_nx_lto_in_decl_state (void *x_p)
{
  struct lto_in_decl_state * const x = (struct lto_in_decl_state *)x_p;
  if (gt_pch_note_object (x, x, gt_pch_p_17lto_in_decl_state))
    {
      {
        size_t i0;
        size_t l0 = (size_t)(LTO_N_DECL_STREAMS);
        for (i0 = 0; i0 != l0; i0++) {
          {
            size_t l1 = (size_t)(((*x).streams[i0]).size);
            if ((*x).streams[i0].trees != NULL) {
              size_t i1;
              for (i1 = 0; i1 != (size_t)(l1); i1++) {
                gt_pch_n_9tree_node ((*x).streams[i0].trees[i1]);
              }
              gt_pch_note_object ((*x).streams[i0].trees, x, gt_pch_p_17lto_in_decl_state);
            }
          }
        }
      }
      gt_pch_n_9tree_node ((*x).fn_decl);
    }
}
