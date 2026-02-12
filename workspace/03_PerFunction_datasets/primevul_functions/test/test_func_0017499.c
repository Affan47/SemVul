del_termcode(char_u *name)
{
    int	    i;

    if (termcodes == NULL)
	return;

    need_gather = TRUE;

    for (i = 0; i < tc_len; ++i)
	if (termcodes[i].name[0] == name[0] && termcodes[i].name[1] == name[1])
	{
	    del_termcode_idx(i);
	    return;
	}

}
