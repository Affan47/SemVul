vgr_qflist_valid(
	win_T	    *wp,
	qf_info_T   *qi,
	int_u	    qfid,
	char_u	    *title)
{

    if (!qflist_valid(wp, qfid))
    {
	if (wp != NULL)
	{

	    emsg(_(e_current_location_list_was_changed));
	    return FALSE;
	}
	else
	{

	    qf_new_list(qi, title);
	    return TRUE;
	}
    }

    if (qf_restore_list(qi, qfid) == FAIL)
	return FALSE;

    return TRUE;
}
