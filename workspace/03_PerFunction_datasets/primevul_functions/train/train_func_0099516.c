semsg(const char *s, ...)
{

    if (!emsg_not_now())
    {
	if (IObuff == NULL)
	{


	    return emsg_core((char_u *)s);
	}
	else
	{
	    va_list ap;

	    va_start(ap, s);
	    vim_vsnprintf((char *)IObuff, IOSIZE, s, ap);
	    va_end(ap);
	    return emsg_core(IObuff);
	}
    }
    return TRUE;
}
