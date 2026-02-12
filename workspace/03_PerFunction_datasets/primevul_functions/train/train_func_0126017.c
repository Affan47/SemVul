builtin_bin(PyObject *module, PyObject *number)

{
    return PyNumber_ToBase(number, 2);
}
