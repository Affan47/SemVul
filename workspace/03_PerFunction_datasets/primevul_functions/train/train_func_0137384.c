static void wsgi_python_child_init(apr_pool_t *p)
{
    PyGILState_STATE state;
    PyInterpreterState *interp = NULL;
    PyObject *object = NULL;

    int thread_id = 0;
    int *thread_handle = NULL;


    state = PyGILState_Ensure();


    if (wsgi_python_initialized && !wsgi_python_after_fork)
        PyOS_AfterFork();


    PyType_Ready(&Log_Type);
    PyType_Ready(&Stream_Type);
    PyType_Ready(&Input_Type);
    PyType_Ready(&Adapter_Type);
    PyType_Ready(&Restricted_Type);
    PyType_Ready(&Interpreter_Type);
    PyType_Ready(&ShutdownInterpreter_Type);
    PyType_Ready(&Dispatch_Type);

#if defined(MOD_WSGI_WITH_AAA_HANDLERS)
    PyType_Ready(&Auth_Type);
#endif


    wsgi_interpreters = PyDict_New();

#if APR_HAS_THREADS
    apr_thread_mutex_create(&wsgi_interp_lock, APR_THREAD_MUTEX_UNNESTED, p);
    apr_thread_mutex_create(&wsgi_module_lock, APR_THREAD_MUTEX_UNNESTED, p);
#endif


#if APR_HAS_THREADS
    apr_threadkey_private_create(&wsgi_thread_key, NULL, p);

    thread_id = wsgi_thread_count++;
    thread_handle = (int*)apr_pmemdup(wsgi_server->process->pool,
                                      &thread_id, sizeof(thread_id));
    apr_threadkey_private_set(thread_handle, wsgi_thread_key);
#endif


    object = (PyObject *)newInterpreterObject(NULL);
    PyDict_SetItemString(wsgi_interpreters, "", object);
    Py_DECREF(object);


    PyGILState_Release(state);


#if AP_SERVER_MAJORVERSION_NUMBER < 2
    ap_register_cleanup(p, NULL, wsgi_python_child_cleanup,
                        ap_null_cleanup);
#else
    apr_pool_cleanup_register(p, NULL, wsgi_python_child_cleanup,
                              apr_pool_cleanup_null);
#endif


    if (wsgi_import_list) {
        apr_array_header_t *scripts = NULL;

        WSGIScriptFile *entries;
        WSGIScriptFile *entry;

        int i;

        scripts = wsgi_import_list;
        entries = (WSGIScriptFile *)scripts->elts;

        for (i = 0; i < scripts->nelts; ++i) {
            int l = 0;

            entry = &entries[i];

            if (!strcmp(wsgi_daemon_group, entry->process_group)) {
                InterpreterObject *interp = NULL;
                PyObject *modules = NULL;
                PyObject *module = NULL;
                char *name = NULL;
                int exists = 0;

                interp = wsgi_acquire_interpreter(entry->application_group);

                if (!interp) {
                    ap_log_error(APLOG_MARK, WSGI_LOG_CRIT(0), wsgi_server,
                                  "mod_wsgi (pid=%d): Cannot acquire "
                                  "interpreter '%s'.", getpid(),
                                  entry->application_group);
                }


                name = wsgi_module_name(p, entry->handler_script);


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


                if (module && wsgi_server_config->script_reloading) {
                    if (wsgi_reload_required(p, NULL, entry->handler_script,
                                             module, NULL)) {


                        Py_DECREF(module);
                        module = NULL;

                        PyDict_DelItemString(modules, name);
                    }
                }

                if (!module) {
                    module = wsgi_load_source(p, NULL, name, exists,
                                              entry->handler_script,
                                              entry->process_group,
                                              entry->application_group);

                    if (PyErr_Occurred())
                        PyErr_Clear();
                }


#if APR_HAS_THREADS
                apr_thread_mutex_unlock(wsgi_module_lock);
#endif


                Py_XDECREF(module);

                wsgi_release_interpreter(interp);
            }
        }
    }
}
