iobase_close(PyObject *self, PyObject *args)
{
    PyObject *res;

    if (IS_CLOSED(self))
        Py_RETURN_NONE;

    res = PyObject_CallMethodObjArgs(self, _PyIO_str_flush, NULL);

    if (_PyObject_SetAttrId(self, &PyId___IOBase_closed, Py_True) < 0) {
        Py_XDECREF(res);
        return NULL;
    }

    if (res == NULL)
        return NULL;

    Py_DECREF(res);
    Py_RETURN_NONE;
}
