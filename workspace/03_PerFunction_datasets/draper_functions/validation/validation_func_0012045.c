decode_mc_coords (unsigned max_state, wfa_t *wfa, bitfile_t *input)


{
   unsigned	       label;
   unsigned	       state;
   mv_t		      *mv;
   static huff_node_t *huff_mv_root = NULL;

   if (huff_mv_root == NULL)
      huff_mv_root = create_huff_tree ();

   for (state = wfa->basis_states; state < max_state; state++)
      for (label = 0; label < MAXLABELS; label++)
      {
	 mv = &wfa->mv_tree[state][label];
	 switch (mv->type)
	 {
	    case NONE:
	       break;
	    case FORWARD:
	       mv->fx = get_mv (1, huff_mv_root, input);
	       mv->fy = get_mv (1, huff_mv_root, input);
	       break;
	    case BACKWARD:
	       mv->bx = get_mv (1, huff_mv_root, input);
	       mv->by = get_mv (1, huff_mv_root, input);
	       break;
	    case INTERPOLATED:
	       mv->fx = get_mv (1, huff_mv_root, input);
	       mv->fy = get_mv (1, huff_mv_root, input);
	       mv->bx = get_mv (1, huff_mv_root, input);
	       mv->by = get_mv (1, huff_mv_root, input);
	       break;
	 }
      }

   INPUT_BYTE_ALIGN (input);
}
