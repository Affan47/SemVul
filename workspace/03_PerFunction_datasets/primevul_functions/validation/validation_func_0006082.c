multi_init(struct multi_context *m, struct context *t, bool tcp_mode, int thread_mode)
{
    int dev = DEV_TYPE_UNDEF;

    msg(D_MULTI_LOW, "MULTI: multi_init called, r=%d v=%d",
        t->options.real_hash_size,
        t->options.virtual_hash_size);


    dev = dev_type_enum(t->options.dev, t->options.dev_type);


    CLEAR(*m);

    m->thread_mode = thread_mode;


    m->hash = hash_init(t->options.real_hash_size,
                        get_random(),
                        mroute_addr_hash_function,
                        mroute_addr_compare_function);


    m->vhash = hash_init(t->options.virtual_hash_size,
                         get_random(),
                         mroute_addr_hash_function,
                         mroute_addr_compare_function);


    m->iter = hash_init(1,
                        get_random(),
                        mroute_addr_hash_function,
                        mroute_addr_compare_function);

#ifdef MANAGEMENT_DEF_AUTH
    m->cid_hash = hash_init(t->options.real_hash_size,
                            0,
                            cid_hash_function,
                            cid_compare_function);
#endif

#ifdef ENABLE_ASYNC_PUSH


    m->inotify_watchers = hash_init(t->options.real_hash_size,
                                    get_random(),
                                    int_hash_function,
                                    int_compare_function);
#endif


    m->schedule = schedule_init();


    m->new_connection_limiter = frequency_limit_init(t->options.cf_max,
                                                     t->options.cf_per);


    m->mbuf = mbuf_init(t->options.n_bcast_buf);


    m->status_file_version = t->options.status_file_version;


    if (t->options.ifconfig_pool_defined)
    {
        int pool_type = IFCONFIG_POOL_INDIV;

        if (dev == DEV_TYPE_TUN && t->options.topology == TOP_NET30)
        {
            pool_type = IFCONFIG_POOL_30NET;
        }

        m->ifconfig_pool = ifconfig_pool_init(pool_type,
                                              t->options.ifconfig_pool_start,
                                              t->options.ifconfig_pool_end,
                                              t->options.duplicate_cn,
                                              t->options.ifconfig_ipv6_pool_defined,
                                              t->options.ifconfig_ipv6_pool_base,
                                              t->options.ifconfig_ipv6_pool_netbits );


        if (t->c1.ifconfig_pool_persist)
        {
            ifconfig_pool_read(t->c1.ifconfig_pool_persist, m->ifconfig_pool);
        }
    }


    m->route_helper = mroute_helper_init(MULTI_CACHE_ROUTE_TTL);


    m->reaper = multi_reap_new(reap_buckets_per_pass(t->options.virtual_hash_size));


    CLEAR(m->local);
    ASSERT(t->c1.tuntap);
    mroute_extract_in_addr_t(&m->local, t->c1.tuntap->local);


    m->max_clients = t->options.max_clients;

    m->instances = calloc(m->max_clients, sizeof(struct multi_instance *));


    if (tcp_mode)
    {
        m->mtcp = multi_tcp_init(t->options.max_clients, &m->max_clients);
    }
    m->tcp_queue_limit = t->options.tcp_queue_limit;


    m->enable_c2c = t->options.enable_c2c;


    if (t->options.stale_routes_check_interval > 0)
    {
        msg(M_INFO, "Initializing stale route check timer to run every %i seconds and to removing routes with activity timeout older than %i seconds",
            t->options.stale_routes_check_interval, t->options.stale_routes_ageing_time);
        event_timeout_init(&m->stale_routes_check_et, t->options.stale_routes_check_interval, 0);
    }

    m->deferred_shutdown_signal.signal_received = 0;
}
