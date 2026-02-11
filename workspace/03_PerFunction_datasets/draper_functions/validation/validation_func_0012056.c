eval_to_string(arg, nextcmd, convert)
    char_u	*arg;
    char_u	**nextcmd;
    int		convert;
{
    typval_T	tv;
    char_u	*retval;
    garray_T	ga;
#ifdef FEAT_FLOAT
    char_u	numbuf[NUMBUFLEN];
#endif

    if (eval0(arg, &tv, nextcmd, TRUE) == FAIL)
	retval = NULL;
    else
    {
	if (convert && tv.v_type == VAR_LIST)
	{
	    ga_init2(&ga, (int)sizeof(char), 80);
	    if (tv.vval.v_list != NULL)
		list_join(&ga, tv.vval.v_list, (char_u *)"\n", TRUE, 0);
	    ga_append(&ga, NUL);
	    retval = (char_u *)ga.ga_data;
	}
#ifdef FEAT_FLOAT
	else if (convert && tv.v_type == VAR_FLOAT)
	{
	    vim_snprintf((char *)numbuf, NUMBUFLEN, "%g", tv.vval.v_float);
	    retval = vim_strsave(numbuf);
	}
#endif
	else
	    retval = vim_strsave(get_tv_string(&tv));
	clear_tv(&tv);
    }

    return retval;
}
