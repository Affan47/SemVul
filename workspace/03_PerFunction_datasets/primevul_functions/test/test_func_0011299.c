qf_find_entry_before_pos(
	int		bnr,
	pos_T		*pos,
	int		linewise,
	qfline_T	*qfp,
	int		*errornr)
{

    while (qfp->qf_next != NULL
	    && qfp->qf_next->qf_fnum == bnr
	    && qf_entry_before_pos(qfp->qf_next, pos, linewise))
    {
	qfp = qfp->qf_next;
	++*errornr;
    }

    if (qf_entry_on_or_after_pos(qfp, pos, linewise))
	return NULL;

    if (linewise)

	qfp = qf_find_first_entry_on_line(qfp, errornr);

    return qfp;
}
