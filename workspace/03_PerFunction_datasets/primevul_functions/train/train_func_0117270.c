static int wsgi_execute_script(request_rec *r)
{
    WSGIRequestConfig *config = NULL;

    InterpreterObject *interp = NULL;
    PyObject *modules = NULL;
    PyObject *module = NULL;
    const char *script = NULL;
    const char *name = NULL;
    int exists = 0;

    int status;


    config = (WSGIRequestConfig *)ap_get_module_config(r->request_config,
                                                       &wsgi_module);


    interp = wsgi_acquire_interpreter(config->application_group);

    if (!interp) {
        ap_log_rerror(APLOG_MARK, WSGI_LOG_CRIT(0), r,
                      "mod_wsgi (pid=%d): Cannot acquire interpreter '%s'.",
                      getpid(), config->application_group);

        return HTTP_INTERNAL_SERVER_ERROR;
    }


    if (config->handler_script && *config->handler_script)
        script = config->handler_script;
    else
        script = r->filename;

    name = wsgi_module_name(r->pool, script);


#if APR_HAS_THREADS
    Py_BEGIN_ALLOW_THREADS
    apr_thread_mutex_lock(wsgi_module_lock);
    Py_END_ALLOW_THREADS
#endif

    modules = PyImport_GetModuleDict();
    module = PyDict_GetItemString(modules, name);

    Py_XINCREF(module);

    if (module)
        exists = 1;


    if (module && config->script_reloading) {
        if (wsgi_reload_required(r->pool, r, script, module, r->filename)) {


            Py_DECREF(module);
            module = NULL;

#if defined(MOD_WSGI_WITH_DAEMONS)
            if (*config->process_group) {


                Py_BEGIN_ALLOW_THREADS
                ap_log_rerror(APLOG_MARK, WSGI_LOG_INFO(0), r,
                             "mod_wsgi (pid=%d): Force restart of "
                             "process '%s'.", getpid(),
                             config->process_group);
                Py_END_ALLOW_THREADS

#if APR_HAS_THREADS
                apr_thread_mutex_unlock(wsgi_module_lock);
#endif

                wsgi_release_interpreter(interp);

                r->status = HTTP_INTERNAL_SERVER_ERROR;
                r->status_line = "200 Rejected";

                wsgi_daemon_shutdown++;
                kill(getpid(), SIGINT);

                return OK;
            }
            else {


                PyDict_DelItemString(modules, name);
            }
#else


            PyDict_DelItemString(modules, name);
#endif
        }
    }


#if defined(MOD_WSGI_WITH_DAEMONS)
    if (*config->process_group) {
        ap_filter_t *filters;
        apr_bucket_brigade *bb;
        apr_bucket *b;

        const char *data = "Status: 200 Continue\r\n\r\n";
        int length = strlen(data);

        filters = r->output_filters;
        while (filters && filters->frec->ftype != AP_FTYPE_NETWORK) {
            filters = filters->next;
        }

        bb = apr_brigade_create(r->pool, r->connection->bucket_alloc);

        b = apr_bucket_transient_create(data, length,
                                        r->connection->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, b);

        b = apr_bucket_flush_create(r->connection->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, b);


        ap_pass_brigade(filters, bb);
    }
#endif


    if (!module) {
        module = wsgi_load_source(r->pool, r, name, exists, script,
                                  config->process_group,
                                  config->application_group);
    }


#if APR_HAS_THREADS
    apr_thread_mutex_unlock(wsgi_module_lock);
#endif


    status = HTTP_INTERNAL_SERVER_ERROR;


    if (module) {
        PyObject *module_dict = NULL;
        PyObject *object = NULL;

        module_dict = PyModule_GetDict(module);
        object = PyDict_GetItemString(module_dict, config->callable_object);

        if (object) {
            AdapterObject *adapter = NULL;
            adapter = newAdapterObject(r);

            if (adapter) {
                PyObject *method = NULL;
                PyObject *args = NULL;

                Py_INCREF(object);
                status = Adapter_run(adapter, object);
                Py_DECREF(object);


                adapter->r = NULL;
                adapter->input->r = NULL;


                method = PyObject_GetAttrString(adapter->log, "close");

                if (!method) {
                    PyErr_Format(PyExc_AttributeError,
                                 "'%s' object has no attribute 'close'",
                                 adapter->log->ob_type->tp_name);
                }
                else {
                    args = PyTuple_New(0);
                    object = PyEval_CallObject(method, args);
                    Py_DECREF(args);
                }

                Py_XDECREF(object);
                Py_XDECREF(method);

#if defined(MOD_WSGI_WITH_BUCKETS)
                adapter->bb = NULL;
#endif
            }

            Py_XDECREF((PyObject *)adapter);
        }
        else {
            Py_BEGIN_ALLOW_THREADS
            ap_log_rerror(APLOG_MARK, WSGI_LOG_ERR(0), r,
                          "mod_wsgi (pid=%d): Target WSGI script '%s' does "
                          "not contain WSGI application '%s'.",
                          getpid(), script, config->callable_object);
            Py_END_ALLOW_THREADS

            status = HTTP_NOT_FOUND;
        }
    }


    if (PyErr_Occurred())
        wsgi_log_python_error(r, NULL, r->filename);


    Py_XDECREF(module);

    wsgi_release_interpreter(interp);

    return status;
}
