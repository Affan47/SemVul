config_tuning(struct configuration *p, struct tuning *tp)
{
	const char *t;

	if ((t = gettoken(p)) != t_open)
		return t;
	while ((t = gettoken(p)) != t_close) {
		if (t != t_string)
			return t;
		if (!strcasecmp(p->tokbuf, c_timeout))
			t = config_int(p, &tp->timeout);
		else if (!strcasecmp(p->tokbuf, c_buf_size))
			t = config_int(p, &tp->buf_size);
		else if (!strcasecmp(p->tokbuf, c_input_buf_size))
			t = config_int(p, &tp->input_buf_size);
		else if (!strcasecmp(p->tokbuf, c_num_connections))
			t = config_int(p, &tp->num_connections);
		else if (!strcasecmp(p->tokbuf, c_accept_multi))
			t = config_flag(p, &tp->accept_multi);
		else if (!strcasecmp(p->tokbuf, c_num_headers))
			t = config_int(p, &tp->num_headers);
		else if (!strcasecmp(p->tokbuf, c_script_timeout))
			t = config_int(p, &tp->script_timeout);
		else if (!strcasecmp(p->tokbuf, c_script_buf_size))
			t = config_int(p, &tp->script_buf_size);
		else if (!strcasecmp(p->tokbuf, c_clobber))
			t = config_flag(p, &tp->clobber);
		else if (!strcasecmp(p->tokbuf, c_wait))
			t = config_int(p, &tp->wait_timeout);
		else if (!strcasecmp(p->tokbuf, c_num_processes))
			t = config_smallint(p, &tp->num_processes);
		else if (!strcasecmp(p->tokbuf, c_greedy))
			t = config_flag(p, &tp->greedy);
		else if (!strcasecmp(p->tokbuf, c_adjust_output_buffer))
			t = config_flag(p, &tp->adjust_output_buffer);
		else
			t = e_keyword;
		if (t)
			return t;
	}
	return 0;
}
