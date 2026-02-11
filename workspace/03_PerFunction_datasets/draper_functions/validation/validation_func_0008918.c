relabel_sources(struct call_graph *graph)
{
	int i = 0;
	int j = 0;


	qsort(graph->edge_from.ptr, graph->edge_from.size,
	      graph->edge_from.elemsize, cmp_branch_by_src);

	while (j < graph->edge_from.size) {
		struct cg_edge *br = CG_EDGE_FROM(graph, j);
		struct cg_node *n;


		while (i + 1 < graph->node_list.size &&
		       CG_NODE(graph, i + 1)->offset <= br->src)
			i++;

		n = CG_NODE(graph, i);
		if (n->offset <= br->src)
			br->src = n->offset;
		j++;
	}
}
