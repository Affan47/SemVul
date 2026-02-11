unicode_islower(PyUnicodeObject *self)
{
    register const Py_UNICODE *p = PyUnicode_AS_UNICODE(self);
    register const Py_UNICODE *e;
    int cased;


    if (PyUnicode_GET_SIZE(self) == 1)
        return PyBool_FromLong(Py_UNICODE_ISLOWER(*p));


    if (PyUnicode_GET_SIZE(self) == 0)
        return PyBool_FromLong(0);

    e = p + PyUnicode_GET_SIZE(self);
    cased = 0;
    for (; p < e; p++) {
        register const Py_UNICODE ch = *p;

        if (Py_UNICODE_ISUPPER(ch) || Py_UNICODE_ISTITLE(ch))
            return PyBool_FromLong(0);
        else if (!cased && Py_UNICODE_ISLOWER(ch))
            cased = 1;
    }
    return PyBool_FromLong(cased);
}
