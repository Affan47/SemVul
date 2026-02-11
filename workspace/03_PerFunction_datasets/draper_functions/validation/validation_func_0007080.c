schedule_update_flush(struct interface *ifp, int urgent)
{
    unsigned msecs;
    msecs = update_jitter(ifp, urgent);
    if(ifp->update_flush_timeout.tv_sec != 0 &&
       timeval_minus_msec(&ifp->update_flush_timeout, &now) < msecs)
        return;
    set_timeout(&ifp->update_flush_timeout, msecs);
}
