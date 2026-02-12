alist_name(aentry_T *aep)
{
    buf_T	*bp;


    bp = buflist_findnr(aep->ae_fnum);
    if (bp == NULL || bp->b_fname == NULL)
	return aep->ae_fname;
    return bp->b_fname;
}
