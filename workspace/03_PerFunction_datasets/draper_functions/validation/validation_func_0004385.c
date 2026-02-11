fm_job_finalize(GObject *object)
{
    g_return_if_fail(object != NULL);
    g_return_if_fail(FM_IS_JOB(object));

    if (G_OBJECT_CLASS(fm_job_parent_class)->finalize)
        (* G_OBJECT_CLASS(fm_job_parent_class)->finalize)(object);

    --n_jobs;
    if(0 == n_jobs)
    {
        g_thread_pool_free(thread_pool, TRUE, FALSE);
        thread_pool = NULL;
    }
}
