static int Adapter_process_file_wrapper(AdapterObject *self)
{
    int done = 0;

#ifndef WIN32
    PyObject *filelike = NULL;
    PyObject *method = NULL;
    PyObject *object = NULL;

    apr_status_t rv = 0;

    apr_os_file_t fd = -1;
    apr_file_t *tmpfile = NULL;
    apr_finfo_t finfo;

    apr_off_t fd_offset = 0;
    apr_off_t fo_offset = 0;

    apr_off_t length = 0;


    if (!PyObject_IsInstance(self->sequence, (PyObject *)&Stream_Type))
        return 0;


    if (self->output_length != 0)
        return 0;


    filelike = PyObject_GetAttrString((PyObject *)self->sequence, "filelike");

    if (!filelike) {
        PyErr_SetString(PyExc_KeyError,
                        "file wrapper no filelike attribute");
        return 0;
    }

    fd = PyObject_AsFileDescriptor(filelike);
    if (fd == -1) {
        PyErr_Clear();
        Py_DECREF(filelike);
        return 0;
    }

    Py_DECREF(filelike);


    if (self->config->enable_sendfile)
        apr_os_file_put(&tmpfile, &fd, APR_SENDFILE_ENABLED, self->r->pool);
    else
        apr_os_file_put(&tmpfile, &fd, 0, self->r->pool);

    rv = apr_file_info_get(&finfo, APR_FINFO_SIZE|APR_FINFO_TYPE, tmpfile);
    if (rv != APR_SUCCESS || finfo.filetype != APR_REG)
        return 0;


    rv = apr_file_seek(tmpfile, APR_CUR, &fd_offset);
    if (rv != APR_SUCCESS)
        return 0;

    method = PyObject_GetAttrString(filelike, "tell");
    if (!method)
        return 0;

    object = PyEval_CallObject(method, NULL);
    Py_DECREF(method);

    if (!object) {
        PyErr_Clear();
        return 0;
    }

    if (PyLong_Check(object)) {
#if defined(HAVE_LONG_LONG)
        fo_offset = PyLong_AsLongLong(object);
#else
        fo_offset = PyLong_AsLong(object);
#endif
    }
#if PY_MAJOR_VERSION < 3
    else if (PyInt_Check(object)) {
        fo_offset = PyInt_AsLong(object);
    }
#endif
    else {
        Py_DECREF(object);
        return 0;
    }

    if (PyErr_Occurred()){
        Py_DECREF(object);
        PyErr_Clear();
        return 0;
    }

    Py_DECREF(object);


    if (!Adapter_output(self, "", 0, NULL, 0))
        return 1;


    if (!self->content_length_set) {
        length = finfo.size - fo_offset;
        self->output_length += length;

        ap_set_content_length(self->r, length);

        self->content_length_set = 1;
        self->content_length = length;

        if (Adapter_output_file(self, tmpfile, fo_offset, length))
            self->result = OK;

        done = 1;
    }
    else {
        length = finfo.size - fo_offset;
        self->output_length += length;


        length = self->content_length;

        if (Adapter_output_file(self, tmpfile, fo_offset, length))
            self->result = OK;

        done = 1;
    }


    apr_file_seek(tmpfile, APR_SET, &fd_offset);

#endif

    return done;
}
