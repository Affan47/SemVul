term_get_winpos(int *x, int *y, varnumber_T timeout)
{
    int count = 0;
    int prev_winpos_x = winpos_x;
    int prev_winpos_y = winpos_y;

    if (*T_CGP == NUL || !can_get_termresponse())
	return FAIL;
    winpos_x = -1;
    winpos_y = -1;
    ++did_request_winpos;
    termrequest_sent(&winpos_status);
    OUT_STR(T_CGP);
    out_flush();


    while (count++ <= timeout / 10 && !got_int)
    {
	(void)vpeekc_nomap();
	if (winpos_x >= 0 && winpos_y >= 0)
	{
	    *x = winpos_x;
	    *y = winpos_y;
	    return OK;
	}
	ui_delay(10L, FALSE);
    }


    winpos_x = prev_winpos_x;
    winpos_y = prev_winpos_y;
    if (timeout < 10 && prev_winpos_y >= 0 && prev_winpos_x >= 0)
    {

	*x = winpos_x;
	*y = winpos_y;
	return OK;
    }

    return FALSE;
}
