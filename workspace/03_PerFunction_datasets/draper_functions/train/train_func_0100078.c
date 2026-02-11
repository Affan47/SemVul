getargs_Z(PyObject *self, PyObject *args)
{
    Py_UNICODE *str;
    Py_ssize_t size;
    if (!PyArg_ParseTuple(args, "Z", &str))
        return NULL;
    if (str != NULL) {
        size = Py_UNICODE_strlen(str);
        return PyUnicode_FromUnicode(str, size);
    } else
        Py_RETURN_NONE;
}
