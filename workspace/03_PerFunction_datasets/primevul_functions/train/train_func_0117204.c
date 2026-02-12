static int wsgi_hook_handler(request_rec *r)
{
    int status;
    apr_off_t limit = 0;

    WSGIRequestConfig *config = NULL;

    const char *value = NULL;


    if (!r->handler)
        return DECLINED;


    config = wsgi_create_req_config(r->pool, r);

    ap_set_module_config(r->request_config, &wsgi_module, config);


    if (!strcmp(r->handler, "wsgi-script") ||
        !strcmp(r->handler, "application/x-httpd-wsgi")) {


        if (!(ap_allow_options(r) & OPT_EXECCGI) &&
            !wsgi_is_script_aliased(r)) {
            wsgi_log_script_error(r, "Options ExecCGI is off in this "
                                  "directory", r->filename);
            return HTTP_FORBIDDEN;
        }


#if AP_SERVER_MAJORVERSION_NUMBER < 2
        if (r->finfo.st_mode == 0) {
            wsgi_log_script_error(r, "Target WSGI script not found or unable "
                                  "to stat", r->filename);
            return HTTP_NOT_FOUND;
        }
#else
        if (r->finfo.filetype == 0) {
            wsgi_log_script_error(r, "Target WSGI script not found or unable "
                                  "to stat", r->filename);
            return HTTP_NOT_FOUND;
        }
#endif

#if AP_SERVER_MAJORVERSION_NUMBER < 2
        if (S_ISDIR(r->finfo.st_mode)) {
            wsgi_log_script_error(r, "Attempt to invoke directory as WSGI "
                                  "application", r->filename);
            return HTTP_FORBIDDEN;
        }
#else
        if (r->finfo.filetype == APR_DIR) {
            wsgi_log_script_error(r, "Attempt to invoke directory as WSGI "
                                  "application", r->filename);
            return HTTP_FORBIDDEN;
        }
#endif

        if (wsgi_is_script_aliased(r)) {


            if (value = apr_table_get(r->notes, "mod_wsgi.process_group"))
                config->process_group = wsgi_process_group(r, value);
            if (value = apr_table_get(r->notes, "mod_wsgi.application_group"))
                config->application_group = wsgi_application_group(r, value);
            if (value = apr_table_get(r->notes, "mod_wsgi.callable_object"))
                config->callable_object = value;

            if (value = apr_table_get(r->notes,
                                      "mod_wsgi.pass_authorization")) {
                if (!strcmp(value, "1"))
                    config->pass_authorization = 1;
                else
                    config->pass_authorization = 0;
            }
        }
    }
#if AP_SERVER_MAJORVERSION_NUMBER >= 2
    else if (config->handler_scripts) {
        WSGIScriptFile *entry;

        entry = (WSGIScriptFile *)apr_hash_get(config->handler_scripts,
                                               r->handler,
                                               APR_HASH_KEY_STRING);

        if (entry) {
            config->handler_script = entry->handler_script;
            config->callable_object = "handle_request";

            if (value = entry->process_group)
                config->process_group = wsgi_process_group(r, value);
            if (value = entry->application_group)
                config->application_group = wsgi_application_group(r, value);

            if (value = entry->pass_authorization) {
                if (!strcmp(value, "1"))
                    config->pass_authorization = 1;
                else
                    config->pass_authorization = 0;
            }
        }
        else
            return DECLINED;
    }
#endif
    else
        return DECLINED;


#if AP_MODULE_MAGIC_AT_LEAST(20011212,0)
    if ((r->used_path_info == AP_REQ_REJECT_PATH_INFO) &&
        r->path_info && *r->path_info) {
        wsgi_log_script_error(r, "AcceptPathInfo off disallows user's path",
                              r->filename);
        return HTTP_NOT_FOUND;
    }
#endif


    if (config->chunked_request)
        status = ap_setup_client_block(r, REQUEST_CHUNKED_DECHUNK);
    else
        status = ap_setup_client_block(r, REQUEST_CHUNKED_ERROR);

    if (status != OK)
        return status;


    limit = ap_get_limit_req_body(r);

    if (limit && limit < r->remaining) {
        ap_discard_request_body(r);
        return OK;
    }


    wsgi_build_environment(r);


    if (config->dispatch_script) {
        status = wsgi_execute_dispatch(r);

        if (status != OK)
            return status;
    }


#if defined(MOD_WSGI_WITH_DAEMONS)
    status = wsgi_execute_remote(r);

    if (status != DECLINED)
        return status;
#endif

#if defined(MOD_WSGI_DISABLE_EMBEDDED)
    wsgi_log_script_error(r, "Embedded mode of mod_wsgi disabled at compile "
                          "time", r->filename);
    return HTTP_INTERNAL_SERVER_ERROR;
#endif

    if (wsgi_server_config->restrict_embedded == 1) {
        wsgi_log_script_error(r, "Embedded mode of mod_wsgi disabled by "
                              "runtime configuration", r->filename);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    return wsgi_execute_script(r);
}
