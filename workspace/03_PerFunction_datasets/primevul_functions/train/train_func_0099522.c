add_msg_hist(
    char_u	*s,
    int		len,
    int		attr)
{
    struct msg_hist *p;

    if (msg_hist_off || msg_silent != 0)
	return;


    while (msg_hist_len > MAX_MSG_HIST_LEN)
	(void)delete_first_msg();


    p = ALLOC_ONE(struct msg_hist);
    if (p != NULL)
    {
	if (len < 0)
	    len = (int)STRLEN(s);

	while (len > 0 && *s == '\n')
	{
	    ++s;
	    --len;
	}
	while (len > 0 && s[len - 1] == '\n')
	    --len;
	p->msg = vim_strnsave(s, len);
	p->next = NULL;
	p->attr = attr;
	if (last_msg_hist != NULL)
	    last_msg_hist->next = p;
	last_msg_hist = p;
	if (first_msg_hist == NULL)
	    first_msg_hist = last_msg_hist;
	++msg_hist_len;
    }
}
