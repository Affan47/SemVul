win_free_lsize(win_T *wp)
{

    if (wp != NULL)
	VIM_CLEAR(wp->w_lines);
}
