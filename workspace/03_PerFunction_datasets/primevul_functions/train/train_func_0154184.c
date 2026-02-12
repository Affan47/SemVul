void i40e_fdir_check_and_reenable(struct i40e_pf *pf)
{
	struct i40e_fdir_filter *filter;
	u32 fcnt_prog, fcnt_avail;
	struct hlist_node *node;

	if (test_bit(__I40E_FD_FLUSH_REQUESTED, pf->state))
		return;


	fcnt_prog = i40e_get_global_fd_count(pf);
	fcnt_avail = pf->fdir_pf_filter_count;
	if ((fcnt_prog < (fcnt_avail - I40E_FDIR_BUFFER_HEAD_ROOM)) ||
	    (pf->fd_add_err == 0) ||
	    (i40e_get_current_atr_cnt(pf) < pf->fd_atr_cnt))
		i40e_reenable_fdir_sb(pf);


	if ((fcnt_prog < (fcnt_avail - I40E_FDIR_BUFFER_HEAD_ROOM_FOR_ATR)) &&
	    (pf->fd_tcp4_filter_cnt == 0))
		i40e_reenable_fdir_atr(pf);


	if (pf->fd_inv > 0) {
		hlist_for_each_entry_safe(filter, node,
					  &pf->fdir_filter_list, fdir_node)
			if (filter->fd_id == pf->fd_inv)
				i40e_delete_invalid_filter(pf, filter);
	}
}
