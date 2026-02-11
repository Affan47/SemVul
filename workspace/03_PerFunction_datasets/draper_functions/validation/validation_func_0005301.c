maximalize_clique(set_t s,graph_t *g) {
	int i,j;
	boolean add;

	for (i=0; i < g->n; i++) {
		add=TRUE;
		for (j=0; j < g->n; j++) {
			if (SET_CONTAINS_FAST(s,j) && !GRAPH_IS_EDGE(g,i,j)) {
				add=FALSE;
				break;
			}
		}
		if (add) {
			SET_ADD_ELEMENT(s,i);
		}
	}
	return;
}
