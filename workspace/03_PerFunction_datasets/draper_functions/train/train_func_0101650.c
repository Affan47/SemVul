common_neighbors(vtx_data * graph, int v, int u, int *v_vector)
{

    int neighbor;
    int num_shared_neighbors = 0;
    int j;
    for (j = 1; j < graph[u].nedges; j++) {
	neighbor = graph[u].edges[j];
	if (v_vector[neighbor] > 0) {

	    num_shared_neighbors++;
	}
    }
    return num_shared_neighbors;
}
