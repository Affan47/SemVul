ex_args(exarg_T *eap)
{
    int		i;

    if (eap->cmdidx != CMD_args)
    {
	if (check_arglist_locked() == FAIL)
	    return;
	alist_unlink(ALIST(curwin));
	if (eap->cmdidx == CMD_argglobal)
	    ALIST(curwin) = &global_alist;
	else
	    alist_new();
    }

    if (*eap->arg != NUL)
    {
	if (check_arglist_locked() == FAIL)
	    return;


	ex_next(eap);
    }
    else if (eap->cmdidx == CMD_args)
    {

	if (ARGCOUNT > 0)
	{
	    char_u **items = ALLOC_MULT(char_u *, ARGCOUNT);

	    if (items != NULL)
	    {


		gotocmdline(TRUE);

		for (i = 0; i < ARGCOUNT; ++i)
		    items[i] = alist_name(&ARGLIST[i]);
		list_in_columns(items, ARGCOUNT, curwin->w_arg_idx);
		vim_free(items);
	    }
	}
    }
    else if (eap->cmdidx == CMD_arglocal)
    {
	garray_T	*gap = &curwin->w_alist->al_ga;


	if (GA_GROW_OK(gap, GARGCOUNT))
	    for (i = 0; i < GARGCOUNT; ++i)
		if (GARGLIST[i].ae_fname != NULL)
		{
		    AARGLIST(curwin->w_alist)[gap->ga_len].ae_fname =
					    vim_strsave(GARGLIST[i].ae_fname);
		    AARGLIST(curwin->w_alist)[gap->ga_len].ae_fnum =
							  GARGLIST[i].ae_fnum;
		    ++gap->ga_len;
		}
    }
}
