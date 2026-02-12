builtin_oct(PyObject *module, PyObject *number)

{
    return PyNumber_ToBase(number, 8);
}
