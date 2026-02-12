start_redo(long count, int old_redo)
{
    int	    c;


    if (read_redo(TRUE, old_redo) == FAIL)
	return FAIL;

    c = read_redo(FALSE, old_redo);


    if (c == '"')
    {
	add_buff(&readbuf2, (char_u *)"\"", 1L);
	c = read_redo(FALSE, old_redo);


	if (c >= '1' && c < '9')
	    ++c;
	add_char_buff(&readbuf2, c);


	if (c == '=')
	{
	    add_char_buff(&readbuf2, CAR);
	    cmd_silent = TRUE;
	}

	c = read_redo(FALSE, old_redo);
    }

    if (c == 'v')
    {
	VIsual = curwin->w_cursor;
	VIsual_active = TRUE;
	VIsual_select = FALSE;
	VIsual_reselect = TRUE;
	redo_VIsual_busy = TRUE;
	c = read_redo(FALSE, old_redo);
    }


    if (count)
    {
	while (VIM_ISDIGIT(c))
	    c = read_redo(FALSE, old_redo);
	add_num_buff(&readbuf2, count);
    }


    add_char_buff(&readbuf2, c);
    copy_redo(old_redo);
    return OK;
}
