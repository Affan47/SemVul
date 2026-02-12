builtin_isinstance_impl(PyObject *module, PyObject *obj,
                        PyObject *class_or_tuple)

{
    int retval;

    retval = PyObject_IsInstance(obj, class_or_tuple);
    if (retval < 0)
        return NULL;
    return PyBool_FromLong(retval);
}
