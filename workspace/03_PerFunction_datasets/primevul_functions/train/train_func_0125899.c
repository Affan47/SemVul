builtin_issubclass_impl(PyObject *module, PyObject *cls,
                        PyObject *class_or_tuple)

{
    int retval;

    retval = PyObject_IsSubclass(cls, class_or_tuple);
    if (retval < 0)
        return NULL;
    return PyBool_FromLong(retval);
}
