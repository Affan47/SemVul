set_shellsize(int width, int height, int mustset)
{
    static int		busy = FALSE;


    if (busy)
	return;

    if (width < 0 || height < 0)
	return;

    if (State == MODE_HITRETURN || State == MODE_SETWSIZE)
    {

	State = MODE_SETWSIZE;
	return;
    }

    if (updating_screen)

	return;


    if (curwin->w_buffer == NULL || curwin->w_lines == NULL)
	return;

    ++busy;

#ifdef AMIGA
    out_flush();

#endif

    if (mustset || (ui_get_shellsize() == FAIL && height != 0))
    {
	Rows = height;
	Columns = width;
	check_shellsize();
	ui_set_shellsize(mustset);
    }
    else
	check_shellsize();


    if (State != MODE_ASKMORE && State != MODE_EXTERNCMD
						      && State != MODE_CONFIRM)
	screenclear();
    else
	screen_start();

    if (starting != NO_SCREEN)
    {
	maketitle();

	changed_line_abv_curs();
	invalidate_botline();


	if (State == MODE_ASKMORE || State == MODE_EXTERNCMD
				     || State == MODE_CONFIRM || exmode_active)
	{
	    screenalloc(FALSE);
	    repeat_message();
	}
	else
	{
	    if (curwin->w_p_scb)
		do_check_scrollbind(TRUE);
	    if (State & MODE_CMDLINE)
	    {
		update_screen(NOT_VALID);
		redrawcmdline();
	    }
	    else
	    {
		update_topline();
		if (pum_visible())
		{
		    redraw_later(NOT_VALID);
		    ins_compl_show_pum();
		}
		update_screen(NOT_VALID);
		if (redrawing())
		    setcursor();
	    }
	}
	cursor_on();
    }
    out_flush();
    --busy;
}
