frame_new_height(
    frame_T	*topfrp,
    int		height,
    int		topfirst,
    int		wfh)

{
    frame_T	*frp;
    int		extra_lines;
    int		h;

    if (topfrp->fr_win != NULL)
    {

	win_new_height(topfrp->fr_win,
				    height - topfrp->fr_win->w_status_height
					      - WINBAR_HEIGHT(topfrp->fr_win));
    }
    else if (topfrp->fr_layout == FR_ROW)
    {
	do
	{

	    FOR_ALL_FRAMES(frp, topfrp->fr_child)
	    {
		frame_new_height(frp, height, topfirst, wfh);
		if (frp->fr_height > height)
		{

		    height = frp->fr_height;
		    break;
		}
	    }
	}
	while (frp != NULL);
    }
    else
    {


	frp = topfrp->fr_child;
	if (wfh)

	    while (frame_fixed_height(frp))
	    {
		frp = frp->fr_next;
		if (frp == NULL)
		    return;
	    }
	if (!topfirst)
	{

	    while (frp->fr_next != NULL)
		frp = frp->fr_next;
	    if (wfh)

		while (frame_fixed_height(frp))
		    frp = frp->fr_prev;
	}

	extra_lines = height - topfrp->fr_height;
	if (extra_lines < 0)
	{

	    while (frp != NULL)
	    {
		h = frame_minheight(frp, NULL);
		if (frp->fr_height + extra_lines < h)
		{
		    extra_lines += frp->fr_height - h;
		    frame_new_height(frp, h, topfirst, wfh);
		}
		else
		{
		    frame_new_height(frp, frp->fr_height + extra_lines,
							       topfirst, wfh);
		    break;
		}
		if (topfirst)
		{
		    do
			frp = frp->fr_next;
		    while (wfh && frp != NULL && frame_fixed_height(frp));
		}
		else
		{
		    do
			frp = frp->fr_prev;
		    while (wfh && frp != NULL && frame_fixed_height(frp));
		}

		if (frp == NULL)
		    height -= extra_lines;
	    }
	}
	else if (extra_lines > 0)
	{

	    frame_new_height(frp, frp->fr_height + extra_lines, topfirst, wfh);
	}
    }
    topfrp->fr_height = height;
}
