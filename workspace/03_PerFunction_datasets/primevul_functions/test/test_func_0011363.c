get_nth_entry(qf_list_T *qfl, int errornr, int *new_qfidx)
{
    qfline_T	*qf_ptr = qfl->qf_ptr;
    int		qf_idx = qfl->qf_index;


    while (errornr < qf_idx && qf_idx > 1 && qf_ptr->qf_prev != NULL)
    {
	--qf_idx;
	qf_ptr = qf_ptr->qf_prev;
    }

    while (errornr > qf_idx && qf_idx < qfl->qf_count &&
						qf_ptr->qf_next != NULL)
    {
	++qf_idx;
	qf_ptr = qf_ptr->qf_next;
    }

    *new_qfidx = qf_idx;
    return qf_ptr;
}
