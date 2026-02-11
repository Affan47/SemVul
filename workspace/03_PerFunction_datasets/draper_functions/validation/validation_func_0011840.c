do_ordering_node (graph_t * g, node_t* n, int outflag)
{
    int i, ne;
    node_t *u, *v;
    edge_t *e, *f, *fe;
    edge_t **sortlist = TE_list;

    if (ND_clust(n))
	return;
    if (outflag) {
	for (i = ne = 0; (e = ND_out(n).list[i]); i++)
	    if (!betweenclust(e))
		sortlist[ne++] = e;
    } else {
	for (i = ne = 0; (e = ND_in(n).list[i]); i++)
	    if (!betweenclust(e))
		sortlist[ne++] = e;
    }
    if (ne <= 1)
	return;


    sortlist[ne] = 0;
    qsort(sortlist, ne, sizeof(sortlist[0]), (qsort_cmpf) edgeidcmpf);
    for (ne = 1; (f = sortlist[ne]); ne++) {
	e = sortlist[ne - 1];
	if (outflag) {
	    u = aghead(e);
	    v = aghead(f);
	} else {
	    u = agtail(e);
	    v = agtail(f);
	}
	if (find_flat_edge(u, v))
	    return;
	fe = new_virtual_edge(u, v, NULL);
	ED_edge_type(fe) = FLATORDER;
	flat_edge(g, fe);
    }
}
