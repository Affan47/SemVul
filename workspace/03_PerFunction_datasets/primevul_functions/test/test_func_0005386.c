insert_reg(
    int		regname,
    int		literally_arg)
{
    long	i;
    int		retval = OK;
    char_u	*arg;
    int		allocated;
    int		literally = literally_arg;


    ui_breakcheck();
    if (got_int)
	return FAIL;


    if (regname != NUL && !valid_yank_reg(regname, FALSE))
	return FAIL;

#ifdef FEAT_CLIPBOARD
    regname = may_get_selection(regname);
#endif

    if (regname == '.')
	retval = stuff_inserted(NUL, 1L, TRUE);
    else if (get_spec_reg(regname, &arg, &allocated, TRUE))
    {
	if (arg == NULL)
	    return FAIL;
	stuffescaped(arg, literally);
	if (allocated)
	    vim_free(arg);
    }
    else
    {
	if (get_yank_register(regname, FALSE))
	    literally = TRUE;
	if (y_current->y_array == NULL)
	    retval = FAIL;
	else
	{
	    for (i = 0; i < y_current->y_size; ++i)
	    {
		if (regname == '-')
		{
		    AppendCharToRedobuff(Ctrl_R);
		    AppendCharToRedobuff(regname);
		    do_put(regname, NULL, BACKWARD, 1L, PUT_CURSEND);
		}
		else
		    stuffescaped(y_current->y_array[i], literally);


		if (y_current->y_type == MLINE || i < y_current->y_size - 1)
		    stuffcharReadbuff('\n');
	    }
	}
    }

    return retval;
}
