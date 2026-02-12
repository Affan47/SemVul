builtin_delattr_impl(PyObject *module, PyObject *obj, PyObject *name)

{
    if (PyObject_SetAttr(obj, name, (PyObject *)NULL) != 0)
        return NULL;
    Py_RETURN_NONE;
}
