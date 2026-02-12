smsg(const char *s, ...)
{
    if (IObuff == NULL)
    {


	return msg((char *)s);
    }
    else
    {
	va_list arglist;

	va_start(arglist, s);
	vim_vsnprintf((char *)IObuff, IOSIZE, s, arglist);
	va_end(arglist);
	return msg((char *)IObuff);
    }
}
