menu_translate_tab_and_shift(arg_start)
    char_u	*arg_start;
{
    char_u	*arg = arg_start;

    while (*arg && !vim_iswhite(*arg))
    {
	if ((*arg == '\\' || *arg == Ctrl_V) && arg[1] != NUL)
	    arg++;
	else if (STRNICMP(arg, "<TAB>", 5) == 0)
	{
	    *arg = TAB;
	    STRMOVE(arg + 1, arg + 5);
	}
	arg++;
    }
    if (*arg != NUL)
	*arg++ = NUL;
    arg = skipwhite(arg);

    return arg;
}
