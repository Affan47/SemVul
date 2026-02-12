update_prepare(void)
{
    cursor_off();
    updating_screen = TRUE;
#ifdef FEAT_GUI


    if (gui.in_use)
	gui_undraw_cursor();
#endif
#ifdef FEAT_SEARCH_EXTRA
    start_search_hl();
#endif
#ifdef FEAT_PROP_POPUP

    may_update_popup_mask(must_redraw);
#endif
}
