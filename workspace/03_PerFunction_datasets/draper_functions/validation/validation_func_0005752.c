do_unlet_var(lp, name_end, forceit)
    lval_T	*lp;
    char_u	*name_end;
    int		forceit;
{
    int		ret = OK;
    int		cc;

    if (lp->ll_tv == NULL)
    {
	cc = *name_end;
	*name_end = NUL;


	if (check_changedtick(lp->ll_name))
	    ret = FAIL;
	else if (do_unlet(lp->ll_name, forceit) == FAIL)
	    ret = FAIL;
	*name_end = cc;
    }
    else if (tv_check_lock(lp->ll_tv->v_lock, lp->ll_name))
	return FAIL;
    else if (lp->ll_range)
    {
	listitem_T    *li;


	while (lp->ll_li != NULL && (lp->ll_empty2 || lp->ll_n2 >= lp->ll_n1))
	{
	    li = lp->ll_li->li_next;
	    listitem_remove(lp->ll_list, lp->ll_li);
	    lp->ll_li = li;
	    ++lp->ll_n1;
	}
    }
    else
    {
	if (lp->ll_list != NULL)

	    listitem_remove(lp->ll_list, lp->ll_li);
	else

	    dictitem_remove(lp->ll_dict, lp->ll_di);
    }

    return ret;
}
