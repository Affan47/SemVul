builtin_setattr_impl(PyObject *module, PyObject *obj, PyObject *name,
                     PyObject *value)

{
    if (PyObject_SetAttr(obj, name, value) != 0)
        return NULL;
    Py_RETURN_NONE;
}
