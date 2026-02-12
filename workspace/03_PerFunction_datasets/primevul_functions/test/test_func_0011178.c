ll_get_or_alloc_list(win_T *wp)
{
    if (IS_LL_WINDOW(wp))

	return wp->w_llist_ref;


    ll_free_all(&wp->w_llist_ref);

    if (wp->w_llist == NULL)
	wp->w_llist = qf_alloc_stack(QFLT_LOCATION);
    return wp->w_llist;
}
