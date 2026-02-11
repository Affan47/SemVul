POINTER(PyObject *self, PyObject *cls)
{
    PyObject *result;
    PyTypeObject *typ;
    PyObject *key;
    char *buf;

    result = PyDict_GetItem(_ctypes_ptrtype_cache, cls);
    if (result) {
        Py_INCREF(result);
        return result;
    }
    if (PyUnicode_CheckExact(cls)) {
        char *name = _PyUnicode_AsString(cls);
        buf = alloca(strlen(name) + 3 + 1);
        sprintf(buf, "LP_%s", name);
        result = PyObject_CallFunction((PyObject *)Py_TYPE(&PyCPointer_Type),
                                       "s(O){}",
                                       buf,
                                       &PyCPointer_Type);
        if (result == NULL)
            return result;
        key = PyLong_FromVoidPtr(result);
    } else if (PyType_Check(cls)) {
        typ = (PyTypeObject *)cls;
        buf = alloca(strlen(typ->tp_name) + 3 + 1);
        sprintf(buf, "LP_%s", typ->tp_name);
        result = PyObject_CallFunction((PyObject *)Py_TYPE(&PyCPointer_Type),
                                       "s(O){sO}",
                                       buf,
                                       &PyCPointer_Type,
                                       "_type_", cls);
        if (result == NULL)
            return result;
        Py_INCREF(cls);
        key = cls;
    } else {
        PyErr_SetString(PyExc_TypeError, "must be a ctypes type");
        return NULL;
    }
    if (-1 == PyDict_SetItem(_ctypes_ptrtype_cache, key, result)) {
        Py_DECREF(result);
        Py_DECREF(key);
        return NULL;
    }
    Py_DECREF(key);
    return result;
}
