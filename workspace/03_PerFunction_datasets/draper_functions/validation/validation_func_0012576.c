f_sort(argvars, rettv)
    typval_T	*argvars;
    typval_T	*rettv;
{
    list_T	*l;
    listitem_T	*li;
    listitem_T	**ptrs;
    long	len;
    long	i;

    if (argvars[0].v_type != VAR_LIST)
	EMSG2(_(e_listarg), "sort()");
    else
    {
	l = argvars[0].vval.v_list;
	if (l == NULL || tv_check_lock(l->lv_lock,
					     (char_u *)_("sort() argument")))
	    return;
	rettv->vval.v_list = l;
	rettv->v_type = VAR_LIST;
	++l->lv_refcount;

	len = list_len(l);
	if (len <= 1)
	    return;

	item_compare_ic = FALSE;
	item_compare_func = NULL;
	item_compare_selfdict = NULL;
	if (argvars[1].v_type != VAR_UNKNOWN)
	{

	    if (argvars[1].v_type == VAR_FUNC)
		item_compare_func = argvars[1].vval.v_string;
	    else
	    {
		int	    error = FALSE;

		i = get_tv_number_chk(&argvars[1], &error);
		if (error)
		    return;
		if (i == 1)
		    item_compare_ic = TRUE;
		else
		    item_compare_func = get_tv_string(&argvars[1]);
	    }

	    if (argvars[2].v_type != VAR_UNKNOWN)
	    {

		if (argvars[2].v_type != VAR_DICT)
		{
		    EMSG(_(e_dictreq));
		    return;
		}
		item_compare_selfdict = argvars[2].vval.v_dict;
	    }
	}


	ptrs = (listitem_T **)alloc((int)(len * sizeof(listitem_T *)));
	if (ptrs == NULL)
	    return;
	i = 0;
	for (li = l->lv_first; li != NULL; li = li->li_next)
	    ptrs[i++] = li;

	item_compare_func_err = FALSE;

	if (item_compare_func != NULL
		&& item_compare2((void *)&ptrs[0], (void *)&ptrs[1])
							 == ITEM_COMPARE_FAIL)
	    EMSG(_("E702: Sort compare function failed"));
	else
	{

	    qsort((void *)ptrs, (size_t)len, sizeof(listitem_T *),
		    item_compare_func == NULL ? item_compare : item_compare2);

	    if (!item_compare_func_err)
	    {

		l->lv_first = l->lv_last = l->lv_idx_item = NULL;
		l->lv_len = 0;
		for (i = 0; i < len; ++i)
		    list_append(l, ptrs[i]);
	    }
	}

	vim_free(ptrs);
    }
}
