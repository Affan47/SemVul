redraw_after_callback(int call_update_screen, int do_message)
{
    ++redrawing_for_callback;

    if (State == HITRETURN || State == ASKMORE || State == SETWSIZE
	    || State == EXTERNCMD || State == CONFIRM || exmode_active)
    {
	if (do_message)
	    repeat_message();
    }
    else if (State & CMDLINE)
    {

	if (cmdline_row > 0)
	{


	    if (msg_scrolled == 0
#ifdef FEAT_WILDMENU
		    && wild_menu_showing == 0
#endif
		    && call_update_screen)
		update_screen(0);


	    redrawcmdline_ex(FALSE);
	}
    }
    else if (State & (NORMAL | INSERT | TERMINAL))
    {

	update_screen(VALID_NO_UPDATE);
	setcursor();

	if (msg_scrolled == 0)
	{

	    msg_didany = FALSE;
	    need_wait_return = FALSE;
	}
    }
    cursor_on();
#ifdef FEAT_GUI
    if (gui.in_use && !gui_mch_is_blink_off())


	out_flush_cursor(FALSE, FALSE);
    else
#endif
	out_flush();

    --redrawing_for_callback;
}
