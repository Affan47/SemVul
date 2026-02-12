msg_scroll_up(void)
{
#ifdef FEAT_GUI


    if (gui.in_use)
	gui_undraw_cursor();
#endif

    mch_disable_flush();
    screen_del_lines(0, 0, 1, (int)Rows, TRUE, 0, NULL);
    mch_enable_flush();

    if (!can_clear((char_u *)" "))
    {


	screen_fill((int)Rows - 1, (int)Rows, 0, (int)Columns, ' ', ' ', 0);


	if (ScreenAttrs[LineOffset[Rows - 2] + Columns - 1] == (sattr_T)-1)
	    screen_fill((int)Rows - 2, (int)Rows - 1,
				 (int)Columns - 1, (int)Columns, ' ', ' ', 0);
    }
}
