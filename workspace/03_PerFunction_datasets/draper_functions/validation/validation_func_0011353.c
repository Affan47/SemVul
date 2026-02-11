clear_showcmd()
{
    if (!p_sc)
	return;

#ifdef FEAT_VISUAL
    if (VIsual_active && !char_avail())
    {
	int		cursor_bot = lt(VIsual, curwin->w_cursor);
	long		lines;
	colnr_T		leftcol, rightcol;
	linenr_T	top, bot;


	if (cursor_bot)
	{
	    top = VIsual.lnum;
	    bot = curwin->w_cursor.lnum;
	}
	else
	{
	    top = curwin->w_cursor.lnum;
	    bot = VIsual.lnum;
	}
# ifdef FEAT_FOLDING

	hasFolding(top, &top, NULL);
	hasFolding(bot, NULL, &bot);
# endif
	lines = bot - top + 1;

	if (VIsual_mode == Ctrl_V)
	{
# ifdef FEAT_LINEBREAK
	    char_u *saved_sbr = p_sbr;


	    p_sbr = empty_option;
# endif
	    getvcols(curwin, &curwin->w_cursor, &VIsual, &leftcol, &rightcol);
# ifdef FEAT_LINEBREAK
	    p_sbr = saved_sbr;
# endif
	    sprintf((char *)showcmd_buf, "%ldx%ld", lines,
					      (long)(rightcol - leftcol + 1));
	}
	else if (VIsual_mode == 'V' || VIsual.lnum != curwin->w_cursor.lnum)
	    sprintf((char *)showcmd_buf, "%ld", lines);
	else
	{
	    char_u  *s, *e;
	    int	    l;
	    int	    bytes = 0;
	    int	    chars = 0;

	    if (cursor_bot)
	    {
		s = ml_get_pos(&VIsual);
		e = ml_get_cursor();
	    }
	    else
	    {
		s = ml_get_cursor();
		e = ml_get_pos(&VIsual);
	    }
	    while ((*p_sel != 'e') ? s <= e : s < e)
	    {
# ifdef FEAT_MBYTE
		l = (*mb_ptr2len)(s);
# else
		l = (*s == NUL) ? 0 : 1;
# endif
		if (l == 0)
		{
		    ++bytes;
		    ++chars;
		    break;
		}
		bytes += l;
		++chars;
		s += l;
	    }
	    if (bytes == chars)
		sprintf((char *)showcmd_buf, "%d", chars);
	    else
		sprintf((char *)showcmd_buf, "%d-%d", chars, bytes);
	}
	showcmd_buf[SHOWCMD_COLS] = NUL;
	showcmd_visual = TRUE;
    }
    else
#endif
    {
	showcmd_buf[0] = NUL;
	showcmd_visual = FALSE;


	if (showcmd_is_clear)
	    return;
    }

    display_showcmd();
}
