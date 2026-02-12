open_exfile(
    char_u	*fname,
    int		forceit,
    char	*mode)
{
    FILE	*fd;

#ifdef UNIX

    if (mch_isdir(fname))
    {
	semsg(_(e_src_is_directory), fname);
	return NULL;
    }
#endif
    if (!forceit && *mode != 'a' && vim_fexists(fname))
    {
	semsg(_("E189: \"%s\" exists (add ! to override)"), fname);
	return NULL;
    }

    if ((fd = mch_fopen((char *)fname, mode)) == NULL)
	semsg(_("E190: Cannot open \"%s\" for writing"), fname);

    return fd;
}
