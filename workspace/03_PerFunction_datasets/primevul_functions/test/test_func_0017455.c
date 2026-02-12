out_flush(void)
{
    int	    len;

    if (out_pos != 0)
    {

	len = out_pos;
	out_pos = 0;
	ui_write(out_buf, len, FALSE);
#ifdef FEAT_JOB_CHANNEL
	if (ch_log_output != FALSE)
	{
	    out_buf[len] = NUL;
	    ch_log(NULL, "raw %s output: \"%s\"",
# ifdef FEAT_GUI
			(gui.in_use && !gui.dying && !gui.starting) ? "GUI" :
# endif
			"terminal",
			out_buf);
	    if (ch_log_output == TRUE)
		ch_log_output = FALSE;
	}
#endif
    }
}
