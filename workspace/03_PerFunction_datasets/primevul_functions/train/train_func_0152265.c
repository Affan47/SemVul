back_in_line(void)
{
    int		sclass;

    sclass = cls();
    for (;;)
    {
	if (curwin->w_cursor.col == 0)
	    break;
	dec_cursor();
	if (cls() != sclass)
	{
	    inc_cursor();
	    break;
	}
    }
}
