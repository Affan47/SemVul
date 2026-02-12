fuzzy_match_in_list(
	list_T		*l,
	char_u		*str,
	int		matchseq,
	char_u		*key,
	callback_T	*item_cb,
	int		retmatchpos,
	list_T		*fmatchlist,
	long		max_matches)
{
    long	len;
    fuzzyItem_T	*items;
    listitem_T	*li;
    long	i = 0;
    long	match_count = 0;
    int_u	matches[MAX_FUZZY_MATCHES];

    len = list_len(l);
    if (len == 0)
	return;
    if (max_matches > 0 && len > max_matches)
	len = max_matches;

    items = ALLOC_CLEAR_MULT(fuzzyItem_T, len);
    if (items == NULL)
	return;


    FOR_ALL_LIST_ITEMS(l, li)
    {
	int		score;
	char_u		*itemstr;
	typval_T	rettv;

	if (max_matches > 0 && match_count >= max_matches)
	    break;

	itemstr = NULL;
	rettv.v_type = VAR_UNKNOWN;
	if (li->li_tv.v_type == VAR_STRING)
	    itemstr = li->li_tv.vval.v_string;
	else if (li->li_tv.v_type == VAR_DICT
				&& (key != NULL || item_cb->cb_name != NULL))
	{


	    if (key != NULL)
		itemstr = dict_get_string(li->li_tv.vval.v_dict, key, FALSE);
	    else
	    {
		typval_T	argv[2];


		li->li_tv.vval.v_dict->dv_refcount++;
		argv[0].v_type = VAR_DICT;
		argv[0].vval.v_dict = li->li_tv.vval.v_dict;
		argv[1].v_type = VAR_UNKNOWN;
		if (call_callback(item_cb, -1, &rettv, 1, argv) != FAIL)
		{
		    if (rettv.v_type == VAR_STRING)
			itemstr = rettv.vval.v_string;
		}
		dict_unref(li->li_tv.vval.v_dict);
	    }
	}

	if (itemstr != NULL
		&& fuzzy_match(itemstr, str, matchseq, &score, matches,
							MAX_FUZZY_MATCHES))
	{
	    items[match_count].idx = match_count;
	    items[match_count].item = li;
	    items[match_count].score = score;


	    if (retmatchpos)
	    {
		int	j = 0;
		char_u	*p;

		items[match_count].lmatchpos = list_alloc();
		if (items[match_count].lmatchpos == NULL)
		    goto done;

		p = str;
		while (*p != NUL)
		{
		    if (!VIM_ISWHITE(PTR2CHAR(p)) || matchseq)
		    {
			if (list_append_number(items[match_count].lmatchpos,
				    matches[j]) == FAIL)
			    goto done;
			j++;
		    }
		    if (has_mbyte)
			MB_PTR_ADV(p);
		    else
			++p;
		}
	    }
	    ++match_count;
	}
	clear_tv(&rettv);
    }

    if (match_count > 0)
    {
	list_T		*retlist;


	qsort((void *)items, (size_t)match_count, sizeof(fuzzyItem_T),
		fuzzy_match_item_compare);


	if (retmatchpos)
	{
	    li = list_find(fmatchlist, 0);
	    if (li == NULL || li->li_tv.vval.v_list == NULL)
		goto done;
	    retlist = li->li_tv.vval.v_list;
	}
	else
	    retlist = fmatchlist;


	for (i = 0; i < match_count; i++)
	{
	    if (items[i].score == SCORE_NONE)
		break;
	    list_append_tv(retlist, &items[i].item->li_tv);
	}


	if (retmatchpos)
	{
	    li = list_find(fmatchlist, -2);
	    if (li == NULL || li->li_tv.vval.v_list == NULL)
		goto done;
	    retlist = li->li_tv.vval.v_list;

	    for (i = 0; i < match_count; i++)
	    {
		if (items[i].score == SCORE_NONE)
		    break;
		if (items[i].lmatchpos != NULL
			&& list_append_list(retlist, items[i].lmatchpos)
								== FAIL)
		    goto done;
	    }


	    li = list_find(fmatchlist, -1);
	    if (li == NULL || li->li_tv.vval.v_list == NULL)
		goto done;
	    retlist = li->li_tv.vval.v_list;
	    for (i = 0; i < match_count; i++)
	    {
		if (items[i].score == SCORE_NONE)
		    break;
		if (list_append_number(retlist, items[i].score) == FAIL)
		    goto done;
	    }
	}
    }

done:
    vim_free(items);
}
