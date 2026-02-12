ins_compl_check_keys(int frequency, int in_compl_func)
{
    static int	count = 0;
    int		c;


    if (!in_compl_func && (using_script() || ex_normal_busy))
	return;


    if (++count < frequency)
	return;
    count = 0;


    c = vpeekc_any();
    if (c != NUL)
    {
	if (vim_is_ctrl_x_key(c) && c != Ctrl_X && c != Ctrl_R)
	{
	    c = safe_vgetc();
	    compl_shows_dir = ins_compl_key2dir(c);
	    (void)ins_compl_next(FALSE, ins_compl_key2count(c),
				      c != K_UP && c != K_DOWN, in_compl_func);
	}
	else
	{


	    c = safe_vgetc();
	    if (c != K_IGNORE)
	    {


		if (c != Ctrl_R && KeyTyped)
		    compl_interrupted = TRUE;

		vungetc(c);
	    }
	}
    }
    if (compl_pending != 0 && !got_int && !compl_no_insert)
    {
	int todo = compl_pending > 0 ? compl_pending : -compl_pending;

	compl_pending = 0;
	(void)ins_compl_next(FALSE, todo, TRUE, in_compl_func);
    }
}
