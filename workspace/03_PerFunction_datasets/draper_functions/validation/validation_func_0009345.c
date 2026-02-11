traceback_print(PyObject *self, PyObject *args)
{
    PyObject *file;
    PyObject *traceback;
    int result;

    if (!PyArg_ParseTuple(args, "OO:traceback_print",
                            &traceback, &file))
        return NULL;

    result = PyTraceBack_Print(traceback, file);
    if (result < 0)
        return NULL;
    Py_RETURN_NONE;
}
