global_exe(char_u *cmd)
{
    linenr_T old_lcount;
    buf_T    *old_buf = curbuf;
    linenr_T lnum;


    setpcmark();


    msg_didout = TRUE;

    sub_nsubs = 0;
    sub_nlines = 0;
    global_need_beginline = FALSE;
    global_busy = 1;
    old_lcount = curbuf->b_ml.ml_line_count;
    while (!got_int && (lnum = ml_firstmarked()) != 0 && global_busy == 1)
    {
	global_exe_one(cmd, lnum);
	ui_breakcheck();
    }

    global_busy = 0;
    if (global_need_beginline)
	beginline(BL_WHITE | BL_FIX);
    else
	check_cursor();


    changed_line_abv_curs();


    if (msg_col == 0 && msg_scrolled == 0)
	msg_didout = FALSE;


    if (!do_sub_msg(FALSE) && curbuf == old_buf)
	msgmore(curbuf->b_ml.ml_line_count - old_lcount);
}
