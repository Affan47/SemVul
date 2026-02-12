copy_loclist_entries(qf_list_T *from_qfl, qf_list_T *to_qfl)
{
    int		i;
    qfline_T    *from_qfp;
    qfline_T    *prevp;


    FOR_ALL_QFL_ITEMS(from_qfl, from_qfp, i)
    {
	if (qf_add_entry(to_qfl,
		    NULL,
		    NULL,
		    from_qfp->qf_module,
		    0,
		    from_qfp->qf_text,
		    from_qfp->qf_lnum,
		    from_qfp->qf_end_lnum,
		    from_qfp->qf_col,
		    from_qfp->qf_end_col,
		    from_qfp->qf_viscol,
		    from_qfp->qf_pattern,
		    from_qfp->qf_nr,
		    0,
		    from_qfp->qf_valid) == QF_FAIL)
	    return FAIL;


	prevp = to_qfl->qf_last;
	prevp->qf_fnum = from_qfp->qf_fnum;
	prevp->qf_type = from_qfp->qf_type;
	if (from_qfl->qf_ptr == from_qfp)
	    to_qfl->qf_ptr = prevp;
    }

    return OK;
}
