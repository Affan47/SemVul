smsg_attr_keep(int attr, const char *s, ...)
{
    if (IObuff == NULL)
    {


	return msg_attr_keep((char *)s, attr, TRUE);
    }
    else
    {
	va_list arglist;

	va_start(arglist, s);
	vim_vsnprintf((char *)IObuff, IOSIZE, s, arglist);
	va_end(arglist);
	return msg_attr_keep((char *)IObuff, attr, TRUE);
    }
}
