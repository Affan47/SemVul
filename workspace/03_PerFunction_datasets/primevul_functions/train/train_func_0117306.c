static apr_status_t wsgi_python_term()
{
    PyInterpreterState *interp = NULL;
    PyThreadState *tstate = NULL;

    PyObject *module = NULL;

    ap_log_error(APLOG_MARK, WSGI_LOG_INFO(0), wsgi_server,
                 "mod_wsgi (pid=%d): Terminating Python.", getpid());


    PyEval_AcquireThread(wsgi_main_tstate);


    module = PyImport_ImportModule("atexit");
    Py_XDECREF(module);


    if (!PyImport_AddModule("dummy_threading"))
        PyErr_Clear();

    Py_Finalize();

    wsgi_python_initialized = 0;

    ap_log_error(APLOG_MARK, WSGI_LOG_INFO(0), wsgi_server,
                 "mod_wsgi (pid=%d): Python has shutdown.", getpid());

    return APR_SUCCESS;
}
