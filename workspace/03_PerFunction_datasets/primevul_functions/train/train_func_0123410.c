win_free_mem(
    win_T	*win,
    int		*dirp,
    tabpage_T	*tp)
{
    frame_T	*frp;
    win_T	*wp;


    frp = win->w_frame;
    wp = winframe_remove(win, dirp, tp);
    vim_free(frp);
    win_free(win, tp);


    if (tp != NULL && win == tp->tp_curwin)
	tp->tp_curwin = wp;

    return wp;
}
