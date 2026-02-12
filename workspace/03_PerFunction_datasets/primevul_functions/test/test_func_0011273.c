qf_get_entry(
	qf_list_T	*qfl,
	int		errornr,
	int		dir,
	int		*new_qfidx)
{
    qfline_T	*qf_ptr = qfl->qf_ptr;
    int		qfidx = qfl->qf_index;

    if (dir != 0)
	qf_ptr = get_nth_valid_entry(qfl, errornr, dir, &qfidx);
    else if (errornr != 0)
	qf_ptr = get_nth_entry(qfl, errornr, &qfidx);

    *new_qfidx = qfidx;
    return qf_ptr;
}
