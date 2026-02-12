cmdline_paste_reg(
    int regname,
    int literally_arg,
    int remcr)
{
    long	i;
    int		literally = literally_arg;

    if (get_yank_register(regname, FALSE))
	literally = TRUE;
    if (y_current->y_array == NULL)
	return FAIL;

    for (i = 0; i < y_current->y_size; ++i)
    {
	cmdline_paste_str(y_current->y_array[i], literally);


	if ((y_current->y_type == MLINE || i < y_current->y_size - 1) && !remcr)
	    cmdline_paste_str((char_u *)"\r", literally);


	ui_breakcheck();
	if (got_int)
	    return FAIL;
    }
    return OK;
}
