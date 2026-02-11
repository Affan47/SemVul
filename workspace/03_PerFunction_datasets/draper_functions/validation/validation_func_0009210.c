element_iter(ElementObject* self, PyObject* args)
{
    PyObject* result;

    PyObject* tag = Py_None;
    if (!PyArg_ParseTuple(args, "|O:iter", &tag))
        return NULL;

    if (!elementtree_iter_obj) {
        PyErr_SetString(
            PyExc_RuntimeError,
            "iter helper not found"
            );
        return NULL;
    }

    args = PyTuple_New(2);
    if (!args)
        return NULL;

    Py_INCREF(self); PyTuple_SET_ITEM(args, 0, (PyObject*) self);
    Py_INCREF(tag);  PyTuple_SET_ITEM(args, 1, (PyObject*) tag);

    result = PyObject_CallObject(elementtree_iter_obj, args);

    Py_DECREF(args);

    return result;
}
