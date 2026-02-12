open_exfile(
    char_u	*fname,
    int		forceit,
    char	*mode)
{
    FILE	*fd;

#ifdef UNIX

    if (mch_isdir(fname))
    {
	semsg(_(e_str_is_directory), fname);
	return NULL;
    }
#endif
    if (!forceit && *mode != 'a' && vim_fexists(fname))
    {
	semsg(_(e_str_exists_add_bang_to_override), fname);
	return NULL;
    }

    if ((fd = mch_fopen((char *)fname, mode)) == NULL)
	semsg(_(e_cannot_open_str_for_writing_2), fname);

    return fd;
}
