builtin_locals_impl(PyObject *module)

{
    PyObject *d;

    d = PyEval_GetLocals();
    Py_XINCREF(d);
    return d;
}
