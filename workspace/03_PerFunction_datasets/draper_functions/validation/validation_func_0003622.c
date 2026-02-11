log_slow_post_read_request(request_rec *r)
{
    log_slow_config *conf =
         ap_get_module_config(r->server->module_config, &log_slow_module);

    if (!conf || !conf->enabled ) {
        return DECLINED;
    }

    set_snapshot(&usage_start);
#ifdef LOGSLOW_DEBUG
    show_snapshot(r,&usage_start,"START");
#endif
    return OK;
}
