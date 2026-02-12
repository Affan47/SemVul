qf_free_stack(win_T *wp, qf_info_T *qi)
{
    win_T	*qfwin = qf_find_win(qi);
    win_T	*llwin = NULL;

    if (qfwin != NULL)
    {

	if (qi->qf_curlist < qi->qf_listcount)
	    qf_free(qf_get_curlist(qi));
	qf_update_buffer(qi, NULL);
    }

    if (wp != NULL && IS_LL_WINDOW(wp))
    {


	llwin = qf_find_win_with_loclist(qi);
	if (llwin != NULL)
	    wp = llwin;
    }

    qf_free_all(wp);
    if (wp == NULL)
    {

	qi->qf_curlist = 0;
	qi->qf_listcount = 0;
    }
    else if (qfwin != NULL)
    {


	qf_info_T *new_ll = qf_alloc_stack(QFLT_LOCATION);

	if (new_ll != NULL)
	{
	    new_ll->qf_bufnr = qfwin->w_buffer->b_fnum;


	    ll_free_all(&qfwin->w_llist_ref);

	    qfwin->w_llist_ref = new_ll;
	    if (wp != qfwin)
		win_set_loclist(wp, new_ll);
	}
    }
}
