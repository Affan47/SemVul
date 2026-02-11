eval_to_string(arg, nextcmd, dolist)
    char_u	*arg;
    char_u	**nextcmd;
    int		dolist;
{
    typval_T	tv;
    char_u	*retval;
    garray_T	ga;

    if (eval0(arg, &tv, nextcmd, TRUE) == FAIL)
	retval = NULL;
    else
    {
	if (dolist && tv.v_type == VAR_LIST)
	{
	    ga_init2(&ga, (int)sizeof(char), 80);
	    if (tv.vval.v_list != NULL)
		list_join(&ga, tv.vval.v_list, (char_u *)"\n", TRUE, 0);
	    ga_append(&ga, NUL);
	    retval = (char_u *)ga.ga_data;
	}
	else
	    retval = vim_strsave(get_tv_string(&tv));
	clear_tv(&tv);
    }

    return retval;
}
