shell_new_columns(void)
{
    if (firstwin == NULL)
	return;


    frame_new_width(topframe, (int)Columns, FALSE, TRUE);
    if (!frame_check_width(topframe, Columns))
	frame_new_width(topframe, (int)Columns, FALSE, FALSE);

    (void)win_comp_pos();
#if 0

    if (p_ea)
	win_equal(curwin, FALSE, 'h');
#endif
}
