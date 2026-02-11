chm_traverse(chm_config_data_t *chm, cmph_uint8 *visited, cmph_uint32 v)
{

	graph_iterator_t it = graph_neighbors_it(chm->graph, v);
	cmph_uint32 neighbor = 0;
	SETBIT(visited,v);

	DEBUGP("Visiting vertex %u\n", v);
	while((neighbor = graph_next_neighbor(chm->graph, &it)) != GRAPH_NO_NEIGHBOR)
	{
		DEBUGP("Visiting neighbor %u\n", neighbor);
		if(GETBIT(visited,neighbor)) continue;
		DEBUGP("Visiting neighbor %u\n", neighbor);
		DEBUGP("Visiting edge %u->%u with id %u\n", v, neighbor, graph_edge_id(chm->graph, v, neighbor));
		chm->g[neighbor] = graph_edge_id(chm->graph, v, neighbor) - chm->g[v];
		DEBUGP("g is %u (%u - %u mod %u)\n", chm->g[neighbor], graph_edge_id(chm->graph, v, neighbor), chm->g[v], chm->m);
		chm_traverse(chm, visited, neighbor);
	}
}
