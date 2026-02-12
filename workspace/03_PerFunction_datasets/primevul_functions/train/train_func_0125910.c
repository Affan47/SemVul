builtin_id(PyModuleDef *self, PyObject *v)

{
    return PyLong_FromVoidPtr(v);
}
