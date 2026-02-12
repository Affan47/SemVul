win_drag_vsep_line(win_T *dragwin, int offset)
{
    frame_T	*curfr;
    frame_T	*fr;
    int		room;
    int		left;
    int		n;

    fr = dragwin->w_frame;
    if (fr == topframe)
	return;
    curfr = fr;
    fr = fr->fr_parent;

    if (fr->fr_layout != FR_ROW)
    {
	if (fr == topframe)
	    return;
	curfr = fr;
	fr = fr->fr_parent;
    }


    while (curfr->fr_next == NULL)
    {
	if (fr == topframe)
	    break;
	curfr = fr;
	fr = fr->fr_parent;
	if (fr != topframe)
	{
	    curfr = fr;
	    fr = fr->fr_parent;
	}
    }

    if (offset < 0)
    {
	left = TRUE;
	offset = -offset;

	room = 0;
	for (fr = fr->fr_child; ; fr = fr->fr_next)
	{
	    room += fr->fr_width - frame_minwidth(fr, NULL);
	    if (fr == curfr)
		break;
	}
	fr = curfr->fr_next;
    }
    else
    {
	left = FALSE;

	room = 0;
	FOR_ALL_FRAMES(fr, curfr->fr_next)
	    room += fr->fr_width - frame_minwidth(fr, NULL);
	fr = curfr;
    }

    if (room < offset)
	offset = room;
    if (offset <= 0)
	return;
    if (fr == NULL)
	return;


    frame_new_width(fr, fr->fr_width + offset, left, FALSE);


    if (left)
	fr = curfr;
    else
	fr = curfr->fr_next;

    while (fr != NULL && offset > 0)
    {
	n = frame_minwidth(fr, NULL);
	if (fr->fr_width - offset <= n)
	{
	    offset -= fr->fr_width - n;
	    frame_new_width(fr, n, !left, FALSE);
	}
	else
	{
	    frame_new_width(fr, fr->fr_width - offset, !left, FALSE);
	    break;
	}
	if (left)
	    fr = fr->fr_prev;
	else
	    fr = fr->fr_next;
    }
    (void)win_comp_pos();
    redraw_all_later(NOT_VALID);
}
