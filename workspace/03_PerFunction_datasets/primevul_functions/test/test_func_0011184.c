qf_parse_line(
	qf_list_T	*qfl,
	char_u		*linebuf,
	int		linelen,
	efm_T		*fmt_first,
	qffields_T	*fields)
{
    efm_T		*fmt_ptr;
    int			idx = 0;
    char_u		*tail = NULL;
    int			status;

restofline:

    if (fmt_start == NULL)
	fmt_ptr = fmt_first;
    else
    {

	fmt_ptr = fmt_start;
	fmt_start = NULL;
    }


    fields->valid = TRUE;
    for ( ; fmt_ptr != NULL; fmt_ptr = fmt_ptr->next)
    {
	idx = fmt_ptr->prefix;
	status = qf_parse_get_fields(linebuf, linelen, fmt_ptr, fields,
				qfl->qf_multiline, qfl->qf_multiscan, &tail);
	if (status == QF_NOMEM)
	    return status;
	if (status == QF_OK)
	    break;
    }
    qfl->qf_multiscan = FALSE;

    if (fmt_ptr == NULL || idx == 'D' || idx == 'X')
    {
	if (fmt_ptr != NULL)
	{

	    status = qf_parse_dir_pfx(idx, fields, qfl);
	    if (status != QF_OK)
		return status;
	}

	status = qf_parse_line_nomatch(linebuf, linelen, fields);
	if (status != QF_OK)
	    return status;

	if (fmt_ptr == NULL)
	    qfl->qf_multiline = qfl->qf_multiignore = FALSE;
    }
    else if (fmt_ptr != NULL)
    {

	if (fmt_ptr->conthere)
	    fmt_start = fmt_ptr;

	if (vim_strchr((char_u *)"AEWIN", idx) != NULL)
	{
	    qfl->qf_multiline = TRUE;
	    qfl->qf_multiignore = FALSE;
	}
	else if (vim_strchr((char_u *)"CZ", idx) != NULL)
	{
	    status = qf_parse_multiline_pfx(idx, qfl, fields);
	    if (status != QF_OK)
		return status;
	}
	else if (vim_strchr((char_u *)"OPQ", idx) != NULL)
	{
	    status = qf_parse_file_pfx(idx, fields, qfl, tail);
	    if (status == QF_MULTISCAN)
		goto restofline;
	}
	if (fmt_ptr->flags == '-')
	{
	    if (qfl->qf_multiline)

		qfl->qf_multiignore = TRUE;
	    return QF_IGNORE_LINE;
	}
    }

    return QF_OK;
}
