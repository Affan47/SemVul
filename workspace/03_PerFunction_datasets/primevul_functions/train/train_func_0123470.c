win_equal(
    win_T	*next_curwin,
    int		current,
    int		dir)

{
    if (dir == 0)
	dir = *p_ead;
    win_equal_rec(next_curwin == NULL ? curwin : next_curwin, current,
		      topframe, dir, 0, tabline_height(),
					   (int)Columns, topframe->fr_height);
}
