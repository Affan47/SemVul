command_height(void)
{
    int		h;
    frame_T	*frp;
    int		old_p_ch = curtab->tp_ch_used;


    curtab->tp_ch_used = p_ch;


    frp = lastwin->w_frame;
    while (frp->fr_width != Columns && frp->fr_parent != NULL)
	frp = frp->fr_parent;


    while (frp->fr_prev != NULL && frp->fr_layout == FR_LEAF
						      && frp->fr_win->w_p_wfh)
	frp = frp->fr_prev;

    if (starting != NO_SCREEN)
    {
	cmdline_row = Rows - p_ch;

	if (p_ch > old_p_ch)
	{
	    while (p_ch > old_p_ch)
	    {
		if (frp == NULL)
		{
		    emsg(_(e_not_enough_room));
		    p_ch = old_p_ch;
		    curtab->tp_ch_used = p_ch;
		    cmdline_row = Rows - p_ch;
		    break;
		}
		h = frp->fr_height - frame_minheight(frp, NULL);
		if (h > p_ch - old_p_ch)
		    h = p_ch - old_p_ch;
		old_p_ch += h;
		frame_add_height(frp, -h);
		frp = frp->fr_prev;
	    }


	    (void)win_comp_pos();


	    if (full_screen)
		screen_fill((int)(cmdline_row), (int)Rows, 0,
						   (int)Columns, ' ', ' ', 0);
	    msg_row = cmdline_row;
	    redraw_cmdline = TRUE;
	    return;
	}

	if (msg_row < cmdline_row)
	    msg_row = cmdline_row;
	redraw_cmdline = TRUE;
    }
    frame_add_height(frp, (int)(old_p_ch - p_ch));


    if (frp != lastwin->w_frame)
	(void)win_comp_pos();
}
