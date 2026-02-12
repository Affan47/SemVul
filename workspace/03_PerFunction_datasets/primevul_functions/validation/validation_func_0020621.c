buf_modname(
    int	    shortname,
    char_u  *fname,
    char_u  *ext,
    int	    prepend_dot)
{
    char_u	*retval;
    char_u	*s;
    char_u	*e;
    char_u	*ptr;
    int		fnamelen, extlen;

    extlen = (int)STRLEN(ext);


    if (fname == NULL || *fname == NUL)
    {
	retval = alloc((unsigned)(MAXPATHL + extlen + 3));
	if (retval == NULL)
	    return NULL;
	if (mch_dirname(retval, MAXPATHL) == FAIL ||
				     (fnamelen = (int)STRLEN(retval)) == 0)
	{
	    vim_free(retval);
	    return NULL;
	}
	if (!after_pathsep(retval, retval + fnamelen))
	{
	    retval[fnamelen++] = PATHSEP;
	    retval[fnamelen] = NUL;
	}
	prepend_dot = FALSE;
    }
    else
    {
	fnamelen = (int)STRLEN(fname);
	retval = alloc((unsigned)(fnamelen + extlen + 3));
	if (retval == NULL)
	    return NULL;
	STRCPY(retval, fname);
#ifdef VMS
	vms_remove_version(retval);
#endif
    }


    for (ptr = retval + fnamelen; ptr > retval; MB_PTR_BACK(retval, ptr))
    {
	if (*ext == '.'
#ifdef USE_LONG_FNAME
		    && (!USE_LONG_FNAME || shortname)
#else
		    && shortname
#endif
								)
	    if (*ptr == '.')
		*ptr = '_';
	if (vim_ispathsep(*ptr))
	{
	    ++ptr;
	    break;
	}
    }


    if (STRLEN(ptr) > (unsigned)BASENAMELEN)
	ptr[BASENAMELEN] = '\0';

    s = ptr + STRLEN(ptr);


#ifdef USE_LONG_FNAME
    if (!USE_LONG_FNAME || shortname)
#else
    if (shortname)
#endif
    {


	if (fname == NULL || *fname == NUL
				   || vim_ispathsep(fname[STRLEN(fname) - 1]))
	{
	    if (*ext == '.')
		*s++ = '_';
	}


	else if (*ext == '.')
	{
	    if ((size_t)(s - ptr) > (size_t)8)
	    {
		s = ptr + 8;
		*s = '\0';
	    }
	}


	else if ((e = vim_strchr(ptr, '.')) == NULL)
	    *s++ = '.';


	else if ((int)STRLEN(e) + extlen > 4)
	    s = e + 4 - extlen;
    }
#if defined(USE_LONG_FNAME) || defined(WIN3264)


    else if ((fname == NULL || *fname == NUL) && *ext == '.')
	*s++ = '_';
#endif


    STRCPY(s, ext);


    if (prepend_dot && !shortname && *(e = gettail(retval)) != '.'
#ifdef USE_LONG_FNAME
	    && USE_LONG_FNAME
#endif
				)
    {
	STRMOVE(e + 1, e);
	*e = '.';
    }


    if (fname != NULL && STRCMP(fname, retval) == 0)
    {

	while (--s >= ptr)
	{
	    if (*s != '_')
	    {
		*s = '_';
		break;
	    }
	}
	if (s < ptr)
	    *ptr = 'v';
    }
    return retval;
}
