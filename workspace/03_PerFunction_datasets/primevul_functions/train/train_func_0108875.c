inchar(
    char_u	*buf,
    int		maxlen,
    long	wait_time)
{
    int		len = 0;
    int		retesc = FALSE;
    int		script_char;
    int		tb_change_cnt = typebuf.tb_change_cnt;

    if (wait_time == -1L || wait_time > 100L)
    {
	cursor_on();
	out_flush_cursor(FALSE, FALSE);
#if defined(FEAT_GUI) && defined(FEAT_MOUSESHAPE)
	if (gui.in_use && postponed_mouseshape)
	    update_mouseshape(-1);
#endif
    }


    if (State != HITRETURN)
    {
	did_outofmem_msg = FALSE;
	did_swapwrite_msg = FALSE;
    }
    undo_off = FALSE;


    script_char = -1;
    while (scriptin[curscript] != NULL && script_char < 0
#ifdef FEAT_EVAL
	    && !ignore_script
#endif
	    )
    {

#ifdef MESSAGE_QUEUE
	parse_queued_messages();
#endif

	if (got_int || (script_char = getc(scriptin[curscript])) < 0)
	{


	    closescript();


	    if (got_int)
		retesc = TRUE;
	    else
		return -1;
	}
	else
	{
	    buf[0] = script_char;
	    len = 1;
	}
    }

    if (script_char < 0)
    {


	if (got_int)
	{
#define DUM_LEN MAXMAPLEN * 3 + 3
	    char_u	dum[DUM_LEN + 1];

	    for (;;)
	    {
		len = ui_inchar(dum, DUM_LEN, 0L, 0);
		if (len == 0 || (len == 1 && dum[0] == 3))
		    break;
	    }
	    return retesc;
	}


	if (wait_time == -1L || wait_time > 10L)
	    out_flush();


	len = ui_inchar(buf, maxlen / 3, wait_time, tb_change_cnt);
    }


    if (typebuf_changed(tb_change_cnt))
	return 0;


    if (len > 0 && ++typebuf.tb_change_cnt == 0)
	typebuf.tb_change_cnt = 1;

    return fix_input_buffer(buf, len);
}
