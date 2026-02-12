find_prev_quote(
    char_u	*line,
    int		col_start,
    int		quotechar,
    char_u	*escape)
{
    int		n;

    while (col_start > 0)
    {
	--col_start;
	col_start -= (*mb_head_off)(line, line + col_start);
	n = 0;
	if (escape != NULL)
	    while (col_start - n > 0 && vim_strchr(escape,
					     line[col_start - n - 1]) != NULL)
	    ++n;
	if (n & 1)
	    col_start -= n;
	else if (line[col_start] == quotechar)
	    break;
    }
    return col_start;
}
