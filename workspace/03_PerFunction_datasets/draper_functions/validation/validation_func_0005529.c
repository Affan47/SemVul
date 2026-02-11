is_wintouched(WINDOW *win)
{
    int i;

    T((T_CALLED("is_wintouched(%p)"), win));

    if (win)
	for (i = 0; i <= win->_maxy; i++)
	    if (win->_line[i].firstchar != _NOCHANGE)
		returnCode(TRUE);
    returnCode(FALSE);
}
