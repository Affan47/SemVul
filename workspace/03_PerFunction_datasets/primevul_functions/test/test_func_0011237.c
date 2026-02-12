wipe_dummy_buffer(buf_T *buf, char_u *dirname_start)
{


    while (buf->b_nwindows > 0)
    {
	int	    did_one = FALSE;
	win_T	    *wp;

	if (firstwin->w_next != NULL)
	    FOR_ALL_WINDOWS(wp)
		if (wp->w_buffer == buf)
		{
		    if (win_close(wp, FALSE) == OK)
			did_one = TRUE;
		    break;
		}
	if (!did_one)
	    return;
    }

    if (curbuf != buf && buf->b_nwindows == 0)
    {
#if defined(FEAT_EVAL)
	cleanup_T   cs;


	enter_cleanup(&cs);
#endif

	wipe_buffer(buf, TRUE);

#if defined(FEAT_EVAL)


	leave_cleanup(&cs);
#endif

	restore_start_dir(dirname_start);
    }
}
