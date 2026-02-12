read_file_or_blob(typval_T *argvars, typval_T *rettv, int always_blob)
{
    int		binary = FALSE;
    int		blob = always_blob;
    int		failed = FALSE;
    char_u	*fname;
    FILE	*fd;
    char_u	buf[(IOSIZE/256)*256];
    int		io_size = sizeof(buf);
    int		readlen;
    char_u	*prev	 = NULL;
    long	prevlen  = 0;
    long	prevsize = 0;
    long	maxline  = MAXLNUM;
    long	cnt	 = 0;
    char_u	*p;
    char_u	*start;

    if (argvars[1].v_type != VAR_UNKNOWN)
    {
	if (STRCMP(tv_get_string(&argvars[1]), "b") == 0)
	    binary = TRUE;
	if (STRCMP(tv_get_string(&argvars[1]), "B") == 0)
	    blob = TRUE;

	if (argvars[2].v_type != VAR_UNKNOWN)
	    maxline = (long)tv_get_number(&argvars[2]);
    }

    if ((blob ? rettv_blob_alloc(rettv) : rettv_list_alloc(rettv)) == FAIL)
	return;


    fname = tv_get_string(&argvars[0]);

    if (mch_isdir(fname))
    {
	semsg(_(e_src_is_directory), fname);
	return;
    }
    if (*fname == NUL || (fd = mch_fopen((char *)fname, READBIN)) == NULL)
    {
	semsg(_(e_cant_open_file_str), *fname == NUL ? (char_u *)_("<empty>") : fname);
	return;
    }

    if (blob)
    {
	if (read_blob(fd, rettv->vval.v_blob) == FAIL)
	{
	    semsg(_(e_cant_read_file_str), fname);

	    blob_free(rettv->vval.v_blob);
	    rettv->vval.v_blob = NULL;
	}
	fclose(fd);
	return;
    }

    while (cnt < maxline || maxline < 0)
    {
	readlen = (int)fread(buf, 1, io_size, fd);


	for (p = buf, start = buf;
		p < buf + readlen || (readlen <= 0 && (prevlen > 0 || binary));
		++p)
	{
	    if (readlen <= 0 || *p == '\n')
	    {
		listitem_T  *li;
		char_u	    *s	= NULL;
		long_u	    len = p - start;


		if (readlen > 0 && !binary)
		{
		    while (len > 0 && start[len - 1] == '\r')
			--len;

		    if (len == 0)
			while (prevlen > 0 && prev[prevlen - 1] == '\r')
			    --prevlen;
		}
		if (prevlen == 0)
		    s = vim_strnsave(start, len);
		else
		{


		    if ((s = vim_realloc(prev, prevlen + len + 1)) != NULL)
		    {
			mch_memmove(s + prevlen, start, len);
			s[prevlen + len] = NUL;
			prev = NULL;
			prevlen = prevsize = 0;
		    }
		}
		if (s == NULL)
		{
		    do_outofmem_msg((long_u) prevlen + len + 1);
		    failed = TRUE;
		    break;
		}

		if ((li = listitem_alloc()) == NULL)
		{
		    vim_free(s);
		    failed = TRUE;
		    break;
		}
		li->li_tv.v_type = VAR_STRING;
		li->li_tv.v_lock = 0;
		li->li_tv.vval.v_string = s;
		list_append(rettv->vval.v_list, li);

		start = p + 1;
		if ((++cnt >= maxline && maxline >= 0) || readlen <= 0)
		    break;
	    }
	    else if (*p == NUL)
		*p = '\n';


	    else if (*p == 0xbf && enc_utf8 && !binary)
	    {


		char_u back1 = p >= buf + 1 ? p[-1]
				     : prevlen >= 1 ? prev[prevlen - 1] : NUL;
		char_u back2 = p >= buf + 2 ? p[-2]
			  : p == buf + 1 && prevlen >= 1 ? prev[prevlen - 1]
			  : prevlen >= 2 ? prev[prevlen - 2] : NUL;

		if (back2 == 0xef && back1 == 0xbb)
		{
		    char_u *dest = p - 2;


		    if (start == dest)
			start = p + 1;
		    else
		    {

			int adjust_prevlen = 0;

			if (dest < buf)
			{

			    adjust_prevlen = (int)(buf - dest);
			    dest = buf;
			}
			if (readlen > p - buf + 1)
			    mch_memmove(dest, p + 1, readlen - (p - buf) - 1);
			readlen -= 3 - adjust_prevlen;
			prevlen -= adjust_prevlen;
			p = dest - 1;
		    }
		}
	    }
	}

	if (failed || (cnt >= maxline && maxline >= 0) || readlen <= 0)
	    break;
	if (start < p)
	{

	    if (p - start + prevlen >= prevsize)
	    {

		char_u *newprev;


		if (prevsize == 0)
		    prevsize = (long)(p - start);
		else
		{
		    long grow50pc = (prevsize * 3) / 2;
		    long growmin  = (long)((p - start) * 2 + prevlen);
		    prevsize = grow50pc > growmin ? grow50pc : growmin;
		}
		newprev = vim_realloc(prev, prevsize);
		if (newprev == NULL)
		{
		    do_outofmem_msg((long_u)prevsize);
		    failed = TRUE;
		    break;
		}
		prev = newprev;
	    }

	    mch_memmove(prev + prevlen, start, p - start);
	    prevlen += (long)(p - start);
	}
    }


    if (!failed && maxline < 0)
	while (cnt > -maxline)
	{
	    listitem_remove(rettv->vval.v_list, rettv->vval.v_list->lv_first);
	    --cnt;
	}

    if (failed)
    {

	list_free(rettv->vval.v_list);
	rettv_list_alloc(rettv);
    }

    vim_free(prev);
    fclose(fd);
}
