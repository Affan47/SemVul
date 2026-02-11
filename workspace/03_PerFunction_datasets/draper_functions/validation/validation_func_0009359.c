current_tail(struct gfs2_sbd *sdp)
{
	struct gfs2_trans *tr;
	unsigned int tail;

	spin_lock(&sdp->sd_ail_lock);

	if (list_empty(&sdp->sd_ail1_list)) {
		tail = sdp->sd_log_head;
	} else {
		tr = list_entry(sdp->sd_ail1_list.prev, struct gfs2_trans,
				tr_list);
		tail = tr->tr_first;
	}

	spin_unlock(&sdp->sd_ail_lock);

	return tail;
}
