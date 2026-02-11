_validate_node_choice(slurmctld_resv_t *resv_ptr)
{
	bitstr_t *tmp_bitmap = NULL;
	bitstr_t *core_bitmap = NULL;
	int i;
	resv_desc_msg_t resv_desc;

	if (resv_ptr->flags & RESERVE_FLAG_SPEC_NODES ||
	    resv_ptr->flags & RESERVE_FLAG_STATIC)
		return;

	i = bit_overlap(resv_ptr->node_bitmap, avail_node_bitmap);
	if (i == resv_ptr->node_cnt)
		return;


	memset(&resv_desc, 0, sizeof(resv_desc_msg_t));
	resv_desc.start_time = resv_ptr->start_time;
	resv_desc.end_time   = resv_ptr->end_time;
	resv_desc.features   = resv_ptr->features;
	resv_desc.node_cnt   = xmalloc(sizeof(uint32_t) * 2);
	resv_desc.node_cnt[0]= resv_ptr->node_cnt - i;
	i = _select_nodes(&resv_desc, &resv_ptr->part_ptr, &tmp_bitmap,
			  &core_bitmap);
	xfree(resv_desc.node_cnt);
	xfree(resv_desc.node_list);
	xfree(resv_desc.partition);
	if (i == SLURM_SUCCESS) {
		bit_and(resv_ptr->node_bitmap, avail_node_bitmap);
		bit_or(resv_ptr->node_bitmap, tmp_bitmap);
		FREE_NULL_BITMAP(tmp_bitmap);
		FREE_NULL_BITMAP(resv_ptr->core_bitmap);
		resv_ptr->core_bitmap = core_bitmap;
		xfree(resv_ptr->node_list);
		resv_ptr->node_list = bitmap2node_name(resv_ptr->node_bitmap);
		info("modified reservation %s due to unusable nodes, "
		     "new nodes: %s", resv_ptr->name, resv_ptr->node_list);
	} else if (difftime(resv_ptr->start_time, time(NULL)) < 600) {
		info("reservation %s contains unusable nodes, "
		     "can't reallocate now", resv_ptr->name);
	} else {
		debug("reservation %s contains unusable nodes, "
		      "can't reallocate now", resv_ptr->name);
	}
}
