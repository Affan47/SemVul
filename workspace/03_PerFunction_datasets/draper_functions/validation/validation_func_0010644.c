event_pool_new (int count)
{
        struct event_pool *event_pool = NULL;
        extern struct event_ops event_ops_poll;

#ifdef HAVE_SYS_EPOLL_H
        extern struct event_ops event_ops_epoll;

        event_pool = event_ops_epoll.new (count);

        if (event_pool) {
                event_pool->ops = &event_ops_epoll;
        } else {
                gf_log ("event", GF_LOG_WARNING,
                        "falling back to poll based event handling");
        }
#endif

        if (!event_pool) {
                event_pool = event_ops_poll.new (count);

                if (event_pool)
                        event_pool->ops = &event_ops_poll;
        }

        return event_pool;
}
