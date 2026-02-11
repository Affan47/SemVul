do_ordering_for_nodes(graph_t * g)
{

    node_t *n;
    const char *ordering;

    for (n = agfstnode(g); n; n = agnxtnode(g, n)) {
	if ((ordering = late_string(n, N_ordering, NULL))) {
	    if (streq(ordering, "out"))
		do_ordering_node(g, n, TRUE);
	    else if (streq(ordering, "in"))
		do_ordering_node(g, n, FALSE);
	    else if (ordering[0])
		agerr(AGERR, "ordering '%s' not recognized for node '%s'.\n", ordering, agnameof(n));
	}
    }
}
