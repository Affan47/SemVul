qf_find_first_entry_in_buf(qf_list_T *qfl, int bnr, int *errornr)
{
    qfline_T	*qfp = NULL;
    int		idx = 0;


    FOR_ALL_QFL_ITEMS(qfl, qfp, idx)
	if (qfp->qf_fnum == bnr)
	    break;

    *errornr = idx;
    return qfp;
}
