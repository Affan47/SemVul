bt_regexec_multi(
    regmmatch_T	*rmp,
    win_T	*win,
    buf_T	*buf,
    linenr_T	lnum,
    colnr_T	col,
    proftime_T	*tm,
    int		*timed_out)
{
    init_regexec_multi(rmp, win, buf, lnum);
    return bt_regexec_both(NULL, col, tm, timed_out);
}
