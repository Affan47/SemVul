dot_init_node_edge(graph_t * g)
{
    node_t *n;
    edge_t *e;

    initGraph (g);
    for (n = agfstnode(g); n; n = agnxtnode(g, n))
	dot_init_node(n);
    for (n = agfstnode(g); n; n = agnxtnode(g, n)) {
	for (e = agfstout(g, n); e; e = agnxtout(g, e))
	    dot_init_edge(e);
    }
}
