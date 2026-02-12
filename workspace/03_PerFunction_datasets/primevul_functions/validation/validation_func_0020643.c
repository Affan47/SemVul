filemess(
    buf_T	*buf,
    char_u	*name,
    char_u	*s,
    int		attr)
{
    int		msg_scroll_save;

    if (msg_silent != 0)
	return;
    msg_add_fname(buf, name);

    if (STRLEN(IObuff) > IOSIZE - 80)
	IObuff[IOSIZE - 80] = NUL;
    STRCAT(IObuff, s);


    msg_scroll_save = msg_scroll;
    if (shortmess(SHM_OVERALL) && !exiting && p_verbose == 0)
	msg_scroll = FALSE;
    if (!msg_scroll)
	check_for_delay(FALSE);
    msg_start();
    msg_scroll = msg_scroll_save;
    msg_scrolled_ign = TRUE;

    msg_outtrans_attr(msg_may_trunc(FALSE, IObuff), attr);
    msg_clr_eos();
    out_flush();
    msg_scrolled_ign = FALSE;
}
