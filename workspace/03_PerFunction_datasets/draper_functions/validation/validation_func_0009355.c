good_nodes_from_inx(cluster_nodes_t *cnodes, char *node_inx, int submit)
{
	bitstr_t *job_bitmap = NULL;

	if (! cnodes)
		return 1;

	if(!node_inx || !node_inx[0])
		return 0;

	if(!cnodes->curr_cluster ||
	   (submit < (cnodes->curr_cluster)->start) ||
	   (submit > (cnodes->curr_cluster)->end)) {
		local_cluster_t *local_cluster = NULL;
		ListIterator itr =
			list_iterator_create(cnodes->cluster_list);
		while((local_cluster = list_next(itr))) {
			if((submit >= local_cluster->start)
			   && (submit <= local_cluster->end)) {
				cnodes->curr_cluster = local_cluster;
				break;
			}
		}
		list_iterator_destroy(itr);
		if (! local_cluster)
			return 0;
	}
	job_bitmap = bit_alloc(hostlist_count((cnodes->curr_cluster)->hl));
	bit_unfmt(job_bitmap, node_inx);
	if(!bit_overlap((cnodes->curr_cluster)->asked_bitmap, job_bitmap)) {
		FREE_NULL_BITMAP(job_bitmap);
		return 0;
	}
	FREE_NULL_BITMAP(job_bitmap);
	return 1;
}
