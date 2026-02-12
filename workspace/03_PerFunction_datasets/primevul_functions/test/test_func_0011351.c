ex_cbuffer(exarg_T *eap)
{
    buf_T	*buf = NULL;
    qf_info_T	*qi;
    char_u	*au_name = NULL;
    int		res;
    int_u	save_qfid;
    win_T	*wp = NULL;
    char_u	*qf_title;
    linenr_T	line1;
    linenr_T	line2;

    au_name = cbuffer_get_auname(eap->cmdidx);
    if (au_name != NULL && apply_autocmds(EVENT_QUICKFIXCMDPRE, au_name,
					curbuf->b_fname, TRUE, curbuf))
    {
#ifdef FEAT_EVAL
	if (aborting())
	    return;
#endif
    }


    qi = qf_cmd_get_or_alloc_stack(eap, &wp);
    if (qi == NULL)
	return;

    if (cbuffer_process_args(eap, &buf, &line1, &line2) == FAIL)
	return;

    qf_title = qf_cmdtitle(*eap->cmdlinep);

    if (buf->b_sfname)
    {
	vim_snprintf((char *)IObuff, IOSIZE, "%s (%s)",
		(char *)qf_title, (char *)buf->b_sfname);
	qf_title = IObuff;
    }

    incr_quickfix_busy();

    res = qf_init_ext(qi, qi->qf_curlist, NULL, buf, NULL, p_efm,
	    (eap->cmdidx != CMD_caddbuffer
	     && eap->cmdidx != CMD_laddbuffer),
	    line1, line2,
	    qf_title, NULL);
    if (qf_stack_empty(qi))
    {
	decr_quickfix_busy();
	return;
    }
    if (res >= 0)
	qf_list_changed(qf_get_curlist(qi));


    save_qfid = qf_get_curlist(qi)->qf_id;
    if (au_name != NULL)
    {
	buf_T *curbuf_old = curbuf;

	apply_autocmds(EVENT_QUICKFIXCMDPOST, au_name, curbuf->b_fname,
								TRUE, curbuf);
	if (curbuf != curbuf_old)


	    res = 0;
    }


    if (res > 0 && (eap->cmdidx == CMD_cbuffer ||
		eap->cmdidx == CMD_lbuffer)
	    && qflist_valid(wp, save_qfid))

	qf_jump_first(qi, save_qfid, eap->forceit);

    decr_quickfix_busy();
}
