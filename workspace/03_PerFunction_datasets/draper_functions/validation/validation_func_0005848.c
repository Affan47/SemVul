topo_sort(sample_producer *node, GList **order) {
  if (g_list_find(*order, (gpointer)node))
    return;
  else {
    sample_producer **children;
    for (children = node->get_children(node);
	 *children;
	 children++) {
      topo_sort(*children, order);
    }
    *order = g_list_append(*order, (gpointer)node);
  }
}
