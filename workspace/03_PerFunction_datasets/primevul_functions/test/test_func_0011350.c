qf_get_nextline(qfstate_T *state)
{
    int status = QF_FAIL;

    if (state->fd == NULL)
    {
	if (state->tv != NULL)
	{
	    if (state->tv->v_type == VAR_STRING)

		status = qf_get_next_str_line(state);
	    else if (state->tv->v_type == VAR_LIST)

		status = qf_get_next_list_line(state);
	}
	else

	    status = qf_get_next_buf_line(state);
    }
    else

	status = qf_get_next_file_line(state);

    if (status != QF_OK)
	return status;


    if (state->linelen > 0 && state->linebuf[state->linelen - 1] == '\n')
    {
	state->linebuf[state->linelen - 1] = NUL;
#ifdef USE_CRNL
	if (state->linelen > 1 && state->linebuf[state->linelen - 2] == '\r')
	    state->linebuf[state->linelen - 2] = NUL;
#endif
    }

    remove_bom(state->linebuf);

    return QF_OK;
}
