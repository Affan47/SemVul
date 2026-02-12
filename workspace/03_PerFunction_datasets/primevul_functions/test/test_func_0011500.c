nv_bracket_block(cmdarg_T *cap, pos_T *old_pos)
{
    pos_T	new_pos = {0, 0, 0};
    pos_T	*pos = NULL;
    pos_T	prev_pos;
    long	n;
    int		findc;
    int		c;

    if (cap->nchar == '*')
	cap->nchar = '/';
    prev_pos.lnum = 0;
    if (cap->nchar == 'm' || cap->nchar == 'M')
    {
	if (cap->cmdchar == '[')
	    findc = '{';
	else
	    findc = '}';
	n = 9999;
    }
    else
    {
	findc = cap->nchar;
	n = cap->count1;
    }
    for ( ; n > 0; --n)
    {
	if ((pos = findmatchlimit(cap->oap, findc,
			(cap->cmdchar == '[') ? FM_BACKWARD : FM_FORWARD, 0)) == NULL)
	{
	    if (new_pos.lnum == 0)
	    {
		if (cap->nchar != 'm' && cap->nchar != 'M')
		    clearopbeep(cap->oap);
	    }
	    else
		pos = &new_pos;
	    break;
	}
	prev_pos = new_pos;
	curwin->w_cursor = *pos;
	new_pos = *pos;
    }
    curwin->w_cursor = *old_pos;

    if (cap->nchar == 'm' || cap->nchar == 'M')
    {

	int	    norm = ((findc == '{') == (cap->nchar == 'm'));

	n = cap->count1;

	if (prev_pos.lnum != 0)
	{
	    pos = &prev_pos;
	    curwin->w_cursor = prev_pos;
	    if (norm)
		--n;
	}
	else
	    pos = NULL;
	while (n > 0)
	{
	    for (;;)
	    {
		if ((findc == '{' ? dec_cursor() : inc_cursor()) < 0)
		{

		    if (pos == NULL)
			clearopbeep(cap->oap);
		    n = 0;
		    break;
		}
		c = gchar_cursor();
		if (c == '{' || c == '}')
		{

		    if ((c == findc && norm) || (n == 1 && !norm))
		    {
			new_pos = curwin->w_cursor;
			pos = &new_pos;
			n = 0;
		    }

		    else if (new_pos.lnum == 0)
		    {
			new_pos = curwin->w_cursor;
			pos = &new_pos;
		    }

		    else if ((pos = findmatchlimit(cap->oap, findc,
			      (cap->cmdchar == '[') ? FM_BACKWARD : FM_FORWARD,
								   0)) == NULL)
			n = 0;
		    else
			curwin->w_cursor = *pos;
		    break;
		}
	    }
	    --n;
	}
	curwin->w_cursor = *old_pos;
	if (pos == NULL && new_pos.lnum != 0)
	    clearopbeep(cap->oap);
    }
    if (pos != NULL)
    {
	setpcmark();
	curwin->w_cursor = *pos;
	curwin->w_set_curswant = TRUE;
#ifdef FEAT_FOLDING
	if ((fdo_flags & FDO_BLOCK) && KeyTyped
		&& cap->oap->op_type == OP_NOP)
	    foldOpenCursor();
#endif
    }
}
}
}
