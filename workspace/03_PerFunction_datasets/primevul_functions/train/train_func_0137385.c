static InterpreterObject *newInterpreterObject(const char *name)
{
    PyInterpreterState *interp = NULL;
    InterpreterObject *self = NULL;
    PyThreadState *tstate = NULL;
    PyThreadState *save_tstate = NULL;
    PyObject *module = NULL;
    PyObject *object = NULL;
    PyObject *item = NULL;


    self = PyObject_New(InterpreterObject, &Interpreter_Type);
    if (self == NULL)
        return NULL;


    if (!name) {
        interp = PyInterpreterState_Head();
        while (interp->next)
            interp = interp->next;

        name = "";
    }


    self->name = strdup(name);

    if (interp) {


        ap_log_error(APLOG_MARK, WSGI_LOG_INFO(0), wsgi_server,
                     "mod_wsgi (pid=%d): Attach interpreter '%s'.",
                     getpid(), name);

        self->interp = interp;
        self->owner = 0;
    }
    else {
        PyObject *module = NULL;


        save_tstate = PyThreadState_Swap(NULL);


        tstate = Py_NewInterpreter();

        if (!tstate) {
            PyErr_SetString(PyExc_RuntimeError, "Py_NewInterpreter() failed");

            Py_DECREF(self);

            return NULL;
        }

        Py_BEGIN_ALLOW_THREADS
        ap_log_error(APLOG_MARK, WSGI_LOG_INFO(0), wsgi_server,
                     "mod_wsgi (pid=%d): Create interpreter '%s'.",
                     getpid(), name);
        Py_END_ALLOW_THREADS

        self->interp = tstate->interp;
        self->owner = 1;


#if PY_MAJOR_VERSION > 3 || (PY_MAJOR_VERSION == 3 && PY_MINOR_VERSION >= 4)
        module = PyImport_ImportModule("threading");

        if (module) {
            PyObject *dict = NULL;
            PyObject *func = NULL;

            dict = PyModule_GetDict(module);
            func = PyDict_GetItemString(dict, "_shutdown");

            if (func) {
                PyObject *wrapper = NULL;

                wrapper = newShutdownInterpreterObject(func);
                PyDict_SetItemString(dict, "_shutdown", wrapper);
                Py_DECREF(wrapper);
            }
        }

        Py_XDECREF(module);
#endif
    }


    object = newLogObject(NULL, APLOG_ERR, "stderr");
    PySys_SetObject("stderr", object);
    Py_DECREF(object);

#ifndef WIN32
    if (wsgi_parent_pid != getpid()) {
#endif
        if (wsgi_server_config->restrict_stdout == 1) {
            object = (PyObject *)newRestrictedObject("sys.stdout");
            PySys_SetObject("stdout", object);
            Py_DECREF(object);
        }
        else {
            object = newLogObject(NULL, APLOG_ERR, "stdout");
            PySys_SetObject("stdout", object);
            Py_DECREF(object);
        }

        if (wsgi_server_config->restrict_stdin == 1) {
            object = (PyObject *)newRestrictedObject("sys.stdin");
            PySys_SetObject("stdin", object);
            Py_DECREF(object);
        }
#ifndef WIN32
    }
#endif


    object = PyList_New(0);
#if PY_MAJOR_VERSION >= 3
    item = PyUnicode_FromString("mod_wsgi");
#else
    item = PyString_FromString("mod_wsgi");
#endif
    PyList_Append(object, item);
    PySys_SetObject("argv", object);
    Py_DECREF(item);
    Py_DECREF(object);


    if (wsgi_server_config->restrict_signal != 0) {
        module = PyImport_ImportModule("signal");
        PyModule_AddObject(module, "signal", PyCFunction_New(
                           &wsgi_signal_method[0], NULL));
        Py_DECREF(module);
    }


    item = PyCodec_Encoder("ascii");
    Py_XDECREF(item);


#ifndef WIN32
    if (wsgi_daemon_pool) {
        module = PyImport_ImportModule("os");

        if (module) {
            PyObject *dict = NULL;
            PyObject *key = NULL;
            PyObject *value = NULL;

            dict = PyModule_GetDict(module);
            object = PyDict_GetItemString(dict, "environ");

            if (object) {
                struct passwd *pwent;

                pwent = getpwuid(geteuid());

                if (getenv("USER")) {
#if PY_MAJOR_VERSION >= 3
                    key = PyUnicode_FromString("USER");
                    value = PyUnicode_Decode(pwent->pw_name,
                                             strlen(pwent->pw_name),
                                             Py_FileSystemDefaultEncoding,
                                             "surrogateescape");
#else
                    key = PyString_FromString("USER");
                    value = PyString_FromString(pwent->pw_name);
#endif

                    PyObject_SetItem(object, key, value);

                    Py_DECREF(key);
                    Py_DECREF(value);
                }

                if (getenv("USERNAME")) {
#if PY_MAJOR_VERSION >= 3
                    key = PyUnicode_FromString("USERNAME");
                    value = PyUnicode_Decode(pwent->pw_name,
                                             strlen(pwent->pw_name),
                                             Py_FileSystemDefaultEncoding,
                                             "surrogateescape");
#else
                    key = PyString_FromString("USERNAME");
                    value = PyString_FromString(pwent->pw_name);
#endif

                    PyObject_SetItem(object, key, value);

                    Py_DECREF(key);
                    Py_DECREF(value);
                }

                if (getenv("LOGNAME")) {
#if PY_MAJOR_VERSION >= 3
                    key = PyUnicode_FromString("LOGNAME");
                    value = PyUnicode_Decode(pwent->pw_name,
                                             strlen(pwent->pw_name),
                                             Py_FileSystemDefaultEncoding,
                                             "surrogateescape");
#else
                    key = PyString_FromString("LOGNAME");
                    value = PyString_FromString(pwent->pw_name);
#endif

                    PyObject_SetItem(object, key, value);

                    Py_DECREF(key);
                    Py_DECREF(value);
                }
            }

            Py_DECREF(module);
        }
    }
#endif


#ifndef WIN32
    if (wsgi_daemon_pool) {
        module = PyImport_ImportModule("os");

        if (module) {
            PyObject *dict = NULL;
            PyObject *key = NULL;
            PyObject *value = NULL;

            dict = PyModule_GetDict(module);
            object = PyDict_GetItemString(dict, "environ");

            if (object) {
                struct passwd *pwent;

                pwent = getpwuid(geteuid());
#if PY_MAJOR_VERSION >= 3
                key = PyUnicode_FromString("HOME");
                value = PyUnicode_Decode(pwent->pw_dir, strlen(pwent->pw_dir),
                                         Py_FileSystemDefaultEncoding,
                                         "surrogateescape");
#else
                key = PyString_FromString("HOME");
                value = PyString_FromString(pwent->pw_dir);
#endif

                PyObject_SetItem(object, key, value);

                Py_DECREF(key);
                Py_DECREF(value);
            }

            Py_DECREF(module);
        }
    }
#endif


    if (!wsgi_daemon_pool)
        wsgi_python_eggs = wsgi_server_config->python_eggs;

    if (wsgi_python_eggs) {
        module = PyImport_ImportModule("os");

        if (module) {
            PyObject *dict = NULL;
            PyObject *key = NULL;
            PyObject *value = NULL;

            dict = PyModule_GetDict(module);
            object = PyDict_GetItemString(dict, "environ");

            if (object) {
#if PY_MAJOR_VERSION >= 3
                key = PyUnicode_FromString("PYTHON_EGG_CACHE");
                value = PyUnicode_Decode(wsgi_python_eggs,
                                         strlen(wsgi_python_eggs),
                                         Py_FileSystemDefaultEncoding,
                                         "surrogateescape");
#else
                key = PyString_FromString("PYTHON_EGG_CACHE");
                value = PyString_FromString(wsgi_python_eggs);
#endif

                PyObject_SetItem(object, key, value);

                Py_DECREF(key);
                Py_DECREF(value);
            }

            Py_DECREF(module);
        }
    }


    if (!wsgi_daemon_pool)
        wsgi_python_path = wsgi_server_config->python_path;

    if (wsgi_python_path) {
        PyObject *path = NULL;

        module = PyImport_ImportModule("site");
        path = PySys_GetObject("path");

        if (module && path) {
            PyObject *dict = NULL;

            PyObject *old = NULL;
            PyObject *new = NULL;
            PyObject *tmp = NULL;

            PyObject *item = NULL;

            int i = 0;

            old = PyList_New(0);
            new = PyList_New(0);
            tmp = PyList_New(0);

            for (i=0; i<PyList_Size(path); i++)
                PyList_Append(old, PyList_GetItem(path, i));

            dict = PyModule_GetDict(module);
            object = PyDict_GetItemString(dict, "addsitedir");

            if (object) {
                const char *start;
                const char *end;
                const char *value;

                PyObject *item;
                PyObject *args;

                PyObject *result = NULL;

                Py_INCREF(object);

                start = wsgi_python_path;
                end = strchr(start, DELIM);

                if (end) {
#if PY_MAJOR_VERSION >= 3
                    item = PyUnicode_Decode(start, end-start,
                                            Py_FileSystemDefaultEncoding,
                                            "surrogateescape");
#else
                    item = PyString_FromStringAndSize(start, end-start);
#endif
                    start = end+1;

                    value = PyString_AsString(item);

                    Py_BEGIN_ALLOW_THREADS
                    ap_log_error(APLOG_MARK, WSGI_LOG_INFO(0), wsgi_server,
                                 "mod_wsgi (pid=%d): Adding '%s' to "
                                 "path.", getpid(), value);
                    Py_END_ALLOW_THREADS

                    args = Py_BuildValue("(O)", item);
                    result = PyEval_CallObject(object, args);

                    if (!result) {
                        Py_BEGIN_ALLOW_THREADS
                        ap_log_error(APLOG_MARK, WSGI_LOG_ERR(0), wsgi_server,
                                     "mod_wsgi (pid=%d): Call to "
                                     "'site.addsitedir()' failed for '%s', "
                                     "stopping.", getpid(), value);
                        Py_END_ALLOW_THREADS
                    }

                    Py_XDECREF(result);
                    Py_DECREF(item);
                    Py_DECREF(args);

                    end = strchr(start, DELIM);

                    while (result && end) {
#if PY_MAJOR_VERSION >= 3
                        item = PyUnicode_Decode(start, end-start,
                                                Py_FileSystemDefaultEncoding,
                                                "surrogateescape");
#else
                        item = PyString_FromStringAndSize(start, end-start);
#endif
                        start = end+1;

                        value = PyString_AsString(item);

                        Py_BEGIN_ALLOW_THREADS
                        ap_log_error(APLOG_MARK, WSGI_LOG_INFO(0), wsgi_server,
                                     "mod_wsgi (pid=%d): Adding '%s' to "
                                     "path.", getpid(), value);
                        Py_END_ALLOW_THREADS

                        args = Py_BuildValue("(O)", item);
                        result = PyEval_CallObject(object, args);

                        if (!result) {
                            Py_BEGIN_ALLOW_THREADS
                            ap_log_error(APLOG_MARK, WSGI_LOG_ERR(0),
                                         wsgi_server, "mod_wsgi (pid=%d): "
                                         "Call to 'site.addsitedir()' failed "
                                         "for '%s', stopping.",
                                         getpid(), value);
                            Py_END_ALLOW_THREADS
                        }

                        Py_XDECREF(result);
                        Py_DECREF(item);
                        Py_DECREF(args);

                        end = strchr(start, DELIM);
                    }
                }

                Py_BEGIN_ALLOW_THREADS
                ap_log_error(APLOG_MARK, WSGI_LOG_INFO(0), wsgi_server,
                             "mod_wsgi (pid=%d): Adding '%s' to "
                             "path.", getpid(), start);
                Py_END_ALLOW_THREADS

                args = Py_BuildValue("(s)", start);
                result = PyEval_CallObject(object, args);

                if (!result) {
                    Py_BEGIN_ALLOW_THREADS
                    ap_log_error(APLOG_MARK, WSGI_LOG_ERR(0), wsgi_server,
                                 "mod_wsgi (pid=%d): Call to "
                                 "'site.addsitedir()' failed for '%s'.",
                                 getpid(), start);
                    Py_END_ALLOW_THREADS
                }

                Py_XDECREF(result);
                Py_DECREF(args);

                Py_DECREF(object);
            }
            else {
                Py_BEGIN_ALLOW_THREADS
                ap_log_error(APLOG_MARK, WSGI_LOG_ERR(0), wsgi_server,
                             "mod_wsgi (pid=%d): Unable to locate "
                             "'site.addsitedir()'.", getpid());
                Py_END_ALLOW_THREADS
            }

            for (i=0; i<PyList_Size(path); i++)
                PyList_Append(tmp, PyList_GetItem(path, i));

            for (i=0; i<PyList_Size(tmp); i++) {
                item = PyList_GetItem(tmp, i);
                if (!PySequence_Contains(old, item)) {
                    int index = PySequence_Index(path, item);
                    PyList_Append(new, item);
                    if (index != -1)
                        PySequence_DelItem(path, index);
                }
            }

            PyList_SetSlice(path, 0, 0, new);

            Py_DECREF(old);
            Py_DECREF(new);
            Py_DECREF(tmp);
        }
        else {
            if (!module) {
                Py_BEGIN_ALLOW_THREADS
                ap_log_error(APLOG_MARK, WSGI_LOG_ERR(0), wsgi_server,
                             "mod_wsgi (pid=%d): Unable to import 'site' "
                             "module.", getpid());
                Py_END_ALLOW_THREADS
            }

            if (!path) {
                Py_BEGIN_ALLOW_THREADS
                ap_log_error(APLOG_MARK, WSGI_LOG_ERR(0), wsgi_server,
                             "mod_wsgi (pid=%d): Lookup for 'sys.path' "
                             "failed.", getpid());
                Py_END_ALLOW_THREADS
            }
        }

        Py_XDECREF(module);
    }


    module = PyImport_ImportModule("mod_wsgi");

    if (!module) {
        PyObject *modules = NULL;

        modules = PyImport_GetModuleDict();
        module = PyDict_GetItemString(modules, "mod_wsgi");

        if (module) {
            PyErr_Print();

            PyDict_DelItemString(modules, "mod_wsgi");
        }

        PyErr_Clear();

        module = PyImport_AddModule("mod_wsgi");

        Py_INCREF(module);
    }
    else if (!*name) {
        Py_BEGIN_ALLOW_THREADS
        ap_log_error(APLOG_MARK, WSGI_LOG_INFO(0), wsgi_server,
                     "mod_wsgi (pid=%d): Imported 'mod_wsgi'.",
                     getpid());
        Py_END_ALLOW_THREADS
    }


    PyModule_AddObject(module, "version", Py_BuildValue("(ii)",
                       MOD_WSGI_MAJORVERSION_NUMBER,
                       MOD_WSGI_MINORVERSION_NUMBER));


#if PY_MAJOR_VERSION >= 3
    PyModule_AddObject(module, "process_group",
                       PyUnicode_DecodeLatin1(wsgi_daemon_group,
                       strlen(wsgi_daemon_group), NULL));
    PyModule_AddObject(module, "application_group",
                       PyUnicode_DecodeLatin1(name, strlen(name), NULL));
#else
    PyModule_AddObject(module, "process_group",
                       PyString_FromString(wsgi_daemon_group));
    PyModule_AddObject(module, "application_group",
                       PyString_FromString(name));
#endif

    Py_DECREF(module);


    module = NULL;

    if (!wsgi_daemon_pool) {
        module = PyImport_ImportModule("apache");

        if (!module) {
            PyObject *modules = NULL;

            modules = PyImport_GetModuleDict();
            module = PyDict_GetItemString(modules, "apache");

            if (module) {
                Py_BEGIN_ALLOW_THREADS
                ap_log_error(APLOG_MARK, WSGI_LOG_INFO(0), wsgi_server,
                             "mod_wsgi (pid=%d): Unable to import "
                             "'apache' extension module.", getpid());
                Py_END_ALLOW_THREADS

                PyErr_Print();

                PyDict_DelItemString(modules, "apache");

                module = NULL;
            }

            PyErr_Clear();
        }
        else {
            Py_BEGIN_ALLOW_THREADS
            ap_log_error(APLOG_MARK, WSGI_LOG_INFO(0), wsgi_server,
                         "mod_wsgi (pid=%d): Imported 'apache'.",
                         getpid());
            Py_END_ALLOW_THREADS
        }
    }

    if (!module) {
        module = PyImport_AddModule("apache");

        Py_INCREF(module);
    }


    PyModule_AddObject(module, "version", Py_BuildValue("(ii)",
                       AP_SERVER_MAJORVERSION_NUMBER,
                       AP_SERVER_MINORVERSION_NUMBER));

    Py_DECREF(module);


    if (self->owner) {
#if APR_HAS_THREADS
        int thread_id = 0;
        int *thread_handle = NULL;

        self->tstate_table = apr_hash_make(wsgi_server->process->pool);

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

        if (wsgi_server_config->verbose_debugging) {
            ap_log_error(APLOG_MARK, WSGI_LOG_DEBUG(0), wsgi_server,
                         "mod_wsgi (pid=%d): Bind thread state for "
                         "thread %d against interpreter '%s'.", getpid(),
                         thread_id, self->name);
        }

        apr_hash_set(self->tstate_table, thread_handle,
                     sizeof(*thread_handle), tstate);

        PyThreadState_Swap(save_tstate);
#else
        self->tstate = tstate;
        PyThreadState_Swap(save_tstate);
#endif
    }

    return self;
}
