multi_process_per_second_timers_dowork(struct multi_context *m)
{

    multi_reap_process(m);


    if (m->top.c1.status_output)
    {
        if (status_trigger(m->top.c1.status_output))
        {
            multi_print_status(m, m->top.c1.status_output, m->status_file_version);
        }
    }


    multi_ifconfig_pool_persist(m, false);

#ifdef ENABLE_DEBUG
    gremlin_flood_clients(m);
#endif


    if (m->top.options.stale_routes_check_interval && stale_route_check_trigger(m))
    {
        check_stale_routes(m);
    }
}
