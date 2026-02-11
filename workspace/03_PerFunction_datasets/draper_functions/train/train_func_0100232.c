rs_start_results(void* vparams,
							 kdtree_t* ytree, int ynode) {
	rs_params* p = (rs_params*)vparams;
	p->ydone += 1 + kdtree_right(ytree, ynode) - kdtree_left(ytree, ynode);
	if (p->user_progress)
		p->user_progress(p->user_progress_param, p->ydone);
}
