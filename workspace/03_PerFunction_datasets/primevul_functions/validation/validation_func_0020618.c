vim_tempname(
    int	    extra_char UNUSED,
    int	    keep UNUSED)
{
#ifdef USE_TMPNAM
    char_u	itmp[L_tmpnam];
#else
    char_u	itmp[TEMPNAMELEN];
#endif

#ifdef TEMPDIRNAMES
    static char	*(tempdirs[]) = {TEMPDIRNAMES};
    int		i;
# ifndef EEXIST
    stat_T	st;
# endif


    if (vim_tempdir == NULL)
    {


	for (i = 0; i < (int)(sizeof(tempdirs) / sizeof(char *)); ++i)
	{
# ifndef HAVE_MKDTEMP
	    size_t	itmplen;
	    long	nr;
	    long	off;
# endif


	    expand_env((char_u *)tempdirs[i], itmp, TEMPNAMELEN - 20);
	    if (itmp[0] != '$' && mch_isdir(itmp))
	    {

		add_pathsep(itmp);

# ifdef HAVE_MKDTEMP
		{
#  if defined(UNIX) || defined(VMS)


		    mode_t	umask_save = umask(077);
#  endif

		    STRCAT(itmp, "vXXXXXX");
		    if (mkdtemp((char *)itmp) != NULL)
			vim_settempdir(itmp);
#  if defined(UNIX) || defined(VMS)
		    (void)umask(umask_save);
#  endif
		}
# else


		nr = (mch_get_pid() + (long)time(NULL)) % 1000000L;
		itmplen = STRLEN(itmp);


		for (off = 0; off < 10000L; ++off)
		{
		    int		r;
#  if defined(UNIX) || defined(VMS)
		    mode_t	umask_save;
#  endif

		    sprintf((char *)itmp + itmplen, "v%ld", nr + off);
#  ifndef EEXIST


		    if (mch_stat((char *)itmp, &st) >= 0)
			continue;
#  endif
#  if defined(UNIX) || defined(VMS)


		    umask_save = umask(077);
#  endif
		    r = vim_mkdir(itmp, 0700);
#  if defined(UNIX) || defined(VMS)
		    (void)umask(umask_save);
#  endif
		    if (r == 0)
		    {
			vim_settempdir(itmp);
			break;
		    }
#  ifdef EEXIST


		    if (errno != EEXIST)
#  endif
			break;
		}
# endif
		if (vim_tempdir != NULL)
		    break;
	    }
	}
    }

    if (vim_tempdir != NULL)
    {


	sprintf((char *)itmp, "%s%ld", vim_tempdir, temp_count++);
	return vim_strsave(itmp);
    }

    return NULL;

#else

# ifdef WIN3264
    char	szTempFile[_MAX_PATH + 1];
    char	buf4[4];
    char_u	*retval;
    char_u	*p;

    STRCPY(itmp, "");
    if (GetTempPath(_MAX_PATH, szTempFile) == 0)
    {
	szTempFile[0] = '.';
	szTempFile[1] = NUL;
    }
    strcpy(buf4, "VIM");
    buf4[2] = extra_char;
    if (GetTempFileName(szTempFile, buf4, 0, (LPSTR)itmp) == 0)
	return NULL;
    if (!keep)

	(void)DeleteFile((LPSTR)itmp);


    retval = vim_strsave(itmp);
    if (*p_shcf == '-' || p_ssl)
	for (p = retval; *p; ++p)
	    if (*p == '\\')
		*p = '/';
    return retval;

# else

#  ifdef USE_TMPNAM
    char_u	*p;


    p = tmpnam((char *)itmp);
    if (p == NULL || *p == NUL)
	return NULL;
#  else
    char_u	*p;

#   ifdef VMS_TEMPNAM


    sprintf((char *)itmp, "VIM%c", extra_char);
    p = (char_u *)tempnam("tmp:", (char *)itmp);
    if (p != NULL)
    {


	STRCPY(itmp, p);
	STRCAT(itmp, ".txt");
	free(p);
    }
    else
	return NULL;
#   else
    STRCPY(itmp, TEMPNAME);
    if ((p = vim_strchr(itmp, '?')) != NULL)
	*p = extra_char;
    if (mktemp((char *)itmp) == NULL)
	return NULL;
#   endif
#  endif

    return vim_strsave(itmp);
# endif
#endif
}
