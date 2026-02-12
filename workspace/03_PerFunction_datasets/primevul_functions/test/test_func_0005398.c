do_record(int c)
{
    char_u	    *p;
    static int	    regname;
    yankreg_T	    *old_y_previous, *old_y_current;
    int		    retval;

    if (reg_recording == 0)
    {

	if (c < 0 || (!ASCII_ISALNUM(c) && c != '"'))
	    retval = FAIL;
	else
	{
	    reg_recording = c;
	    showmode();
	    regname = c;
	    retval = OK;
	}
    }
    else
    {


	reg_recording = 0;
	msg("");
	p = get_recorded();
	if (p == NULL)
	    retval = FAIL;
	else
	{

	    vim_unescape_csi(p);


	    old_y_previous = y_previous;
	    old_y_current = y_current;

	    retval = stuff_yank(regname, p);

	    y_previous = old_y_previous;
	    y_current = old_y_current;
	}
    }
    return retval;
}
