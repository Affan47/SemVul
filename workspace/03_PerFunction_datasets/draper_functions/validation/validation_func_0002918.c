instancemethod_getattro(PyObject *obj, PyObject *name)
{
    PyMethodObject *im = (PyMethodObject *)obj;
    PyTypeObject *tp = obj->ob_type;
    PyObject *descr = NULL;

    if (PyType_HasFeature(tp, Py_TPFLAGS_HAVE_CLASS)) {
        if (tp->tp_dict == NULL) {
            if (PyType_Ready(tp) < 0)
                return NULL;
        }
        descr = _PyType_Lookup(tp, name);
    }

    if (descr != NULL) {
        descrgetfunc f = TP_DESCR_GET(descr->ob_type);
        if (f != NULL)
            return f(descr, obj, (PyObject *)obj->ob_type);
        else {
            Py_INCREF(descr);
            return descr;
        }
    }

    return PyObject_GetAttr(im->im_func, name);
}
