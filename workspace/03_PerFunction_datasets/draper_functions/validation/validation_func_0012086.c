PR_Wait(PRMonitor *mon, PRIntervalTime timeout)
{
    PRStatus rv;
    PRUint32 saved_entries;
    pthread_t saved_owner;

    PR_ASSERT(mon != NULL);
    rv = pthread_mutex_lock(&mon->lock);
    PR_ASSERT(0 == rv);

    PR_ASSERT(mon->entryCount > 0);

    PR_ASSERT(pthread_equal(mon->owner, pthread_self()));


    saved_entries = mon->entryCount;
    mon->entryCount = 0;
    _PT_PTHREAD_COPY_THR_HANDLE(mon->owner, saved_owner);
    _PT_PTHREAD_INVALIDATE_THR_HANDLE(mon->owner);


    if (0 != mon->notifyTimes)
    {
        pt_PostNotifiesFromMonitor(&mon->waitCV, mon->notifyTimes);
        mon->notifyTimes = 0;
    }
    rv = pthread_cond_signal(&mon->entryCV);
    PR_ASSERT(0 == rv);

    if (timeout == PR_INTERVAL_NO_TIMEOUT)
        rv = pthread_cond_wait(&mon->waitCV, &mon->lock);
    else
        rv = pt_TimedWait(&mon->waitCV, &mon->lock, timeout);
    PR_ASSERT(0 == rv);

    while (mon->entryCount != 0)
    {
        rv = pthread_cond_wait(&mon->entryCV, &mon->lock);
        PR_ASSERT(0 == rv);
    }
    PR_ASSERT(0 == mon->notifyTimes);

    mon->entryCount = saved_entries;
    _PT_PTHREAD_COPY_THR_HANDLE(saved_owner, mon->owner);

    rv = pthread_mutex_unlock(&mon->lock);
    PR_ASSERT(0 == rv);
    return rv;
}
