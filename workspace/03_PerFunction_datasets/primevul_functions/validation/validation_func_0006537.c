ins_compl_accept_char(int c)
{
    if (ctrl_x_mode & CTRL_X_WANT_IDENT)

	return vim_isIDc(c);

    switch (ctrl_x_mode)
    {
	case CTRL_X_FILES:


	    return vim_isfilec(c) && !vim_ispathsep(c);

	case CTRL_X_CMDLINE:
	case CTRL_X_CMDLINE_CTRL_X:
	case CTRL_X_OMNI:


	    return vim_isprintc(c) && !VIM_ISWHITE(c);

	case CTRL_X_WHOLE_LINE:

	    return vim_isprintc(c);
    }
    return vim_iswordc(c);
}
