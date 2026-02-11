globus_l_gram_job_manager_staging_match(
    void *                              datum,
    void *                              arg)
{
    globus_gram_job_manager_staging_info_t *
                                        item;
    globus_gram_job_manager_staging_info_t *
                                        query;

    item = datum;
    query = arg;

    globus_assert(item->type == query->type);

    if((strcmp(item->evaled_from, query->evaled_from) == 0) &&
       (strcmp(item->evaled_to, query->evaled_to) == 0))
    {
        return GLOBUS_TRUE;
    }
    else
    {
        return GLOBUS_FALSE;
    }
}
