qf_current_entry(win_T *wp)
{
    qf_info_T	*qi = &ql_info;

    if (IS_LL_WINDOW(wp))

	qi = wp->w_llist_ref;

    return qf_get_curlist(qi)->qf_index;
}
