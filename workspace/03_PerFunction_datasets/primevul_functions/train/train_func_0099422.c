msg_start(void)
{
    int		did_return = FALSE;

    if (!msg_silent)
    {
	VIM_CLEAR(keep_msg);
	need_fileinfo = FALSE;
    }

#ifdef FEAT_EVAL
    if (need_clr_eos)
    {


	need_clr_eos = FALSE;
	msg_clr_eos();
    }
#endif

    if (!msg_scroll && full_screen)
    {
	msg_row = cmdline_row;
	msg_col =
#ifdef FEAT_RIGHTLEFT
	    cmdmsg_rl ? Columns - 1 :
#endif
	    0;
    }
    else if (msg_didout)
    {
	msg_putchar('\n');
	did_return = TRUE;
	if (exmode_active != EXMODE_NORMAL)
	    cmdline_row = msg_row;
    }
    if (!msg_didany || lines_left < 0)
	msg_starthere();
    if (msg_silent == 0)
    {
	msg_didout = FALSE;
	cursor_off();
    }


    if (!did_return)
	redir_write((char_u *)"\n", -1);
}
