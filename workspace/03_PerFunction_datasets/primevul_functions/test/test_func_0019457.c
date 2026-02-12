redraw_cmd(int clear)
{
    int		r = RedrawingDisabled;
    int		p = p_lz;

    RedrawingDisabled = 0;
    p_lz = FALSE;
    validate_cursor();
    update_topline();
    update_screen(clear ? UPD_CLEAR : VIsual_active ? UPD_INVERTED : 0);
    if (need_maketitle)
	maketitle();
#if defined(MSWIN) && (!defined(FEAT_GUI_MSWIN) || defined(VIMDLL))
# ifdef VIMDLL
    if (!gui.in_use)
# endif
	resize_console_buf();
#endif
    RedrawingDisabled = r;
    p_lz = p;


    screen_stop_highlight();


    msg_didout = FALSE;
    msg_col = 0;


    need_wait_return = FALSE;


    if (State & MODE_CMDLINE)
	redrawcmdline();

    out_flush();
}
