qf_add_entry(
    qf_list_T	*qfl,
    char_u	*dir,
    char_u	*fname,
    char_u	*module,
    int		bufnum,
    char_u	*mesg,
    long	lnum,
    long	end_lnum,
    int		col,
    int		end_col,
    int		vis_col,
    char_u	*pattern,
    int		nr,
    int		type,
    int		valid)
{
    qfline_T	*qfp;
    qfline_T	**lastp;

    if ((qfp = ALLOC_ONE_ID(qfline_T, aid_qf_qfline)) == NULL)
	return QF_FAIL;
    if (bufnum != 0)
    {
	buf_T *buf = buflist_findnr(bufnum);

	qfp->qf_fnum = bufnum;
	if (buf != NULL)
	    buf->b_has_qf_entry |=
		IS_QF_LIST(qfl) ? BUF_HAS_QF_ENTRY : BUF_HAS_LL_ENTRY;
    }
    else
	qfp->qf_fnum = qf_get_fnum(qfl, dir, fname);
    if ((qfp->qf_text = vim_strsave(mesg)) == NULL)
    {
	vim_free(qfp);
	return QF_FAIL;
    }
    qfp->qf_lnum = lnum;
    qfp->qf_end_lnum = end_lnum;
    qfp->qf_col = col;
    qfp->qf_end_col = end_col;
    qfp->qf_viscol = vis_col;
    if (pattern == NULL || *pattern == NUL)
	qfp->qf_pattern = NULL;
    else if ((qfp->qf_pattern = vim_strsave(pattern)) == NULL)
    {
	vim_free(qfp->qf_text);
	vim_free(qfp);
	return QF_FAIL;
    }
    if (module == NULL || *module == NUL)
	qfp->qf_module = NULL;
    else if ((qfp->qf_module = vim_strsave(module)) == NULL)
    {
	vim_free(qfp->qf_text);
	vim_free(qfp->qf_pattern);
	vim_free(qfp);
	return QF_FAIL;
    }
    qfp->qf_nr = nr;
    if (type != 1 && !vim_isprintc(type))
	type = 0;
    qfp->qf_type = type;
    qfp->qf_valid = valid;

    lastp = &qfl->qf_last;
    if (qf_list_empty(qfl))
    {
	qfl->qf_start = qfp;
	qfl->qf_ptr = qfp;
	qfl->qf_index = 0;
	qfp->qf_prev = NULL;
    }
    else
    {
	qfp->qf_prev = *lastp;
	(*lastp)->qf_next = qfp;
    }
    qfp->qf_next = NULL;
    qfp->qf_cleared = FALSE;
    *lastp = qfp;
    ++qfl->qf_count;
    if (qfl->qf_index == 0 && qfp->qf_valid)
    {
	qfl->qf_index = qfl->qf_count;
	qfl->qf_ptr = qfp;
    }

    return QF_OK;
}
