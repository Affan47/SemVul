win_totop(int size, int flags)
{
    int		dir;
    int		height = curwin->w_height;

    if (ONE_WINDOW)
    {
	beep_flush();
	return;
    }
    if (check_split_disallowed() == FAIL)
	return;


    (void)winframe_remove(curwin, &dir, NULL);
    win_remove(curwin, NULL);
    last_status(FALSE);
    (void)win_comp_pos();


    (void)win_split_ins(size, flags, curwin, dir);
    if (!(flags & WSP_VERT))
    {
	win_setheight(height);
	if (p_ea)
	    win_equal(curwin, TRUE, 'v');
    }

#if defined(FEAT_GUI)


    gui_may_update_scrollbars();
#endif
}
