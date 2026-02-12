redraw_all_later(int type)
{
    win_T	*wp;

    FOR_ALL_WINDOWS(wp)
	redraw_win_later(wp, type);

    if (must_redraw < type)
	must_redraw = type;
}
