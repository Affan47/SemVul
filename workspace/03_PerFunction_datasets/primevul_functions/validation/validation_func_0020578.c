check_timestamps(
    int		focus)
{
    buf_T	*buf;
    int		didit = 0;
    int		n;


    if (no_check_timestamps > 0)
	return FALSE;


    if (focus && did_check_timestamps)
    {
	need_check_timestamps = TRUE;
	return FALSE;
    }

    if (!stuff_empty() || global_busy || !typebuf_typed()
#ifdef FEAT_AUTOCMD
			|| autocmd_busy || curbuf_lock > 0 || allbuf_lock > 0
#endif
					)
	need_check_timestamps = TRUE;
    else
    {
	++no_wait_return;
	did_check_timestamps = TRUE;
	already_warned = FALSE;
	FOR_ALL_BUFFERS(buf)
	{

	    if (buf->b_nwindows > 0)
	    {
		bufref_T bufref;

		set_bufref(&bufref, buf);
		n = buf_check_timestamp(buf, focus);
		if (didit < n)
		    didit = n;
		if (n > 0 && !bufref_valid(&bufref))
		{


		    buf = firstbuf;
		    continue;
		}
	    }
	}
	--no_wait_return;
	need_check_timestamps = FALSE;
	if (need_wait_return && didit == 2)
	{

	    msg_puts((char_u *)"\n");
	    out_flush();
	}
    }
    return didit;
}
