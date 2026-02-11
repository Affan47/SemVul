create_loop_tree_node_allocnos (ira_loop_tree_node_t loop_node)
{
  if (loop_node->bb != NULL)
    create_bb_allocnos (loop_node);
  else if (loop_node != ira_loop_tree_root)
    {
      int i;
      edge_iterator ei;
      edge e;
      VEC (edge, heap) *edges;

      ira_assert (current_loops != NULL);
      FOR_EACH_EDGE (e, ei, loop_node->loop->header->preds)
	if (e->src != loop_node->loop->latch)
	  create_loop_allocnos (e);

      edges = get_loop_exit_edges (loop_node->loop);
      FOR_EACH_VEC_ELT (edge, edges, i, e)
	create_loop_allocnos (e);
      VEC_free (edge, heap, edges);
    }
}
