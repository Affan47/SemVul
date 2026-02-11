resetRW (graph_t * g)
{
    node_t* n;

    for (n = agfstnode(g); n; n = agnxtnode(g,n)) {
	if (ND_other(n).list) {
	    double tmp = ND_rw(n);
	    ND_rw(n) = ND_mval(n);
	    ND_mval(n) = tmp;
	}
    }
}
