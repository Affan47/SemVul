type_abstractmethods(PyTypeObject *type, void *context)
{
    PyObject *mod = NULL;


    if (type != &PyType_Type)
        mod = _PyDict_GetItemId(type->tp_dict, &PyId___abstractmethods__);
    if (!mod) {
        PyObject *message = _PyUnicode_FromId(&PyId___abstractmethods__);
        if (message)
            PyErr_SetObject(PyExc_AttributeError, message);
        return NULL;
    }
    Py_XINCREF(mod);
    return mod;
}
