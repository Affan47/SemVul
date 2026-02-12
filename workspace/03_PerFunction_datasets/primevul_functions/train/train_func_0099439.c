msg_puts_display(
    char_u	*str,
    int		maxlen,
    int		attr,
    int		recurse)
{
    char_u	*s = str;
    char_u	*t_s = str;
    int		t_col = 0;
    int		l;
    int		cw;
    char_u	*sb_str = str;
    int		sb_col = msg_col;
    int		wrap;
    int		did_last_char;

    did_wait_return = FALSE;
    while ((maxlen < 0 || (int)(s - str) < maxlen) && *s != NUL)
    {


	if (!recurse && msg_row >= Rows - 1 && (*s == '\n' || (
#ifdef FEAT_RIGHTLEFT
		    cmdmsg_rl
		    ? (
			msg_col <= 1
		      || (*s == TAB && msg_col <= 7)
		      || (has_mbyte && (*mb_ptr2cells)(s) > 1 && msg_col <= 2))
		    :
#endif
		      ((*s != '\r' && msg_col + t_col >= Columns - 1)
		       || (*s == TAB && msg_col + t_col >= ((Columns - 1) & ~7))
		       || (has_mbyte && (*mb_ptr2cells)(s) > 1
					 && msg_col + t_col >= Columns - 2)))))
	{


	    if (t_col > 0)

		t_puts(&t_col, t_s, s, attr);


	    if (msg_no_more && lines_left == 0)
		break;


	    msg_scroll_up();

	    msg_row = Rows - 2;
	    if (msg_col >= Columns)
		msg_col = Columns - 1;


	    if (*s >= ' '
#ifdef FEAT_RIGHTLEFT
		    && !cmdmsg_rl
#endif
	       )
	    {
		if (has_mbyte)
		{
		    if (enc_utf8 && maxlen >= 0)

			l = utfc_ptr2len_len(s, (int)((str + maxlen) - s));
		    else
			l = (*mb_ptr2len)(s);
		    s = screen_puts_mbyte(s, l, attr);
		}
		else
		    msg_screen_putchar(*s++, attr);
		did_last_char = TRUE;
	    }
	    else
		did_last_char = FALSE;

	    if (p_more)

		store_sb_text(&sb_str, s, attr, &sb_col, TRUE);

	    inc_msg_scrolled();
	    need_wait_return = TRUE;
	    redraw_cmdline = TRUE;
	    if (cmdline_row > 0 && !exmode_active)
		--cmdline_row;


	    if (lines_left > 0)
		--lines_left;
	    if (p_more && lines_left == 0 && State != MODE_HITRETURN
					    && !msg_no_more && !exmode_active)
	    {
#ifdef FEAT_CON_DIALOG
		if (do_more_prompt(NUL))
		    s = confirm_msg_tail;
#else
		(void)do_more_prompt(NUL);
#endif
		if (quit_more)
		    return;
	    }


	    if (did_last_char)
		continue;
	}

	wrap = *s == '\n'
		    || msg_col + t_col >= Columns
		    || (has_mbyte && (*mb_ptr2cells)(s) > 1
					    && msg_col + t_col >= Columns - 1);
	if (t_col > 0 && (wrap || *s == '\r' || *s == '\b'
						 || *s == '\t' || *s == BELL))

	    t_puts(&t_col, t_s, s, attr);

	if (wrap && p_more && !recurse)

	    store_sb_text(&sb_str, s, attr, &sb_col, TRUE);

	if (*s == '\n')
	{
	    msg_didout = FALSE;
#ifdef FEAT_RIGHTLEFT
	    if (cmdmsg_rl)
		msg_col = Columns - 1;
	    else
#endif
		msg_col = 0;
	    if (++msg_row >= Rows)
		msg_row = Rows - 1;
	}
	else if (*s == '\r')
	{
	    msg_col = 0;
	}
	else if (*s == '\b')
	{
	    if (msg_col)
		--msg_col;
	}
	else if (*s == TAB)
	{
	    do
		msg_screen_putchar(' ', attr);
	    while (msg_col & 7);
	}
	else if (*s == BELL)
	    vim_beep(BO_SH);
	else
	{
	    if (has_mbyte)
	    {
		cw = (*mb_ptr2cells)(s);
		if (enc_utf8 && maxlen >= 0)

		    l = utfc_ptr2len_len(s, (int)((str + maxlen) - s));
		else
		    l = (*mb_ptr2len)(s);
	    }
	    else
	    {
		cw = 1;
		l = 1;
	    }


	    if (
# ifdef FEAT_RIGHTLEFT
		    cmdmsg_rl ||
# endif
		    (cw > 1 && msg_col + t_col >= Columns - 1))
	    {
		if (l > 1)
		    s = screen_puts_mbyte(s, l, attr) - 1;
		else
		    msg_screen_putchar(*s, attr);
	    }
	    else
	    {

		if (t_col == 0)
		    t_s = s;
		t_col += cw;
		s += l - 1;
	    }
	}
	++s;
    }


    if (t_col > 0)
	t_puts(&t_col, t_s, s, attr);
    if (p_more && !recurse)
	store_sb_text(&sb_str, s, attr, &sb_col, FALSE);

    msg_check();
}
