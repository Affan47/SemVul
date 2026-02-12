normal_cmd_wait_for_msg(void)
{
    int	save_State = State;


    if (restart_edit != 0)
	State = MODE_INSERT;


    if (must_redraw && keep_msg != NULL && !emsg_on_display)
    {
	char_u	*kmsg;

	kmsg = keep_msg;
	keep_msg = NULL;


	setcursor();
	update_screen(0);

	keep_msg = kmsg;

	kmsg = vim_strsave(keep_msg);
	if (kmsg != NULL)
	{
	    msg_attr((char *)kmsg, keep_msg_attr);
	    vim_free(kmsg);
	}
    }
    setcursor();
#ifdef CURSOR_SHAPE
    ui_cursor_shape();
#endif
    cursor_on();
    out_flush();
    if (msg_scroll || emsg_on_display)
	ui_delay(1003L, TRUE);
    ui_delay(3003L, FALSE);
    State = save_State;

    msg_scroll = FALSE;
    emsg_on_display = FALSE;
}
