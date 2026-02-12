qf_init_ext(
    qf_info_T	    *qi,
    int		    qf_idx,
    char_u	    *efile,
    buf_T	    *buf,
    typval_T	    *tv,
    char_u	    *errorformat,
    int		    newlist,
    linenr_T	    lnumfirst,
    linenr_T	    lnumlast,
    char_u	    *qf_title,
    char_u	    *enc)
{
    qf_list_T	    *qfl;
    qfstate_T	    state;
    qffields_T	    fields;
    qfline_T	    *old_last = NULL;
    int		    adding = FALSE;
    static efm_T    *fmt_first = NULL;
    char_u	    *efm;
    static char_u   *last_efm = NULL;
    int		    retval = -1;
    int		    status;


    VIM_CLEAR(qf_last_bufname);

    CLEAR_FIELD(state);
    CLEAR_FIELD(fields);
    if ((qf_alloc_fields(&fields) == FAIL) ||
		(qf_setup_state(&state, enc, efile, tv, buf,
					lnumfirst, lnumlast) == FAIL))
	goto qf_init_end;

    if (newlist || qf_idx == qi->qf_listcount)
    {

	qf_new_list(qi, qf_title);
	qf_idx = qi->qf_curlist;
	qfl = qf_get_list(qi, qf_idx);
    }
    else
    {

	adding = TRUE;
	qfl = qf_get_list(qi, qf_idx);
	if (!qf_list_empty(qfl))
	    old_last = qfl->qf_last;
    }


    if (errorformat == p_efm && tv == NULL && *buf->b_p_efm != NUL)
	efm = buf->b_p_efm;
    else
	efm = errorformat;


    if (last_efm == NULL || (STRCMP(last_efm, efm) != 0))
    {

	VIM_CLEAR(last_efm);
	free_efm_list(&fmt_first);


	fmt_first = parse_efm_option(efm);
	if (fmt_first != NULL)
	    last_efm = vim_strsave(efm);
    }

    if (fmt_first == NULL)
	goto error2;


    got_int = FALSE;


    while (!got_int)
    {
	status = qf_init_process_nextline(qfl, fmt_first, &state, &fields);
	if (status == QF_NOMEM)
	    goto qf_init_end;
	if (status == QF_END_OF_INPUT)
	    break;
	if (status == QF_FAIL)
	    goto error2;

	line_breakcheck();
    }
    if (state.fd == NULL || !ferror(state.fd))
    {
	if (qfl->qf_index == 0)
	{

	    qfl->qf_ptr = qfl->qf_start;
	    qfl->qf_index = 1;
	    qfl->qf_nonevalid = TRUE;
	}
	else
	{
	    qfl->qf_nonevalid = FALSE;
	    if (qfl->qf_ptr == NULL)
		qfl->qf_ptr = qfl->qf_start;
	}

	retval = qfl->qf_count;
	goto qf_init_end;
    }
    emsg(_(e_error_while_reading_errorfile));
error2:
    if (!adding)
    {

	qf_free(qfl);
	qi->qf_listcount--;
	if (qi->qf_curlist > 0)
	    --qi->qf_curlist;
    }
qf_init_end:
    if (qf_idx == qi->qf_curlist)
	qf_update_buffer(qi, old_last);
    qf_cleanup_state(&state);
    qf_free_fields(&fields);

    return retval;
}
