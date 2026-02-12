builtin_callable(PyObject *module, PyObject *obj)

{
    return PyBool_FromLong((long)PyCallable_Check(obj));
}
