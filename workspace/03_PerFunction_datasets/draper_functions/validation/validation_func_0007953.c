PyInstanceMethod_New(PyObject *func) {
    PyInstanceMethodObject *method;
    method = PyObject_GC_New(PyInstanceMethodObject,
                             &PyInstanceMethod_Type);
    if (method == NULL) return NULL;
    Py_INCREF(func);
    method->func = func;
    _PyObject_GC_TRACK(method);
    return (PyObject *)method;
}
