get_reg_type(int regname, long *reglen)
{
    switch (regname)
    {
	case '%':
	case '#':
	case '=':
	case ':':
	case '/':
	case '.':
# ifdef FEAT_SEARCHPATH
	case Ctrl_F:
	case Ctrl_P:
# endif
	case Ctrl_W:
	case Ctrl_A:
	case '_':
	    return MCHAR;
    }

# ifdef FEAT_CLIPBOARD
    regname = may_get_selection(regname);
# endif

    if (regname != NUL && !valid_yank_reg(regname, FALSE))
	return MAUTO;

    get_yank_register(regname, FALSE);

    if (y_current->y_array != NULL)
    {
	if (reglen != NULL && y_current->y_type == MBLOCK)
	    *reglen = y_current->y_width;
	return y_current->y_type;
    }
    return MAUTO;
}
