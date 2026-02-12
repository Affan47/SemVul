qf_winid(qf_info_T *qi)
{
    win_T	*win;


    if (qi == NULL)
	return 0;
    win = qf_find_win(qi);
    if (win != NULL)
	return win->w_id;
    return 0;
}
