textiowrapper_repr(textio *self)
{
    PyObject *nameobj, *modeobj, *res, *s;

    CHECK_INITIALIZED(self);

    res = PyUnicode_FromString("<_io.TextIOWrapper");
    if (res == NULL)
        return NULL;
    nameobj = _PyObject_GetAttrId((PyObject *) self, &PyId_name);
    if (nameobj == NULL) {
        if (PyErr_ExceptionMatches(PyExc_AttributeError))
            PyErr_Clear();
        else
            goto error;
    }
    else {
        s = PyUnicode_FromFormat(" name=%R", nameobj);
        Py_DECREF(nameobj);
        if (s == NULL)
            goto error;
        PyUnicode_AppendAndDel(&res, s);
        if (res == NULL)
            return NULL;
    }
    modeobj = _PyObject_GetAttrId((PyObject *) self, &PyId_mode);
    if (modeobj == NULL) {
        if (PyErr_ExceptionMatches(PyExc_AttributeError))
            PyErr_Clear();
        else
            goto error;
    }
    else {
        s = PyUnicode_FromFormat(" mode=%R", modeobj);
        Py_DECREF(modeobj);
        if (s == NULL)
            goto error;
        PyUnicode_AppendAndDel(&res, s);
        if (res == NULL)
            return NULL;
    }
    s = PyUnicode_FromFormat("%U encoding=%R>",
                             res, self->encoding);
    Py_DECREF(res);
    return s;
error:
    Py_XDECREF(res);
    return NULL;
}
