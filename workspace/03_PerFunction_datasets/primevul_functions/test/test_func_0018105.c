get_fpos_of_mouse(pos_T *mpos)
{
    win_T	*wp;
    int		row = mouse_row;
    int		col = mouse_col;

    if (row < 0 || col < 0)
	return IN_UNKNOWN;


    wp = mouse_find_win(&row, &col, FAIL_POPUP);
    if (wp == NULL)
	return IN_UNKNOWN;

    if (row >= wp->w_height)
	return IN_STATUS_LINE;
    if (col >= wp->w_width)
	return IN_SEP_LINE;

    if (wp != curwin)
	return IN_UNKNOWN;


    if (mouse_comp_pos(curwin, &row, &col, &mpos->lnum, NULL))
	return IN_STATUS_LINE;

    mpos->col = vcol2col(wp, mpos->lnum, col);

    if (mpos->col > 0)
	--mpos->col;
    mpos->coladd = 0;
    return IN_BUFFER;
}
