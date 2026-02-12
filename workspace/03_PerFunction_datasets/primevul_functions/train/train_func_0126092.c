builtin_hex(PyObject *module, PyObject *number)

{
    return PyNumber_ToBase(number, 16);
}
