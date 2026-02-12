emsg(char *s)
{

    if (!emsg_not_now())
	return emsg_core((char_u *)s);
    return TRUE;
}
