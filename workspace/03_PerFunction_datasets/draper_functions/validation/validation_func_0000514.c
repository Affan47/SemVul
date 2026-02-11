msg_trunc_attr(s, force, attr)
    char_u	*s;
    int		force;
    int		attr;
{
    int		n;


    add_msg_hist(s, -1, attr);

    s = msg_may_trunc(force, s);

    msg_hist_off = TRUE;
    n = msg_attr(s, attr);
    msg_hist_off = FALSE;

    if (n)
	return s;
    return NULL;
}
