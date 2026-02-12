static void wsgi_manage_process(int reason, void *data, apr_wait_t status)
{
    WSGIDaemonProcess *daemon = data;

    switch (reason) {


        case APR_OC_REASON_DEATH: {
            int mpm_state;
            int stopping;


            apr_proc_other_child_unregister(daemon);


            stopping = 1;

            if (ap_mpm_query(AP_MPMQ_MPM_STATE, &mpm_state) == APR_SUCCESS
                && mpm_state != AP_MPMQ_STOPPING) {
                stopping = 0;
            }

            if (!stopping) {
                ap_log_error(APLOG_MARK, WSGI_LOG_INFO(0),
                             wsgi_server, "mod_wsgi (pid=%d): "
                             "Process '%s' has died, restarting.",
                             daemon->process.pid, daemon->group->name);

                wsgi_start_process(wsgi_parent_pool, daemon);
            }

            break;
        }


        case APR_OC_REASON_RESTART: {


            apr_proc_other_child_unregister(daemon);

            break;
        }


        case APR_OC_REASON_LOST: {


            apr_proc_other_child_unregister(daemon);


            ap_log_error(APLOG_MARK, WSGI_LOG_INFO(0),
                         wsgi_server, "mod_wsgi (pid=%d): "
                         "Process '%s' has died, restarting.",
                         daemon->process.pid, daemon->group->name);

            wsgi_start_process(wsgi_parent_pool, daemon);

            break;
        }


        case APR_OC_REASON_UNREGISTER: {


            break;
        }
    }
}
