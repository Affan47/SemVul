static apr_status_t wsgi_python_parent_cleanup(void *data)
#endif
{
    if (wsgi_parent_pid == getpid()) {


        if (wsgi_python_initialized)
            wsgi_python_term();
    }

#if AP_SERVER_MAJORVERSION_NUMBER >= 2
    return APR_SUCCESS;
#endif
}
