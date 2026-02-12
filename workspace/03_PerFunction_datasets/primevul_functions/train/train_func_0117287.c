static InterpreterObject *wsgi_acquire_interpreter(const char *name)
{
    PyThreadState *tstate = NULL;
    PyInterpreterState *interp = NULL;
    InterpreterObject *handle = NULL;

    PyGILState_STATE state;


#if APR_HAS_THREADS
    apr_thread_mutex_lock(wsgi_interp_lock);
#endif


    state = PyGILState_Ensure();


    handle = (InterpreterObject *)PyDict_GetItemString(wsgi_interpreters,
                                                       name);

    if (!handle) {
        handle = newInterpreterObject(name);

        if (!handle) {
            ap_log_error(APLOG_MARK, WSGI_LOG_CRIT(0), wsgi_server,
                         "mod_wsgi (pid=%d): Cannot create interpreter '%s'.",
                         getpid(), name);

            PyErr_Print();
            PyErr_Clear();

            PyGILState_Release(state);

#if APR_HAS_THREADS
            apr_thread_mutex_unlock(wsgi_interp_lock);
#endif
            return NULL;
        }

        PyDict_SetItemString(wsgi_interpreters, name, (PyObject *)handle);
    }
    else
        Py_INCREF(handle);

    interp = handle->interp;


    PyGILState_Release(state);

#if APR_HAS_THREADS
    apr_thread_mutex_unlock(wsgi_interp_lock);
#endif

    if (*name) {
#if APR_HAS_THREADS
        int thread_id = 0;
        int *thread_handle = NULL;

        apr_threadkey_private_get((void**)&thread_handle, wsgi_thread_key);

        if (!thread_handle) {
            thread_id = wsgi_thread_count++;
            thread_handle = (int*)apr_pmemdup(wsgi_server->process->pool,
                                              &thread_id, sizeof(thread_id));
            apr_threadkey_private_set(thread_handle, wsgi_thread_key);
        }
        else {
            thread_id = *thread_handle;
        }

        tstate = apr_hash_get(handle->tstate_table, &thread_id,
                              sizeof(thread_id));

        if (!tstate) {
            tstate = PyThreadState_New(interp);

            if (wsgi_server_config->verbose_debugging) {
                ap_log_error(APLOG_MARK, WSGI_LOG_DEBUG(0), wsgi_server,
                             "mod_wsgi (pid=%d): Create thread state for "
                             "thread %d against interpreter '%s'.", getpid(),
                             thread_id, handle->name);
            }

            apr_hash_set(handle->tstate_table, thread_handle,
                         sizeof(*thread_handle), tstate);
        }
#else
        tstate = handle->tstate;
#endif

        PyEval_AcquireThread(tstate);
    }
    else {
        PyGILState_Ensure();


        tstate = PyThreadState_Get();
        if (tstate && tstate->gilstate_counter == 1)
            tstate->gilstate_counter++;
    }

    return handle;
}
