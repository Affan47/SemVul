static void wsgi_python_init(apr_pool_t *p)
{
    const char *python_home = 0;

#if defined(DARWIN) && (AP_SERVER_MAJORVERSION_NUMBER < 2)
    static int initialized = 0;
#else
    static int initialized = 1;
#endif


    if (!Py_IsInitialized() || !initialized) {


#if PY_MAJOR_VERSION == 2 && PY_MINOR_VERSION >= 6
        if (wsgi_server_config->py3k_warning_flag == 1)
            Py_Py3kWarningFlag++;
#endif


#if PY_MAJOR_VERSION == 2 && PY_MINOR_VERSION >= 6
        if (wsgi_server_config->dont_write_bytecode == 1)
            Py_DontWriteBytecodeFlag++;
#endif


        if (wsgi_server_config->python_optimize > 0)
            Py_OptimizeFlag = wsgi_server_config->python_optimize;
        else
            Py_OptimizeFlag = 0;


        if (wsgi_server_config->python_warnings) {
            apr_array_header_t *options = NULL;
            char **entries;

            int i;

            options = wsgi_server_config->python_warnings;
            entries = (char **)options->elts;

            for (i = 0; i < options->nelts; ++i) {
#if PY_MAJOR_VERSION >= 3
                wchar_t *s = NULL;
                int len = strlen(entries[i])+1;

                s = (wchar_t *)apr_palloc(p, len*sizeof(wchar_t));

#if defined(WIN32) && defined(APR_HAS_UNICODE_FS)
                wsgi_utf8_to_unicode_path(s, len, entries[i]);
#else
                mbstowcs(s, entries[i], len);
#endif
                PySys_AddWarnOption(s);
#else
                PySys_AddWarnOption(entries[i]);
#endif
            }
        }


        python_home = wsgi_server_config->python_home;

#if defined(MOD_WSGI_WITH_DAEMONS)
        if (wsgi_daemon_process && wsgi_daemon_process->group->python_home)
            python_home = wsgi_daemon_process->group->python_home;
#endif

#if PY_MAJOR_VERSION >= 3
        if (python_home) {
            wchar_t *s = NULL;
            int len = strlen(python_home)+1;

            ap_log_error(APLOG_MARK, WSGI_LOG_INFO(0), wsgi_server,
                         "mod_wsgi (pid=%d): Python home %s.", getpid(),
                         python_home);

            s = (wchar_t *)apr_palloc(p, len*sizeof(wchar_t));

#if defined(WIN32) && defined(APR_HAS_UNICODE_FS)
            wsgi_utf8_to_unicode_path(s, len, python_home);
#else
            mbstowcs(s, python_home, len);
#endif
            Py_SetPythonHome(s);
        }
#else
        if (python_home) {
            ap_log_error(APLOG_MARK, WSGI_LOG_INFO(0), wsgi_server,
                         "mod_wsgi (pid=%d): Python home %s.", getpid(),
                         python_home);

            Py_SetPythonHome((char *)python_home);
        }
#endif


#if defined(WIN32) && PY_MAJOR_VERSION == 3 && PY_MINOR_VERSION < 3
        _wputenv(L"PYTHONIOENCODING=cp1252:backslashreplace");
#endif


        ap_log_error(APLOG_MARK, WSGI_LOG_INFO(0), wsgi_server,
                     "mod_wsgi (pid=%d): Initializing Python.", getpid());

        initialized = 1;

        Py_Initialize();


        PyEval_InitThreads();


        wsgi_main_tstate = PyThreadState_Get();
        PyEval_ReleaseThread(wsgi_main_tstate);

        wsgi_python_initialized = 1;


#if AP_SERVER_MAJORVERSION_NUMBER < 2
        ap_register_cleanup(p, NULL, wsgi_python_parent_cleanup,
                            ap_null_cleanup);
#else
        apr_pool_cleanup_register(p, NULL, wsgi_python_parent_cleanup,
                                  apr_pool_cleanup_null);
#endif
    }
}
