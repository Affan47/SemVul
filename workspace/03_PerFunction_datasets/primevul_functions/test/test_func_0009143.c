get_indent_str_vtab(char_u *ptr, int ts, int *vts, int list)
{
    int		count = 0;

    for ( ; *ptr; ++ptr)
    {
	if (*ptr == TAB)
	{
	    if (!list || curwin->w_lcs_chars.tab1)
		count += tabstop_padding(count, ts, vts);
	    else


		count += ptr2cells(ptr);
	}
	else if (*ptr == ' ')
	    ++count;
	else
	    break;
    }
    return count;
}
