static bool mirror_drained_poll(BlockJob *job)
{
    MirrorBlockJob *s = container_of(job, MirrorBlockJob, common);


    if (!s->common.job.paused && !s->common.job.cancelled && !s->in_drain) {
        return true;
    }

    return !!s->in_flight;
}
