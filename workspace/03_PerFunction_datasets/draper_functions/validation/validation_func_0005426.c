bd_refcnt_inc(const void *obj)
{
    if (!obj) {
        return;
    }

    BD_REFCNT *ref = &(((BD_REFCNT *)(intptr_t)obj)[-1]);

    if (!ref->counted) {
        bd_mutex_init(&ref->mutex);
        ref->counted = 1;
        ref->count = 2;
        return;
    }

    bd_mutex_lock(&ref->mutex);
    ++ref->count;
    bd_mutex_unlock(&ref->mutex);
}
