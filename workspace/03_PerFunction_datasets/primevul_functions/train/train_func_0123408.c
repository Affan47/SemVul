win_goto_hor(
    int		left,
    long	count)
{
    win_T	*win;

    win = win_horz_neighbor(curtab, curwin, left, count);
    if (win != NULL)
	win_goto(win);
}
