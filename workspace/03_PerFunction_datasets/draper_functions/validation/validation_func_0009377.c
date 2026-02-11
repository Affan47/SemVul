ctx_mpd_class(PyObject *context, PyObject *v)
{
    PyObject *a;
    const char *cp;

    CONVERT_OP_RAISE(&a, v, context);

    cp = mpd_class(MPD(a), CTX(context));
    Py_DECREF(a);

    return PyUnicode_FromString(cp);
}
