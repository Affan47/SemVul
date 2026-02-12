win_equal_rec(
    win_T	*next_curwin,
    int		current,
    frame_T	*topfr,
    int		dir,
    int		col,
    int		row,
    int		width,
    int		height)
{
    int		n, m;
    int		extra_sep = 0;
    int		wincount, totwincount = 0;
    frame_T	*fr;
    int		next_curwin_size = 0;
    int		room = 0;
    int		new_size;
    int		has_next_curwin = 0;
    int		hnc;

    if (topfr->fr_layout == FR_LEAF)
    {


	if (topfr->fr_height != height || topfr->fr_win->w_winrow != row
		|| topfr->fr_width != width || topfr->fr_win->w_wincol != col
	   )
	{
	    topfr->fr_win->w_winrow = row;
	    frame_new_height(topfr, height, FALSE, FALSE);
	    topfr->fr_win->w_wincol = col;
	    frame_new_width(topfr, width, FALSE, FALSE);
	    redraw_all_later(NOT_VALID);
	}
    }
    else if (topfr->fr_layout == FR_ROW)
    {
	topfr->fr_width = width;
	topfr->fr_height = height;

	if (dir != 'v')
	{


	    n = frame_minwidth(topfr, NOWIN);

	    if (col + width == Columns)
		extra_sep = 1;
	    else
		extra_sep = 0;
	    totwincount = (n + extra_sep) / (p_wmw + 1);
	    has_next_curwin = frame_has_win(topfr, next_curwin);


	    m = frame_minwidth(topfr, next_curwin);
	    room = width - m;
	    if (room < 0)
	    {
		next_curwin_size = p_wiw + room;
		room = 0;
	    }
	    else
	    {
		next_curwin_size = -1;
		FOR_ALL_FRAMES(fr, topfr->fr_child)
		{


		    if (frame_fixed_width(fr))
		    {
			n = frame_minwidth(fr, NOWIN);
			new_size = fr->fr_width;
			if (frame_has_win(fr, next_curwin))
			{
			    room += p_wiw - p_wmw;
			    next_curwin_size = 0;
			    if (new_size < p_wiw)
				new_size = p_wiw;
			}
			else

			    totwincount -= (n + (fr->fr_next == NULL
					      ? extra_sep : 0)) / (p_wmw + 1);
			room -= new_size - n;
			if (room < 0)
			{
			    new_size += room;
			    room = 0;
			}
			fr->fr_newwidth = new_size;
		    }
		}
		if (next_curwin_size == -1)
		{
		    if (!has_next_curwin)
			next_curwin_size = 0;
		    else if (totwincount > 1
			    && (room + (totwincount - 2))
						  / (totwincount - 1) > p_wiw)
		    {


			next_curwin_size = (room + p_wiw
					    + (totwincount - 1) * p_wmw
					    + (totwincount - 1)) / totwincount;
			room -= next_curwin_size - p_wiw;
		    }
		    else
			next_curwin_size = p_wiw;
		}
	    }

	    if (has_next_curwin)
		--totwincount;
	}

	FOR_ALL_FRAMES(fr, topfr->fr_child)
	{
	    wincount = 1;
	    if (fr->fr_next == NULL)

		new_size = width;
	    else if (dir == 'v')
		new_size = fr->fr_width;
	    else if (frame_fixed_width(fr))
	    {
		new_size = fr->fr_newwidth;
		wincount = 0;
	    }
	    else
	    {

		n = frame_minwidth(fr, NOWIN);
		wincount = (n + (fr->fr_next == NULL ? extra_sep : 0))
								/ (p_wmw + 1);
		m = frame_minwidth(fr, next_curwin);
		if (has_next_curwin)
		    hnc = frame_has_win(fr, next_curwin);
		else
		    hnc = FALSE;
		if (hnc)
		    --wincount;
		if (totwincount == 0)
		    new_size = room;
		else
		    new_size = (wincount * room + ((unsigned)totwincount >> 1))
								/ totwincount;
		if (hnc)
		{
		    next_curwin_size -= p_wiw - (m - n);
		    new_size += next_curwin_size;
		    room -= new_size - next_curwin_size;
		}
		else
		    room -= new_size;
		new_size += n;
	    }


	    if (!current || dir != 'v' || topfr->fr_parent != NULL
		    || (new_size != fr->fr_width)
		    || frame_has_win(fr, next_curwin))
		win_equal_rec(next_curwin, current, fr, dir, col, row,
							    new_size, height);
	    col += new_size;
	    width -= new_size;
	    totwincount -= wincount;
	}
    }
    else
    {
	topfr->fr_width = width;
	topfr->fr_height = height;

	if (dir != 'h')
	{

	    n = frame_minheight(topfr, NOWIN);

	    if (row + height == cmdline_row && p_ls == 0)
		extra_sep = 1;
	    else
		extra_sep = 0;
	    totwincount = (n + extra_sep) / (p_wmh + 1);
	    has_next_curwin = frame_has_win(topfr, next_curwin);


	    m = frame_minheight(topfr, next_curwin);
	    room = height - m;
	    if (room < 0)
	    {


		next_curwin_size = p_wh + room;
		room = 0;
	    }
	    else
	    {
		next_curwin_size = -1;
		FOR_ALL_FRAMES(fr, topfr->fr_child)
		{


		    if (frame_fixed_height(fr))
		    {
			n = frame_minheight(fr, NOWIN);
			new_size = fr->fr_height;
			if (frame_has_win(fr, next_curwin))
			{
			    room += p_wh - p_wmh;
			    next_curwin_size = 0;
			    if (new_size < p_wh)
				new_size = p_wh;
			}
			else

			    totwincount -= (n + (fr->fr_next == NULL
					      ? extra_sep : 0)) / (p_wmh + 1);
			room -= new_size - n;
			if (room < 0)
			{
			    new_size += room;
			    room = 0;
			}
			fr->fr_newheight = new_size;
		    }
		}
		if (next_curwin_size == -1)
		{
		    if (!has_next_curwin)
			next_curwin_size = 0;
		    else if (totwincount > 1
			    && (room + (totwincount - 2))
						   / (totwincount - 1) > p_wh)
		    {


			next_curwin_size = (room + p_wh
					   + (totwincount - 1) * p_wmh
					   + (totwincount - 1)) / totwincount;
			room -= next_curwin_size - p_wh;
		    }
		    else
			next_curwin_size = p_wh;
		}
	    }

	    if (has_next_curwin)
		--totwincount;
	}

	FOR_ALL_FRAMES(fr, topfr->fr_child)
	{
	    wincount = 1;
	    if (fr->fr_next == NULL)

		new_size = height;
	    else if (dir == 'h')
		new_size = fr->fr_height;
	    else if (frame_fixed_height(fr))
	    {
		new_size = fr->fr_newheight;
		wincount = 0;
	    }
	    else
	    {

		n = frame_minheight(fr, NOWIN);
		wincount = (n + (fr->fr_next == NULL ? extra_sep : 0))
								/ (p_wmh + 1);
		m = frame_minheight(fr, next_curwin);
		if (has_next_curwin)
		    hnc = frame_has_win(fr, next_curwin);
		else
		    hnc = FALSE;
		if (hnc)
		    --wincount;
		if (totwincount == 0)
		    new_size = room;
		else
		    new_size = (wincount * room + ((unsigned)totwincount >> 1))
								/ totwincount;
		if (hnc)
		{
		    next_curwin_size -= p_wh - (m - n);
		    new_size += next_curwin_size;
		    room -= new_size - next_curwin_size;
		}
		else
		    room -= new_size;
		new_size += n;
	    }


	    if (!current || dir != 'h' || topfr->fr_parent != NULL
		    || (new_size != fr->fr_height)
		    || frame_has_win(fr, next_curwin))
		win_equal_rec(next_curwin, current, fr, dir, col, row,
							     width, new_size);
	    row += new_size;
	    height -= new_size;
	    totwincount -= wincount;
	}
    }
}
