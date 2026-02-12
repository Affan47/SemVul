static apr_status_t wsgi_python_child_cleanup(void *data)
{
    PyObject *interp = NULL;


#if APR_HAS_THREADS
    apr_thread_mutex_lock(wsgi_interp_lock);
#endif


    PyEval_AcquireThread(wsgi_main_tstate);


    interp = PyDict_GetItemString(wsgi_interpreters, "");
    Py_INCREF(interp);


    ap_log_error(APLOG_MARK, APLOG_INFO, 0, wsgi_server,
                 "mod_wsgi (pid=%d): Destroying interpreters.", getpid());

    PyDict_Clear(wsgi_interpreters);

#if APR_HAS_THREADS
    apr_thread_mutex_unlock(wsgi_interp_lock);
#endif


    Py_DECREF(interp);


    PyEval_ReleaseThread(wsgi_main_tstate);


    if (wsgi_python_initialized)
        wsgi_python_term();

    return APR_SUCCESS;
}
