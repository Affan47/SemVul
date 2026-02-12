update_debug_sign(buf_T *buf, linenr_T lnum)
{
    win_T	*wp;
    int		doit = FALSE;

# ifdef FEAT_FOLDING
    win_foldinfo.fi_level = 0;
# endif


    redraw_buf_line_later(buf, lnum);


    FOR_ALL_WINDOWS(wp)
	if (wp->w_redr_type != 0)
	    doit = TRUE;


    if (!doit || updating_screen
	    || State == ASKMORE || State == HITRETURN
	    || msg_scrolled
#ifdef FEAT_GUI
	    || gui.starting
#endif
	    || starting)
	return;


    update_prepare();

    FOR_ALL_WINDOWS(wp)
    {
	if (wp->w_redr_type != 0)
	    win_update(wp);
	if (wp->w_redr_status)
	    win_redr_status(wp, FALSE);
    }

    update_finish();
}
