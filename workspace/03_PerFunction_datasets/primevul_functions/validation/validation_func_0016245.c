parse_queued_messages(void)
{
    int	    old_curwin_id;
    int	    old_curbuf_fnum;
    int	    i;
    int	    save_may_garbage_collect = may_garbage_collect;
    static int entered = 0;
    int	    was_safe = get_was_safe_state();


    if (updating_screen || dont_parse_messages)
	return;


    if (curbuf == NULL || curwin == NULL)
       return;

    old_curbuf_fnum = curbuf->b_fnum;
    old_curwin_id = curwin->w_id;

    ++entered;


    may_garbage_collect = FALSE;


    for (i = 0; i < MAX_REPEAT_PARSE; ++i)
    {

# if (defined(MSWIN) || defined(__HAIKU__)) && defined(FEAT_JOB_CHANNEL)
	channel_handle_events(FALSE);
# endif

# ifdef FEAT_NETBEANS_INTG

	netbeans_parse_messages();
# endif
# ifdef FEAT_JOB_CHANNEL

	channel_write_any_lines();


	channel_parse_messages();
# endif
# if defined(FEAT_CLIENTSERVER) && defined(FEAT_X11)

	server_parse_messages();
# endif
# ifdef FEAT_JOB_CHANNEL


	if (job_check_ended())
	    continue;
# endif
# ifdef FEAT_TERMINAL
	free_unused_terminals();
# endif
# ifdef FEAT_SOUND_CANBERRA
	if (has_sound_callback_in_queue())
	    invoke_sound_callback();
# endif
#ifdef SIGUSR1
	if (got_sigusr1)
	{
	    apply_autocmds(EVENT_SIGUSR1, NULL, NULL, FALSE, curbuf);
	    got_sigusr1 = FALSE;
	}
#endif
	break;
    }


    if (entered == 1 && was_safe)
	may_trigger_safestateagain();

    may_garbage_collect = save_may_garbage_collect;


    if (curwin->w_id != old_curwin_id || curbuf->b_fnum != old_curbuf_fnum)
	ins_char_typebuf(K_IGNORE, 0);

    --entered;
}
