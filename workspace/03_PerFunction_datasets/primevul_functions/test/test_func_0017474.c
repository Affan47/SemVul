check_terminal_behavior(void)
{
    int	    did_send = FALSE;

    if (!can_get_termresponse() || starting != 0 || *T_U7 == NUL)
	return;

    if (u7_status.tr_progress == STATUS_GET
	    && !option_was_set((char_u *)"ambiwidth"))
    {
	char_u	buf[16];


	MAY_WANT_TO_LOG_THIS;
	LOG_TR(("Sending request for ambiwidth check"));


	term_windgoto(1, 0);
	buf[mb_char2bytes(0x25bd, buf)] = NUL;
	out_str(buf);
	out_str(T_U7);
	termrequest_sent(&u7_status);
	out_flush();
	did_send = TRUE;


	screen_stop_highlight();
	term_windgoto(1, 0);
	out_str((char_u *)"  ");
	line_was_clobbered(1);
    }

    if (xcc_status.tr_progress == STATUS_GET && Rows > 2)
    {


	MAY_WANT_TO_LOG_THIS;
	LOG_TR(("Sending xterm compatibility test sequence."));


	term_windgoto(2, 0);

	out_str((char_u *)"\033Pzz\033\\");

	out_str((char_u *)"\033[0%m");
	out_str(T_U7);
	termrequest_sent(&xcc_status);
	out_flush();
	did_send = TRUE;


	screen_stop_highlight();
	term_windgoto(2, 0);
	out_str((char_u *)"           ");
	line_was_clobbered(2);
    }

    if (did_send)
    {
	term_windgoto(0, 0);


	screen_start();


	out_flush();
	(void)vpeekc_nomap();
    }
}
