int_divmod(PyIntObject *x, PyIntObject *y)
{
    long xi, yi;
    long d, m;
    CONVERT_TO_LONG(x, xi);
    CONVERT_TO_LONG(y, yi);
    switch (i_divmod(xi, yi, &d, &m)) {
    case DIVMOD_OK:
        return Py_BuildValue("(ll)", d, m);
    case DIVMOD_OVERFLOW:
        return PyLong_Type.tp_as_number->nb_divmod((PyObject *)x,
                                                   (PyObject *)y);
    default:
        return NULL;
    }
}
