do_dialog(
    int		type UNUSED,
    char_u	*title UNUSED,
    char_u	*message,
    char_u	*buttons,
    int		dfltbutton,
    char_u	*textfield UNUSED,

    int		ex_cmd)

{
    int		oldState;
    int		retval = 0;
    char_u	*hotkeys;
    int		c;
    int		i;
    tmode_T	save_tmode;

#ifndef NO_CONSOLE

    if (silent_mode)
	return dfltbutton;
#endif

#ifdef FEAT_GUI_DIALOG

    if (gui.in_use && vim_strchr(p_go, GO_CONDIALOG) == NULL)
    {

	if (gui_dialog_log(title, message))
	    c = dfltbutton;
	else
	    c = gui_mch_dialog(type, title, message, buttons, dfltbutton,
							   textfield, ex_cmd);

	need_wait_return = FALSE;
	emsg_on_display = FALSE;
	cmdline_row = msg_row;


	out_flush();
	gui_mch_update();

	return c;
    }
#endif

    oldState = State;
    State = MODE_CONFIRM;
    setmouse();


    save_tmode = cur_tmode;
    settmode(TMODE_RAW);


    ++no_wait_return;
    hotkeys = msg_show_console_dialog(message, buttons, dfltbutton);

    if (hotkeys != NULL)
    {
	for (;;)
	{

	    c = get_keystroke();
	    switch (c)
	    {
	    case CAR:
	    case NL:
		retval = dfltbutton;
		break;
	    case Ctrl_C:
	    case ESC:
		retval = 0;
		break;
	    default:
		if (c < 0)
		    continue;
		if (c == ':' && ex_cmd)
		{
		    retval = dfltbutton;
		    ins_char_typebuf(':', 0);
		    break;
		}


		c = MB_TOLOWER(c);
		retval = 1;
		for (i = 0; hotkeys[i]; ++i)
		{
		    if (has_mbyte)
		    {
			if ((*mb_ptr2char)(hotkeys + i) == c)
			    break;
			i += (*mb_ptr2len)(hotkeys + i) - 1;
		    }
		    else
			if (hotkeys[i] == c)
			    break;
		    ++retval;
		}
		if (hotkeys[i])
		    break;

		continue;
	    }
	    break;
	}

	vim_free(hotkeys);
    }

    settmode(save_tmode);
    State = oldState;
    setmouse();
    --no_wait_return;
    msg_end_prompt();

    return retval;
}
