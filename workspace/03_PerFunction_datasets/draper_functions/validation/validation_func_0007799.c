build_cg_bitmap(struct job_record *job_ptr)
{
	FREE_NULL_BITMAP(job_ptr->node_bitmap_cg);
	if (job_ptr->node_bitmap) {
		job_ptr->node_bitmap_cg = bit_copy(job_ptr->node_bitmap);
		if (bit_set_count(job_ptr->node_bitmap_cg) == 0)
			job_ptr->job_state &= (~JOB_COMPLETING);
	} else {
		error("build_cg_bitmap: node_bitmap is NULL");
		job_ptr->node_bitmap_cg = bit_alloc(node_record_count);
		job_ptr->job_state &= (~JOB_COMPLETING);
	}
}
