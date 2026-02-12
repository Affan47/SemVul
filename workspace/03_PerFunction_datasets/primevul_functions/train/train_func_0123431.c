close_others(
    int		message,
    int		forceit)
{
    win_T	*wp;
    win_T	*nextwp;
    int		r;

    if (one_window())
    {
	if (message && !autocmd_busy)
	    msg(_(m_onlyone));
	return;
    }


    for (wp = firstwin; win_valid(wp); wp = nextwp)
    {
	nextwp = wp->w_next;
	if (wp != curwin)
	{


	    r = can_abandon(wp->w_buffer, forceit);
	    if (!win_valid(wp))
	    {
		nextwp = firstwin;
		continue;
	    }
	    if (!r)
	    {
#if defined(FEAT_GUI_DIALOG) || defined(FEAT_CON_DIALOG)
		if (message && (p_confirm || cmdmod.confirm) && p_write)
		{
		    dialog_changed(wp->w_buffer, FALSE);
		    if (!win_valid(wp))
		    {
			nextwp = firstwin;
			continue;
		    }
		}
		if (bufIsChanged(wp->w_buffer))
#endif
		    continue;
	    }
	    win_close(wp, !buf_hide(wp->w_buffer)
					       && !bufIsChanged(wp->w_buffer));
	}
    }

    if (message && !ONE_WINDOW)
	emsg(_("E445: Other window contains changes"));
}
