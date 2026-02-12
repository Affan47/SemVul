frame_setwidth(frame_T *curfrp, int width)
{
    int		room;
    int		take;
    int		run;
    frame_T	*frp;
    int		w;
    int		room_reserved;


    if (curfrp->fr_width == width)
	return;

    if (curfrp->fr_parent == NULL)

	return;

    if (curfrp->fr_parent->fr_layout == FR_COL)
    {


	w = frame_minwidth(curfrp->fr_parent, NULL);
	if (width < w)
	    width = w;
	frame_setwidth(curfrp->fr_parent, width);
    }
    else
    {


	for (run = 1; run <= 2; ++run)
	{
	    room = 0;
	    room_reserved = 0;
	    FOR_ALL_FRAMES(frp, curfrp->fr_parent->fr_child)
	    {
		if (frp != curfrp
			&& frp->fr_win != NULL
			&& frp->fr_win->w_p_wfw)
		    room_reserved += frp->fr_width;
		room += frp->fr_width;
		if (frp != curfrp)
		    room -= frame_minwidth(frp, NULL);
	    }

	    if (width <= room)
		break;
	    if (run == 2 || curfrp->fr_height >= ROWS_AVAIL)
	    {
		if (width > room)
		    width = room;
		break;
	    }
	    frame_setwidth(curfrp->fr_parent, width
		 + frame_minwidth(curfrp->fr_parent, NOWIN) - (int)p_wmw - 1);
	}


	take = width - curfrp->fr_width;


	if (width > room - room_reserved)
	    room_reserved = room - width;


	if (take < 0 && room - curfrp->fr_width < room_reserved)
	    room_reserved = 0;


	frame_new_width(curfrp, width, FALSE, FALSE);


	for (run = 0; run < 2; ++run)
	{
	    if (run == 0)
		frp = curfrp->fr_next;
	    else
		frp = curfrp->fr_prev;
	    while (frp != NULL && take != 0)
	    {
		w = frame_minwidth(frp, NULL);
		if (room_reserved > 0
			&& frp->fr_win != NULL
			&& frp->fr_win->w_p_wfw)
		{
		    if (room_reserved >= frp->fr_width)
			room_reserved -= frp->fr_width;
		    else
		    {
			if (frp->fr_width - room_reserved > take)
			    room_reserved = frp->fr_width - take;
			take -= frp->fr_width - room_reserved;
			frame_new_width(frp, room_reserved, FALSE, FALSE);
			room_reserved = 0;
		    }
		}
		else
		{
		    if (frp->fr_width - take < w)
		    {
			take -= frp->fr_width - w;
			frame_new_width(frp, w, FALSE, FALSE);
		    }
		    else
		    {
			frame_new_width(frp, frp->fr_width - take,
								FALSE, FALSE);
			take = 0;
		    }
		}
		if (run == 0)
		    frp = frp->fr_next;
		else
		    frp = frp->fr_prev;
	    }
	}
    }
}
