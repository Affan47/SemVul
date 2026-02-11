clear_edges_for_node (constraint_graph_t graph, unsigned int node)
{
  if (graph->succs[node])
    BITMAP_FREE (graph->succs[node]);
}
