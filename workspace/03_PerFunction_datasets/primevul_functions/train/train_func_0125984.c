builtin_divmod_impl(PyObject *module, PyObject *x, PyObject *y)

{
    return PyNumber_Divmod(x, y);
}
