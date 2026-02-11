GC_set_oom_fn(GC_oom_func fn)
{
    GC_ASSERT(fn != 0);
    LOCK();
    GC_oom_fn = fn;
    UNLOCK();
}
