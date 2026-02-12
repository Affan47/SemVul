redrawcmd(void)
{
    int save_in_echowindow = in_echowindow;

    if (cmd_silent)
	return;


    if (ccline.cmdbuff == NULL)
    {
	windgoto(cmdline_row, 0);
	msg_clr_eos();
	return;
    }


    in_echowindow = FALSE;

    sb_text_restart_cmdline();
    msg_start();
    redrawcmdprompt();


    msg_no_more = TRUE;
    draw_cmdline(0, ccline.cmdlen);
    msg_clr_eos();
    msg_no_more = FALSE;

    set_cmdspos_cursor();
    if (extra_char != NUL)
	putcmdline(extra_char, extra_char_shift);


    msg_scroll = FALSE;


    skip_redraw = FALSE;

    in_echowindow = save_in_echowindow;
}
