is_qf_entry_present(qf_list_T *qfl, qfline_T *qf_ptr)
{
    qfline_T	*qfp;
    int		i;


    FOR_ALL_QFL_ITEMS(qfl, qfp, i)
	if (qfp == qf_ptr)
	    break;

    if (i > qfl->qf_count)
	return FALSE;

    return TRUE;
}
