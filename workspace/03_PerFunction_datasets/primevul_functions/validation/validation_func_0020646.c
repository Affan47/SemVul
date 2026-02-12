vim_rename(char_u *from, char_u *to)
{
    int		fd_in;
    int		fd_out;
    int		n;
    char	*errmsg = NULL;
    char	*buffer;
#ifdef AMIGA
    BPTR	flock;
#endif
    stat_T	st;
    long	perm;
#ifdef HAVE_ACL
    vim_acl_T	acl;
#endif
    int		use_tmp_file = FALSE;


    if (fnamecmp(from, to) == 0)
    {
	if (p_fic && STRCMP(gettail(from), gettail(to)) != 0)
	    use_tmp_file = TRUE;
	else
	    return 0;
    }


    if (mch_stat((char *)from, &st) < 0)
	return -1;

#ifdef UNIX
    {
	stat_T	st_to;


	if (mch_stat((char *)to, &st_to) >= 0
		&& st.st_dev == st_to.st_dev
		&& st.st_ino == st_to.st_ino)
	    use_tmp_file = TRUE;
    }
#endif
#ifdef WIN3264
    {
	BY_HANDLE_FILE_INFORMATION info1, info2;


	if (win32_fileinfo(from, &info1) == FILEINFO_OK
		&& win32_fileinfo(to, &info2) == FILEINFO_OK
		&& info1.dwVolumeSerialNumber == info2.dwVolumeSerialNumber
		&& info1.nFileIndexHigh == info2.nFileIndexHigh
		&& info1.nFileIndexLow == info2.nFileIndexLow)
	    use_tmp_file = TRUE;
    }
#endif

    if (use_tmp_file)
    {
	char	tempname[MAXPATHL + 1];


	if (STRLEN(from) >= MAXPATHL - 5)
	    return -1;
	STRCPY(tempname, from);
	for (n = 123; n < 99999; ++n)
	{
	    sprintf((char *)gettail((char_u *)tempname), "%d", n);
	    if (mch_stat(tempname, &st) < 0)
	    {
		if (mch_rename((char *)from, tempname) == 0)
		{
		    if (mch_rename(tempname, (char *)to) == 0)
			return 0;


		    mch_rename(tempname, (char *)from);
		    return -1;
		}


		return -1;
	    }
	}
	return -1;
    }


#ifdef AMIGA


    flock = Lock((UBYTE *)from, (long)ACCESS_READ);
#endif
    mch_remove(to);
#ifdef AMIGA
    if (flock)
	UnLock(flock);
#endif


    if (mch_rename((char *)from, (char *)to) == 0)
	return 0;


    perm = mch_getperm(from);
#ifdef HAVE_ACL

    acl = mch_get_acl(from);
#endif
    fd_in = mch_open((char *)from, O_RDONLY|O_EXTRA, 0);
    if (fd_in == -1)
    {
#ifdef HAVE_ACL
	mch_free_acl(acl);
#endif
	return -1;
    }


    fd_out = mch_open((char *)to,
		       O_CREAT|O_EXCL|O_WRONLY|O_EXTRA|O_NOFOLLOW, (int)perm);
    if (fd_out == -1)
    {
	close(fd_in);
#ifdef HAVE_ACL
	mch_free_acl(acl);
#endif
	return -1;
    }

    buffer = (char *)alloc(BUFSIZE);
    if (buffer == NULL)
    {
	close(fd_out);
	close(fd_in);
#ifdef HAVE_ACL
	mch_free_acl(acl);
#endif
	return -1;
    }

    while ((n = read_eintr(fd_in, buffer, BUFSIZE)) > 0)
	if (write_eintr(fd_out, buffer, n) != n)
	{
	    errmsg = _("E208: Error writing to \"%s\"");
	    break;
	}

    vim_free(buffer);
    close(fd_in);
    if (close(fd_out) < 0)
	errmsg = _("E209: Error closing \"%s\"");
    if (n < 0)
    {
	errmsg = _("E210: Error reading \"%s\"");
	to = from;
    }
#ifndef UNIX
    mch_setperm(to, perm);
#endif
#ifdef HAVE_ACL
    mch_set_acl(to, acl);
    mch_free_acl(acl);
#endif
#if defined(HAVE_SELINUX) || defined(HAVE_SMACK)
    mch_copy_sec(from, to);
#endif
    if (errmsg != NULL)
    {
	EMSG2(errmsg, to);
	return -1;
    }
    mch_remove(from);
    return 0;
}
