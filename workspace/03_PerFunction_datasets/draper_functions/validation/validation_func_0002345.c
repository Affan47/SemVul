resetGraph(tgraph * g, int ncnt, int ecnt)
{
    int i;
    tnode *np = g->nodes;
    g->nedges = ecnt;
    for (i = 0; i < ncnt; i++) {
	if (np->edges + np->ne == (np + 1)->edges)
	    np->ne--;
	np++;
    }
}
