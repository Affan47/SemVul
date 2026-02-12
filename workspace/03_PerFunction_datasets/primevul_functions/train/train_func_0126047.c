builtin_pow_impl(PyObject *module, PyObject *x, PyObject *y, PyObject *z)

{
    return PyNumber_Power(x, y, z);
}
