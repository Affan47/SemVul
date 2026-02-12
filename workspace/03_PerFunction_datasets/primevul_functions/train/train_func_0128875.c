check_auto_format(
    int		end_insert)
{
    int		c = ' ';
    int		cc;

    if (did_add_space)
    {
	cc = gchar_cursor();
	if (!WHITECHAR(cc))

	    did_add_space = FALSE;
	else
	{
	    if (!end_insert)
	    {
		inc_cursor();
		c = gchar_cursor();
		dec_cursor();
	    }
	    if (c != NUL)
	    {

		del_char(FALSE);
		did_add_space = FALSE;
	    }
	}
    }
}
