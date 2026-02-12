emsg_core(char_u *s)
{
    int		attr;
    char_u	*p;
    int		r;
#ifdef FEAT_EVAL
    int		ignore = FALSE;
    int		severe;
#endif

#ifdef FEAT_EVAL

    if (ignore_error(s))

	return msg_use_printf() ? FALSE : msg((char *)s);
#endif

    ++called_emsg;

#ifdef FEAT_EVAL


    severe = emsg_severe;
    emsg_severe = FALSE;
#endif

    if (!emsg_off || vim_strchr(p_debug, 't') != NULL)
    {
#ifdef FEAT_EVAL


	if (cause_errthrow(s, severe, &ignore) == TRUE)
	{
	    if (!ignore)
		++did_emsg;
	    return TRUE;
	}

	if (in_assert_fails && emsg_assert_fails_msg == NULL)
	{
	    emsg_assert_fails_msg = vim_strsave(s);
	    emsg_assert_fails_lnum = SOURCING_LNUM;
	    vim_free(emsg_assert_fails_context);
	    emsg_assert_fails_context = vim_strsave(
			 SOURCING_NAME == NULL ? (char_u *)"" : SOURCING_NAME);
	}


	set_vim_var_string(VV_ERRMSG, s, -1);
#endif


	if (emsg_silent != 0)
	{
#ifdef FEAT_EVAL
	    ++did_emsg_silent;
#endif
	    if (emsg_noredir == 0)
	    {
		msg_start();
		p = get_emsg_source();
		if (p != NULL)
		{
		    STRCAT(p, "\n");
		    redir_write(p, -1);
		    vim_free(p);
		}
		p = get_emsg_lnum();
		if (p != NULL)
		{
		    STRCAT(p, "\n");
		    redir_write(p, -1);
		    vim_free(p);
		}
		redir_write(s, -1);
	    }
#ifdef FEAT_EVAL


	    if (emsg_silent == emsg_silent_def)
		++did_emsg_def;
#endif
#ifdef FEAT_JOB_CHANNEL
	    ch_log(NULL, "ERROR silent: %s", (char *)s);
#endif
	    return TRUE;
	}

	ex_exitval = 1;


	msg_silent = 0;
	cmd_silent = FALSE;

	if (global_busy)
	    ++global_busy;

	if (p_eb)
	    beep_flush();
	else
	    flush_buffers(FLUSH_MINIMAL);
	++did_emsg;
#ifdef FEAT_EVAL
	++uncaught_emsg;
#endif
    }

    emsg_on_display = TRUE;
    ++msg_scroll;
    attr = HL_ATTR(HLF_E);
    if (msg_scrolled != 0)
	need_wait_return = TRUE;


#ifdef FEAT_JOB_CHANNEL
    emsg_to_channel_log = TRUE;
#endif


    msg_source(attr);


    msg_nowait = FALSE;
    r = msg_attr((char *)s, attr);

#ifdef FEAT_JOB_CHANNEL
    emsg_to_channel_log = FALSE;
#endif
    return r;
}
