static void thread_pool_completion_bh(void *opaque) {
    ThreadPool *pool = opaque;
    ThreadPoolElement *elem, *next;
    aio_context_acquire(pool->ctx);
restart:
    QLIST_FOREACH_SAFE(elem, &pool->head, all, next) {
        if (elem->state != THREAD_DONE) {
            continue;
        }
        trace_thread_pool_complete(pool, elem, elem->common.opaque, elem->ret);
        QLIST_REMOVE(elem, all);
        if (elem->common.cb) {
            smp_rmb();
