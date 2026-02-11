serve_sticky (char *arg)
{
    FILE *f;

    if (error_pending ()
# ifdef PROXY_SUPPORT
	|| proxy_log
# endif
       ) return;

    f = CVS_FOPEN (CVSADM_TAG, "w+");
    if (f == NULL)
    {
	int save_errno = errno;
	if (alloc_pending (80 + strlen (CVSADM_TAG)))
	    sprintf (pending_error_text, "E cannot open %s", CVSADM_TAG);
	pending_error = save_errno;
	return;
    }
    if (fprintf (f, "%s\n", arg) < 0)
    {
	int save_errno = errno;
	if (alloc_pending (80 + strlen (CVSADM_TAG)))
	    sprintf (pending_error_text, "E cannot write to %s", CVSADM_TAG);
	pending_error = save_errno;
	return;
    }
    if (fclose (f) == EOF)
    {
	int save_errno = errno;
	if (alloc_pending (80 + strlen (CVSADM_TAG)))
	    sprintf (pending_error_text, "E cannot close %s", CVSADM_TAG);
	pending_error = save_errno;
	return;
    }
}
