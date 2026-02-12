win_move_after(win_T *win1, win_T *win2)
{
    int		height;


    if (win1 == win2)
	return;


    if (win2->w_next != win1)
    {
	if (win1->w_frame->fr_parent != win2->w_frame->fr_parent)
	{
	    iemsg("INTERNAL: trying to move a window into another frame");
	    return;
	}


	if (win1 == lastwin)
	{
	    height = win1->w_prev->w_status_height;
	    win1->w_prev->w_status_height = win1->w_status_height;
	    win1->w_status_height = height;
	    if (win1->w_prev->w_vsep_width == 1)
	    {


		win1->w_prev->w_vsep_width = 0;
		win1->w_prev->w_frame->fr_width -= 1;
		win1->w_vsep_width = 1;
		win1->w_frame->fr_width += 1;
	    }
	}
	else if (win2 == lastwin)
	{
	    height = win1->w_status_height;
	    win1->w_status_height = win2->w_status_height;
	    win2->w_status_height = height;
	    if (win1->w_vsep_width == 1)
	    {


		win2->w_vsep_width = 1;
		win2->w_frame->fr_width += 1;
		win1->w_vsep_width = 0;
		win1->w_frame->fr_width -= 1;
	    }
	}
	win_remove(win1, NULL);
	frame_remove(win1->w_frame);
	win_append(win2, win1);
	frame_append(win2->w_frame, win1->w_frame);

	(void)win_comp_pos();
	redraw_later(NOT_VALID);
    }
    win_enter(win1, FALSE);
}
