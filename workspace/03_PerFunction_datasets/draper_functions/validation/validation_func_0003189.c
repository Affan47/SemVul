iobase_readlines(PyObject *self, PyObject *args)
{
    Py_ssize_t hint = -1, length = 0;
    PyObject *result;

    if (!PyArg_ParseTuple(args, "|O&:readlines", &_PyIO_ConvertSsize_t, &hint)) {
        return NULL;
    }

    result = PyList_New(0);
    if (result == NULL)
        return NULL;

    if (hint <= 0) {


        _Py_IDENTIFIER(extend);
        PyObject *ret = _PyObject_CallMethodId(result, &PyId_extend, "O", self);

        if (ret == NULL) {
            Py_DECREF(result);
            return NULL;
        }
        Py_DECREF(ret);
        return result;
    }

    while (1) {
        PyObject *line = PyIter_Next(self);
        if (line == NULL) {
            if (PyErr_Occurred()) {
                Py_DECREF(result);
                return NULL;
            }
            else
                break;
        }

        if (PyList_Append(result, line) < 0) {
            Py_DECREF(line);
            Py_DECREF(result);
            return NULL;
        }
        length += PyObject_Size(line);
        Py_DECREF(line);

        if (length > hint)
            break;
    }
    return result;
}
