update_arrays(graph_t * G, int nG, int i)
{
    int j, k;
    double del[MAXDIM], dist, old;
    node_t *vi, *vj;

    vi = GD_neato_nlist(G)[i];
    for (k = 0; k < Ndim; k++)
	GD_sum_t(G)[i][k] = 0.0;
    for (j = 0; j < nG; j++) {
	if (i == j)
	    continue;
	vj = GD_neato_nlist(G)[j];
	dist = distvec(ND_pos(vi), ND_pos(vj), del);
	for (k = 0; k < Ndim; k++) {
	    old = GD_t(G)[i][j][k];
	    GD_t(G)[i][j][k] =
		GD_spring(G)[i][j] * (del[k] -
				      GD_dist(G)[i][j] * del[k] / dist);
	    GD_sum_t(G)[i][k] += GD_t(G)[i][j][k];
	    old = GD_t(G)[j][i][k];
	    GD_t(G)[j][i][k] = -GD_t(G)[i][j][k];
	    GD_sum_t(G)[j][k] += (GD_t(G)[j][i][k] - old);
	}
    }
}
