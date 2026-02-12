updateWindow(win_T *wp)
{

    if (updating_screen)
	return;

    update_prepare();

#ifdef FEAT_CLIPBOARD

    if (clip_star.available && clip_isautosel_star())
	clip_update_selection(&clip_star);
    if (clip_plus.available && clip_isautosel_plus())
	clip_update_selection(&clip_plus);
#endif

    win_update(wp);


    if (redraw_tabline)
	draw_tabline();

    if (wp->w_redr_status
# ifdef FEAT_CMDL_INFO
	    || p_ru
# endif
# ifdef FEAT_STL_OPT
	    || *p_stl != NUL || *wp->w_p_stl != NUL
# endif
	    )
	win_redr_status(wp, FALSE);

#ifdef FEAT_PROP_POPUP

    update_popups(win_update);
#endif

    update_finish();
}
