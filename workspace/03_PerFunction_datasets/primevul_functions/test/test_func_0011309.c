qf_open_new_file_win(qf_info_T *ll_ref)
{
    int		flags;

    flags = WSP_ABOVE;
    if (ll_ref != NULL)
	flags |= WSP_NEWLOC;
    if (win_split(0, flags) == FAIL)
	return FAIL;
    p_swb = empty_option;
    swb_flags = 0;
    RESET_BINDING(curwin);
    if (ll_ref != NULL)


	win_set_loclist(curwin, ll_ref);
    return OK;
}
