builtin_hasattr_impl(PyObject *module, PyObject *obj, PyObject *name)

{
    PyObject *v;

    if (!PyUnicode_Check(name)) {
        PyErr_SetString(PyExc_TypeError,
                        "hasattr(): attribute name must be string");
        return NULL;
    }
    if (_PyObject_LookupAttr(obj, name, &v) < 0) {
        return NULL;
    }
    if (v == NULL) {
        Py_RETURN_FALSE;
    }
    Py_DECREF(v);
    Py_RETURN_TRUE;
}
