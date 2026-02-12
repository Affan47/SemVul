win_drag_status_line(win_T *dragwin, int offset)
{
    frame_T	*curfr;
    frame_T	*fr;
    int		room;
    int		row;
    int		up;
    int		n;

    fr = dragwin->w_frame;
    curfr = fr;
    if (fr != topframe)
    {
	fr = fr->fr_parent;


	if (fr->fr_layout != FR_COL)
	{
	    curfr = fr;
	    if (fr != topframe)
		fr = fr->fr_parent;
	}
    }


    while (curfr != topframe && curfr->fr_next == NULL)
    {
	if (fr != topframe)
	    fr = fr->fr_parent;
	curfr = fr;
	if (fr != topframe)
	    fr = fr->fr_parent;
    }

    if (offset < 0)
    {
	up = TRUE;
	offset = -offset;

	if (fr == curfr)
	{

	    room = fr->fr_height - frame_minheight(fr, NULL);
	}
	else
	{
	    room = 0;
	    for (fr = fr->fr_child; ; fr = fr->fr_next)
	    {
		room += fr->fr_height - frame_minheight(fr, NULL);
		if (fr == curfr)
		    break;
	    }
	}
	fr = curfr->fr_next;
    }
    else
    {
	up = FALSE;


	room = Rows - cmdline_row;
	if (curfr->fr_next == NULL)
	    room -= 1;
	else
	    room -= p_ch;
	if (room < 0)
	    room = 0;

	FOR_ALL_FRAMES(fr, curfr->fr_next)
	    room += fr->fr_height - frame_minheight(fr, NULL);
	fr = curfr;
    }

    if (room < offset)
	offset = room;
    if (offset <= 0)
	return;


    if (fr != NULL)
	frame_new_height(fr, fr->fr_height + offset, up, FALSE);

    if (up)
	fr = curfr;
    else
	fr = curfr->fr_next;


    while (fr != NULL && offset > 0)
    {
	n = frame_minheight(fr, NULL);
	if (fr->fr_height - offset <= n)
	{
	    offset -= fr->fr_height - n;
	    frame_new_height(fr, n, !up, FALSE);
	}
	else
	{
	    frame_new_height(fr, fr->fr_height - offset, !up, FALSE);
	    break;
	}
	if (up)
	    fr = fr->fr_prev;
	else
	    fr = fr->fr_next;
    }
    row = win_comp_pos();
    screen_fill(row, cmdline_row, 0, (int)Columns, ' ', ' ', 0);
    cmdline_row = row;
    p_ch = Rows - cmdline_row;
    if (p_ch < 1)
	p_ch = 1;
    curtab->tp_ch_used = p_ch;
    redraw_all_later(SOME_VALID);
    showmode();
}
