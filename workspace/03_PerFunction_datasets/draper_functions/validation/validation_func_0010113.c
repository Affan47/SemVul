long_long(PyObject *v)
{
    if (PyLong_CheckExact(v))
        Py_INCREF(v);
    else
        v = _PyLong_Copy((PyLongObject *)v);
    return v;
}
