get_indent_str(
    char_u	*ptr,
    int		ts,
    int		list)
{
    int		count = 0;

    for ( ; *ptr; ++ptr)
    {
	if (*ptr == TAB)
	{
	    if (!list || curwin->w_lcs_chars.tab1)

		count += ts - (count % ts);
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
