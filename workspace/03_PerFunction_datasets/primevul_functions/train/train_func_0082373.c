static int Adapter_output(AdapterObject *self, const char *data, int length,
                          int exception_when_aborted)
{
    int i = 0;
    int n = 0;
    apr_status_t rv;
    request_rec *r;

#if defined(MOD_WSGI_WITH_DAEMONS)
    if (wsgi_inactivity_timeout) {
        apr_thread_mutex_lock(wsgi_shutdown_lock);
        wsgi_inactivity_shutdown_time = apr_time_now();
        wsgi_inactivity_shutdown_time += wsgi_inactivity_timeout;
        apr_thread_mutex_unlock(wsgi_shutdown_lock);
    }
#endif

    if (!self->status_line) {
        PyErr_SetString(PyExc_RuntimeError, "response has not been started");
        return 0;
    }

    r = self->r;


    if (self->headers) {


#if (AP_SERVER_MAJORVERSION_NUMBER == 1) || \
    (AP_SERVER_MAJORVERSION_NUMBER == 2 && \
     AP_SERVER_MINORVERSION_NUMBER < 2) || \
    (AP_SERVER_MAJORVERSION_NUMBER == 2 && \
     AP_SERVER_MINORVERSION_NUMBER == 2 && \
     AP_SERVER_PATCHLEVEL_NUMBER < 8)

        if (!self->input->init) {
            if (self->status >= 200 && self->status < 400) {
                PyObject *args = NULL;
                PyObject *result = NULL;
                args = Py_BuildValue("(i)", 0);
                result = Input_read(self->input, args);
                if (PyErr_Occurred())
                    PyErr_Clear();
                Py_DECREF(args);
                Py_XDECREF(result);
            }
        }

#endif


        r->status = self->status;
        r->status_line = self->status_line;

        for (i = 0; i < PyList_Size(self->headers); i++) {
            PyObject *tuple = NULL;

            PyObject *object1 = NULL;
            PyObject *object2 = NULL;

            char *name = NULL;
            char *value = NULL;

            tuple = PyList_GetItem(self->headers, i);

            if (!PyTuple_Check(tuple)) {
                PyErr_Format(PyExc_TypeError, "list of tuple values "
                             "expected, value of type %.200s found",
                             tuple->ob_type->tp_name);
                return 0;
            }

            if (PyTuple_Size(tuple) != 2) {
                PyErr_Format(PyExc_ValueError, "tuple of length 2 "
                             "expected, length is %d",
                             (int)PyTuple_Size(tuple));
                return 0;
            }

            object1 = PyTuple_GetItem(tuple, 0);
            object2 = PyTuple_GetItem(tuple, 1);

            if (PyString_Check(object1)) {
                name = PyString_AsString(object1);
            }
#if PY_MAJOR_VERSION >= 3
            else if (PyUnicode_Check(object1)) {
                PyObject *latin_object;
                latin_object = PyUnicode_AsLatin1String(object1);
                if (!latin_object) {
                    PyErr_Format(PyExc_TypeError, "header name "
                                 "contained non 'latin-1' characters ");
                    return 0;
                }

                name = apr_pstrdup(r->pool, PyString_AsString(latin_object));
                Py_DECREF(latin_object);
            }
#endif
            else {
                PyErr_Format(PyExc_TypeError, "expected byte string object "
                             "for header name, value of type %.200s "
                             "found", object1->ob_type->tp_name);
                return 0;
            }

            if (PyString_Check(object2)) {
                value = PyString_AsString(object2);
            }
#if PY_MAJOR_VERSION >= 3
            else if (PyUnicode_Check(object2)) {
                PyObject *latin_object;
                latin_object = PyUnicode_AsLatin1String(object2);
                if (!latin_object) {
                    PyErr_Format(PyExc_TypeError, "header value "
                                 "contained non 'latin-1' characters ");
                    return 0;
                }

                value = apr_pstrdup(r->pool, PyString_AsString(latin_object));
                Py_DECREF(latin_object);
            }
#endif
            else {
                PyErr_Format(PyExc_TypeError, "expected byte string object "
                             "for header value, value of type %.200s "
                             "found", object2->ob_type->tp_name);
                return 0;
            }

            if (strchr(name, '\n') != 0 || strchr(value, '\n') != 0) {
                PyErr_Format(PyExc_ValueError, "embedded newline in "
                             "response header with name '%s' and value '%s'",
                             name, value);
                return 0;
            }

            if (!strcasecmp(name, "Content-Type")) {
#if AP_SERVER_MAJORVERSION_NUMBER < 2
                r->content_type = apr_pstrdup(r->pool, value);
#else


                if (*self->config->process_group)
                    r->content_type = apr_pstrdup(r->pool, value);
                else
                    ap_set_content_type(r, value);
#endif
            }
            else if (!strcasecmp(name, "Content-Length")) {
                char *v = value;
                long l = 0;

                errno = 0;
                l = strtol(v, &v, 10);
                if (*v || errno == ERANGE || l < 0) {
                    PyErr_SetString(PyExc_ValueError,
                                    "invalid content length");
                    return 0;
                }

                ap_set_content_length(r, l);

                self->content_length_set = 1;
                self->content_length = l;
            }
            else if (!strcasecmp(name, "WWW-Authenticate")) {
                apr_table_add(r->err_headers_out, name, value);
            }
            else {
                apr_table_add(r->headers_out, name, value);
            }
        }


        Py_BEGIN_ALLOW_THREADS
        ap_send_http_header(r);
        Py_END_ALLOW_THREADS


        r->expecting_100 = 0;


        Py_DECREF(self->headers);
        self->headers = NULL;
    }


    if (length) {
        int output_length = length;

        if (self->content_length_set) {
            if (self->output_length < self->content_length) {
                if (self->output_length + length > self->content_length) {
                    length = self->content_length - self->output_length;
                }
            }
            else
                length = 0;
        }

        self->output_length += output_length;
    }


    if (length) {
#if defined(MOD_WSGI_WITH_BUCKETS)
        apr_bucket *b;


        if (r->connection->aborted) {
            if (!exception_when_aborted) {
                ap_log_rerror(APLOG_MARK, WSGI_LOG_DEBUG(0), self->r,
                              "mod_wsgi (pid=%d): Client closed connection.",
                              getpid());
            }
            else
                PyErr_SetString(PyExc_IOError, "client connection closed");

            return 0;
        }

        if (!self->bb) {
            self->bb = apr_brigade_create(r->pool,
                                          r->connection->bucket_alloc);
        }

        b = apr_bucket_transient_create(data, length,
                                        r->connection->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(self->bb, b);

        b = apr_bucket_flush_create(r->connection->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(self->bb, b);

        Py_BEGIN_ALLOW_THREADS
        rv = ap_pass_brigade(r->output_filters, self->bb);
        Py_END_ALLOW_THREADS

        if (rv != APR_SUCCESS) {
            PyErr_SetString(PyExc_IOError, "failed to write data");
            return 0;
        }

        Py_BEGIN_ALLOW_THREADS
        apr_brigade_cleanup(self->bb);
        Py_END_ALLOW_THREADS
#else


        Py_BEGIN_ALLOW_THREADS
        n = ap_rwrite(data, length, r);
        Py_END_ALLOW_THREADS

        if (n == -1) {
            PyErr_SetString(PyExc_IOError, "failed to write data");
            return 0;
        }

        Py_BEGIN_ALLOW_THREADS
        n = ap_rflush(r);
        Py_END_ALLOW_THREADS

        if (n == -1) {
            PyErr_SetString(PyExc_IOError, "failed to flush data");
            return 0;
        }
#endif
    }


    if (r->connection->aborted) {
        if (!exception_when_aborted) {
            ap_log_rerror(APLOG_MARK, WSGI_LOG_DEBUG(0), self->r,
                          "mod_wsgi (pid=%d): Client closed connection.",
                          getpid());
        }
        else
            PyErr_SetString(PyExc_IOError, "client connection closed");

        return 0;
    }

    return 1;
}
