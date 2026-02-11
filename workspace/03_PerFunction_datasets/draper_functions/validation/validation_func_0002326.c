nodelay(WINDOW *win, bool flag)
{
    T((T_CALLED("nodelay(%p,%d)"), win, flag));

    if (win) {
	if (flag == TRUE)
	    win->_delay = 0;
	else
	    win->_delay = -1;
	returnCode(OK);
    } else
	returnCode(ERR);
}
