ll_free_all(qf_info_T **pqi)
{
    int		i;
    qf_info_T	*qi;

    qi = *pqi;
    if (qi == NULL)
	return;
    *pqi = NULL;


    if (quickfix_busy > 0)
    {
	locstack_queue_delreq(qi);
	return;
    }

    qi->qf_refcount--;
    if (qi->qf_refcount < 1)
    {


	wipe_qf_buffer(qi);

	for (i = 0; i < qi->qf_listcount; ++i)
	    qf_free(qf_get_list(qi, i));
	vim_free(qi);
    }
}
