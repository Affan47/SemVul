win_new_height(win_T *wp, int height)
{
    int		prev_height = wp->w_height;


    if (height < 0)
	height = 0;
    if (wp->w_height == height)
	return;

    if (wp->w_height > 0)
    {
	if (wp == curwin)


	    validate_cursor();
	if (wp->w_height != prev_height)
	    return;

	if (wp->w_wrow != wp->w_prev_fraction_row)
	    set_fraction(wp);
    }

    wp->w_height = height;
    wp->w_skipcol = 0;


    if (!exiting)
	scroll_to_fraction(wp, prev_height);
}
